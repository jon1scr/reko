#region License
/* 
 * Copyright (C) 1999-2016 John K�ll�n.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#endregion

using Reko.Core;
using Reko.Core.Code;
using Reko.Core.Lib;
using Reko.Core.Output;
using Reko.Core.Services;
using Reko.Core.Types;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace Reko.Analysis
{
	/// <summary>
	/// We are keenly interested in discovering the register linkage 
	/// between procedures, i.e. what registers are used by a called 
	/// procedure, and what modified registers are used by a calling 
	/// procedure. Once these registers have been discovered, we can
	/// separate the procedures from each other and proceed with the
	/// decompilation.
	/// </summary>
	public class DataFlowAnalysis
	{
		private Program program;
		private DecompilerEventListener eventListener;
        private IImportResolver importResolver;
		private ProgramDataFlow flow;
        private List<SsaTransform2> ssts;

        public DataFlowAnalysis(Program program, IImportResolver importResolver, DecompilerEventListener eventListener)
		{
			this.program = program;
            this.importResolver = importResolver;
            this.eventListener = eventListener;
			this.flow = new ProgramDataFlow(program);
		}

		public void AnalyzeProgram()
		{
			UntangleProcedures();
			BuildExpressionTrees();
		}

        /// <summary>
        /// Processes procedures individually, building complex expression trees out
        /// of the simple, close-to-the-machine code generated by the disassembly.
        /// </summary>
        /// <param name="rl"></param>
		public void BuildExpressionTrees()
		{
            int i = 0;
			foreach (Procedure proc in program.Procedures.Values)
			{
                eventListener.ShowProgress("Building complex expressions.", i, program.Procedures.Values.Count);
                ++i;

                try
                {
                    var larw = new LongAddRewriter(proc, program.Architecture);
                    larw.Transform();

                    Aliases alias = new Aliases(proc, program.Architecture, flow);
                    alias.Transform();

                    var doms = new DominatorGraph<Block>(proc.ControlGraph, proc.EntryBlock);
                    var sst = new SsaTransform(flow, proc, importResolver, doms, new HashSet<RegisterStorage>());
                    var ssa = sst.SsaState;

                    var icrw = new IndirectCallRewriter(program, ssa, eventListener);
                    icrw.Rewrite();

                    var cce = new ConditionCodeEliminator(ssa, program.Platform);
                    cce.Transform();
                    //var cd = new ConstDivisionImplementedByMultiplication(ssa);
                    //cd.Transform();

                    DeadCode.Eliminate(proc, ssa);

                    var vp = new ValuePropagator(program.Architecture, ssa);
                    vp.Transform();
                    DeadCode.Eliminate(proc, ssa);

                    // Build expressions. A definition with a single use can be subsumed
                    // into the using expression. 

                    var coa = new Coalescer(ssa);
                    coa.Transform();
                    DeadCode.Eliminate(proc, ssa);

                    var liv = new LinearInductionVariableFinder(
                        proc,
                        ssa.Identifiers,
                        new BlockDominatorGraph(proc.ControlGraph, proc.EntryBlock));
                    liv.Find();

                    foreach (KeyValuePair<LinearInductionVariable, LinearInductionVariableContext> de in liv.Contexts)
                    {
                        var str = new StrengthReduction(ssa, de.Key, de.Value);
                        str.ClassifyUses();
                        str.ModifyUses();
                    }
                    var opt = new OutParameterTransformer(proc, ssa.Identifiers);
                    opt.Transform();
                    DeadCode.Eliminate(proc, ssa);

                    // Definitions with multiple uses and variables joined by PHI functions become webs.
                    var web = new WebBuilder(ssa, program.InductionVariables);
                    web.Transform();
                    ssa.ConvertBack(false);
                }
                catch (StatementCorrelatedException stex)
                {
                    eventListener.Error(
                        eventListener.CreateStatementNavigator(program, stex.Statement),
                        stex, 
                        "An error occurred during data flow analysis.");
                }
                catch (Exception ex)
                {
                    eventListener.Error(
                        new NullCodeLocation(proc.Name),
                        ex,
                        "An error occurred during data flow analysis.");
                }
			}
		}

		public void DumpProgram()
		{
			foreach (Procedure proc in program.Procedures.Values)
			{
				StringWriter output = new StringWriter();
                ProcedureFlow pf = this.flow[proc];
                TextFormatter f = new TextFormatter(output);
				if (pf.Signature != null)
					pf.Signature.Emit(proc.Name, FunctionType.EmitFlags.None, f);
				else if (proc.Signature != null)
					proc.Signature.Emit(proc.Name, FunctionType.EmitFlags.None, f);
				else
					output.Write("Warning: no signature found for {0}", proc.Name);
				output.WriteLine();
				pf.Emit(program.Architecture, output);

				output.WriteLine("// {0}", proc.Name);
				proc.Signature.Emit(proc.Name, FunctionType.EmitFlags.None, f);
				output.WriteLine();
				foreach (Block block in proc.ControlGraph.Blocks)
				{
					if (block != null)
					{
						BlockFlow bf = this.flow[block];
						bf.Emit(program.Architecture, output);
						output.WriteLine();
						block.Write(output);
					}
				}
				Debug.WriteLine(output.ToString());
			}
		}

		public ProgramDataFlow ProgramDataFlow
		{
			get { return flow; }
		}

		/// <summary>
		/// Finds all interprocedural register dependencies (in- and out-parameters) and
		/// abstracts them away by rewriting as calls.
		/// </summary>
        /// <returns>A RegisterLiveness object that summarizes the interprocedural register
        /// liveness analysis. This information can be used to generate SSA form.
        /// </returns>
		public void UntangleProcedures()
		{
            eventListener.ShowStatus("Eliminating intra-block dead registers.");
            var usb = new UserSignatureBuilder(program);
            usb.BuildSignatures();
            CallRewriter.Rewrite(program);
            IntraBlockDeadRegisters.Apply(program);
            eventListener.ShowStatus("Finding terminating procedures.");
            var term = new TerminationAnalysis(flow);
            term.Analyze(program);
			eventListener.ShowStatus("Finding trashed registers.");
            var trf = new TrashedRegisterFinder(program, program.Procedures.Values, flow, eventListener);
			trf.Compute();
            eventListener.ShowStatus("Rewriting affine expressions.");
            trf.RewriteBasicBlocks();
            eventListener.ShowStatus("Computing register liveness.");
            var rl = RegisterLiveness.Compute(program, flow, eventListener);
            eventListener.ShowStatus("Rewriting calls.");
			GlobalCallRewriter.Rewrite(program, flow);
		}

        // EXPERIMENTAL - consult uxmal before using
        /// <summary>
        /// Analyzes the procedures of a program by finding all strongly 
        /// connected components (SCCs) and processing the SCCs one by one.
        /// </summary>
        public void AnalyzeProgram2()
        {
            var usb = new UserSignatureBuilder(program);
            usb.BuildSignatures();

            this.ssts = new List<SsaTransform2>();
            var sscf = new SccFinder<Procedure>(new ProcedureGraph(program), UntangleProcedureScc);
            foreach (var procedure in program.Procedures.Values)
            {
                sscf.Find(procedure);
            }

            // Discover values that are live out at each call site.
            var uvr = new UnusedOutValuesRemover();
            uvr.Transform(ssts);

            BuildExpressionTrees2();
        }

        private void UntangleProcedureScc(IList<Procedure> procs)
        {
            // Convert all procedures in the SCC to SSA form and perform
            // value propagation.
            var ssts = procs.Select(p => ConvertToSsa(p)).ToArray();
            this.ssts.AddRange(ssts);

            // At this point, the computation of ProcedureFlow is be possible.
            var tid = new TrashedRegisterFinder2(program.Architecture, flow, ssts, this.eventListener);
            var uid = new UsedRegisterFinder(program.Architecture, flow, ssts, this.eventListener);
            foreach (var sst in ssts)
            {
                tid.Compute(sst.SsaState);
                uid.Compute(sst.SsaState);
            }

            // 
        }

        public void BuildExpressionTrees2()
        {
            foreach (var ssa in this.ssts)
            {
                // Procedures should be untangled from each other. Now process each one separately.
                var proc = ssa.SsaState.Procedure;
                DeadCode.Eliminate(proc, ssa.SsaState);

                // Build expressions. A definition with a single use can be subsumed
                // into the using expression. 

                var coa = new Coalescer(ssa.SsaState);
                coa.Transform();
                DeadCode.Eliminate(proc, ssa.SsaState);

                var liv = new LinearInductionVariableFinder(
                    proc,
                    ssa.SsaState.Identifiers,
                    new BlockDominatorGraph(proc.ControlGraph, proc.EntryBlock));
                liv.Find();

                foreach (var de in liv.Contexts)
                {
                    var str = new StrengthReduction(ssa.SsaState, de.Key, de.Value);
                    str.ClassifyUses();
                    str.ModifyUses();
                }

                //var opt = new OutParameterTransformer(proc, ssa.Identifiers);
                //opt.Transform();
                DeadCode.Eliminate(proc, ssa.SsaState);

                // Definitions with multiple uses and variables joined by PHI functions become webs.
                var web = new WebBuilder(ssa.SsaState, program.InductionVariables);
                web.Transform();
                ssa.SsaState.ConvertBack(false);
            }
        }

        public SsaTransform2 ConvertToSsa(Procedure proc)
        {
            // Transform the procedure to SSA state. When encountering 'call' instructions,
            // they can be to functions already visited. If so, they have a "ProcedureFlow" 
            // associated with them. If they have not been visited, or are computed destinations
            // (e.g. vtables) they will have no "ProcedureFlow" associated with them yet, in
            // which case the the SSA treats the call as a "hell node".
            var sst = new SsaTransform2(program.Architecture, proc, importResolver, new DataFlow2());
            sst.Transform();
            var ssa = sst.SsaState;

            // Propagate condition codes and registers. At the end, the hope is that 
            // all statements like (x86) mem[esp_42+4] will have been converted to
            // mem[fp - 30]. We also hope that procedure constants kept in registers
            // are propagated to the corresponding call sites.
            var cce = new ConditionCodeEliminator(ssa, program.Platform);
            cce.Transform();
            var vp = new ValuePropagator(program.Architecture, ssa);
            vp.Transform();

            // Now compute SSA for the stack-based variables as well. That is:
            // mem[fp - 30] becomes wLoc30, while 
            // mem[fp + 30] becomes wArg30.
            // This allows us to compute the dataflow of this procedure.
            sst.RenameFrameAccesses = true;
            sst.Transform();
            sst.AddUsesToExitBlock();
            sst.RemoveDeadSsaIdentifiers();

            // Propagate those newly discovered identifiers.
            vp.Transform();

            return sst;
        }
	}
}
