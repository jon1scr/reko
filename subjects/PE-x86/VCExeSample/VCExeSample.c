// VCExeSample.c
// Generated by decompiling VCExeSample.exe
// using Reko decompiler version 0.6.1.0.

#include "VCExeSample.h"

int32 main(int32 argc, char * * argv)
{
	test1(*argv, argc, "test123", 1.0F);
	return 0x00;
}

void test1(char * arg1, int32 arg2, char * arg3, real32 arg4)
{
	printf("%s %d %s %f", arg1, arg2, arg3, (real64) arg4);
	return;
}

void test2(word32 dwArg04)
{
	test1("1", 0x02, "3", globals->r4020E8);
	if (dwArg04 == 0x00)
		test1("5", 0x06, "7", globals->r4020E4);
	return;
}

void indirect_call_test3(cdecl_class * c)
{
	c->vtbl->method04(c, 1000);
	return;
}

void test4()
{
	globals->gbl_c->vtbl->method00(globals->gbl_c);
	return;
}

void test5()
{
	globals->gbl_c->vtbl->method04(globals->gbl_c, 999, globals->r4020EC);
	return;
}

void test6(cdecl_class * c, int32 a, int32 b)
{
	c->vtbl->method04(c, c->vtbl->sum(c, a, b));
	return;
}

void test7(real64 rArg04)
{
	if (1.0 > rArg04)
		globals->gbl_thiscall->vtbl->set_double(globals->gbl_thiscall, rArg04);
	globals->gbl_thiscall->vtbl->modify_double(globals->gbl_thiscall, 0x0D, rArg04);
	return;
}

