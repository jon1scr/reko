// example.c
// Generated by decompiling example
// using Reko decompiler version 0.8.0.0.

#include "example.h"

// 00000560: FlagGroup byte _init(Stack word64 qwArg30, Stack word64 qwArg38, Stack word64 qwArg40, Stack word64 qwArg48, Stack word64 qwArg50, Stack word64 qwArg58, Stack word64 qwArg60, Stack word64 qwArg68, Stack word64 qwArg70, Stack word64 qwArg78)
byte _init(word64 qwArg30, word64 qwArg38, word64 qwArg40, word64 qwArg48, word64 qwArg50, word64 qwArg58, word64 qwArg60, word64 qwArg68, word64 qwArg70, word64 qwArg78)
{
	word64 r1_37 = Mem0[0x00002038 + 0x00:word64];
	if (r1_37 != 0x00)
	{
		word64 r15_76;
		word64 r6_77;
		word64 r7_78;
		word64 r8_79;
		word64 r9_80;
		word64 r10_81;
		word64 r11_82;
		word64 r12_83;
		word64 r13_84;
		word64 r14_85;
		word64 r1_86;
		byte CC_87;
		word64 r4_88;
		r1_37();
	}
	word64 r15_61;
	word64 r6_62;
	word64 r7_63;
	word64 r8_64;
	word64 r9_65;
	word64 r10_66;
	word64 r11_67;
	word64 r12_68;
	word64 r13_69;
	word64 r14_70;
	word64 r1_71;
	byte CC_72;
	word64 r4_73;
	r14();
	return CC_72;
}

// 000005C0: void __cxa_finalize()
void __cxa_finalize()
{
}

// 000005E0: void __libc_start_main()
void __libc_start_main()
{
}

// 00000600: void _start(Register Eq_47 r14, Stack Eq_48 qwArg00)
void _start(Eq_47 r14, Eq_48 qwArg00)
{
	Eq_49 r15_7 = (fp & ~0x0F) - 0x00B0;
	*r15_7 = 0x00;
	*((word64) r15_7 + 0x00A0) = r14;
	*((word64) r15_7 + 0x00A8) = r15_7;
	word64 r2_20 = Mem15[0x00002040 + 0x00:word64];
	word64 r2_22 = DPB(r2_20, __libc_start_main(r2_20, qwArg00, (word32) fp + 0x08, 0x00000820, 0x00000888, Mem15[r15_7 + 0x00A0:(ptr32 (fn void ()))], Mem15[r15_7 + 0x00A8:(ptr32 void)]), 0);
}

// 00000648: void deregister_tm_clones()
void deregister_tm_clones()
{
	Eq_92 r2_4 = 0x2068;
	Eq_94 r5_2 = 0x08C8;
	Eq_96 r1_6 = 8303 - r2_4;
	if (r1_6 > *r5_2)
	{
		word64 r1_23 = Mem0[0x00002030 + 0x00:word64];
		if (r1_23 != 0x00)
		{
			word64 r15_32;
			word64 r5_33;
			word64 r1_34;
			word64 r2_35;
			byte CC_36;
			word64 r14_37;
			r1_23();
		}
		else
		{
			word64 r15_26;
			word64 r5_27;
			word64 r1_28;
			word64 r2_29;
			byte CC_30;
			word64 r14_31;
			r14();
		}
	}
	else
	{
		word64 r15_16;
		word64 r5_17;
		word64 r1_18;
		word64 r2_19;
		byte CC_20;
		word64 r14_21;
		r14();
	}
}

// 00000680: void register_tm_clones()
void register_tm_clones()
{
	Eq_129 r3_4 = 0x2068 - 0x2068;
	uint64 r1_6 = r3_4 >> 0x03 >> 0x003F;
	if ((r3_4 >> 0x03) + r1_6 != 0x00)
	{
		word64 r1_26 = Mem0[0x00002050 + 0x00:word64];
		if (r1_26 != 0x00)
		{
			word64 r15_36;
			word64 r1_37;
			word64 r3_38;
			byte CC_39;
			word64 r14_40;
			word64 r2_41;
			r1_26();
		}
		else
		{
			word64 r15_29;
			word64 r1_30;
			word64 r3_31;
			byte CC_32;
			word64 r14_33;
			word64 r2_34;
			r14();
		}
	}
	else
	{
		word64 r15_18;
		word64 r1_19;
		word64 r3_20;
		byte CC_21;
		word64 r14_22;
		word64 r2_23;
		r14();
	}
}

// 000006C8: void __do_global_dtors_aux(Stack word64 qwArg58, Stack word64 qwArg60, Stack word64 qwArg68, Stack word64 qwArg70, Stack word64 qwArg78)
void __do_global_dtors_aux(word64 qwArg58, word64 qwArg60, word64 qwArg68, word64 qwArg70, word64 qwArg78)
{
	Eq_173 r13_16 = 0x08D0;
	Eq_175 r11_18 = 0x2068;
	if (*r11_18 == 0x00)
	{
		if (Mem0[r13_16 + 0x00:byte] != Mem0[0x00002028 + 0x00:byte])
		{
			word64 r15_58;
			word64 r12_60;
			word64 r13_61;
			word64 r14_62;
			byte CC_63;
			word64 r1_64;
			word64 r2_65;
			word64 r4_66;
			__cxa_finalize();
		}
		deregister_tm_clones();
		*r11_18 = 0x01;
	}
	word64 r15_32;
	word64 r11_33;
	word64 r12_34;
	word64 r13_35;
	word64 r14_36;
	byte CC_37;
	word64 r1_38;
	word64 r2_39;
	word64 r4_40;
	r14();
}

// 00000720: void frame_dummy(Stack word64 qwArg68, Stack word64 qwArg70, Stack word64 qwArg78)
void frame_dummy(word64 qwArg68, word64 qwArg70, word64 qwArg78)
{
	Eq_220 r13_10 = 0x08D8;
	Eq_222 r2_12 = 0x1E18;
	Eq_224 CC_14 = cond(*r13_10 - *r2_12);
	if (*r13_10 == *r2_12)
	{
l00000740:
		if (CC_14)
		{
			register_tm_clones();
			return;
		}
	}
	word64 r1_23 = Mem0[0x00002048 + 0x00:word64];
	CC_14 = cond(r1_23);
	if (r1_23 != 0x00)
	{
		word64 r15_27;
		word64 r13_28;
		word64 r14_29;
		word64 r2_31;
		word64 r1_32;
		word64 r3_33;
		r1_23();
	}
	goto l00000740;
}

// 00000768: Register int64 fib(Register int64 r2, Stack word64 qwArg50, Stack word64 qwArg58, Stack word64 qwArg60, Stack word64 qwArg68, Stack word64 qwArg70, Stack word64 qwArg78)
int64 fib(int64 r2, word64 qwArg50, word64 qwArg58, word64 qwArg60, word64 qwArg68, word64 qwArg70, word64 qwArg78)
{
	word32 dwLoc04_23 = (word32) r2;
	if (DPB(r2, dwLoc04_23, 0) > 0x01)
	{
		fib((int64) (dwLoc04_23 - 0x01), qwLoc58, qwLoc50, qwLoc48, qwLoc40, qwLoc38, qwLoc30);
		fib((int64) (dwLoc04_23 - 0x02), qwLoc58, qwLoc50, qwLoc48, qwLoc40, qwLoc38, qwLoc30);
	}
	word64 r15_43;
	word64 r10_44;
	word64 r11_45;
	word64 r12_46;
	word64 r13_47;
	word64 r14_48;
	byte CC_49;
	int64 r2_50;
	word64 r1_51;
	word64 r4_52;
	r14();
	return r2_50;
}

// 000007E0: void main(Register word64 r2, Stack word64 qwArg58, Stack word64 qwArg60, Stack word64 qwArg68, Stack word64 qwArg70, Stack word64 qwArg78)
void main(word64 r2, word64 qwArg58, word64 qwArg60, word64 qwArg68, word64 qwArg70, word64 qwArg78)
{
	fib(0x0A, qwLoc60, qwLoc58, qwLoc50, qwLoc48, qwLoc40, qwLoc38);
	word64 r15_48;
	word64 r11_49;
	word64 r12_50;
	word64 r13_51;
	word64 r14_52;
	byte CC_53;
	word64 r2_54;
	word64 r1_55;
	word64 r3_56;
	word64 r4_57;
	r14();
}

// 00000820: void __libc_csu_init(Stack word64 qwArg38, Stack word64 qwArg40, Stack word64 qwArg48, Stack word64 qwArg50, Stack word64 qwArg58, Stack word64 qwArg60, Stack word64 qwArg68, Stack word64 qwArg70, Stack word64 qwArg78)
void __libc_csu_init(word64 qwArg38, word64 qwArg40, word64 qwArg48, word64 qwArg50, word64 qwArg58, word64 qwArg60, word64 qwArg68, word64 qwArg70, word64 qwArg78)
{
	Eq_332 CC_47 = _init(qwLoc70, qwLoc68, qwLoc60, qwLoc58, qwLoc50, qwLoc48, qwLoc40, qwLoc38, qwLoc30, qwLoc28);
	Eq_346 r1_49 = 7688;
	if (!CC_47)
	{
		Eq_346 r7_85 = r1_49;
		do
		{
			Eq_364 r1_91 = *r7_85;
			word64 r15_98;
			word64 r8_100;
			word64 r9_101;
			word64 r10_102;
			word64 r11_103;
			word64 r12_104;
			word64 r13_105;
			word64 r14_106;
			byte CC_107;
			word64 r2_108;
			word64 r3_109;
			word64 r4_110;
			word64 r1_111;
			r1_91();
		} while (r11_103 != 0x01);
	}
	word64 r15_71;
	word64 r7_72;
	word64 r8_73;
	word64 r9_74;
	word64 r10_75;
	word64 r11_76;
	word64 r12_77;
	word64 r13_78;
	word64 r14_79;
	byte CC_80;
	word64 r2_81;
	word64 r3_82;
	word64 r4_83;
	word64 r1_84;
	r14();
}

// 00000888: void __libc_csu_fini()
void __libc_csu_fini()
{
	word64 r15_3;
	word64 r14_4;
	r14();
}

// 00000890: void _fini(Stack word64 qwArg30, Stack word64 qwArg38, Stack word64 qwArg40, Stack word64 qwArg48, Stack word64 qwArg50, Stack word64 qwArg58, Stack word64 qwArg60, Stack word64 qwArg68, Stack word64 qwArg70, Stack word64 qwArg78)
void _fini(word64 qwArg30, word64 qwArg38, word64 qwArg40, word64 qwArg48, word64 qwArg50, word64 qwArg58, word64 qwArg60, word64 qwArg68, word64 qwArg70, word64 qwArg78)
{
	word64 r15_56;
	word64 r6_57;
	word64 r7_58;
	word64 r8_59;
	word64 r9_60;
	word64 r10_61;
	word64 r11_62;
	word64 r12_63;
	word64 r13_64;
	word64 r14_65;
	word64 r1_66;
	byte CC_67;
	word64 r4_68;
	r14();
}

