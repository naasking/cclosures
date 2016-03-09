#pragma once
#ifndef __DANDY_H__
#define __DANDY_H__

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>

typedef union val val_t;
typedef struct clo *clo_t;

/*
 * The universal representation for all values.
 */
typedef union val {
	float f;
	double d;
	void *p;
	signed   char sc;
	unsigned char uc;
	signed   short ss;
	unsigned short us;
	signed   int si;
	unsigned int ui;
	signed   long long sl;
	unsigned long long ul;
	uintptr_t w;
	clo_t fn;

	/* pointers/arrays of the primitive types */
	val_t *a;
	float *a_f;
	double *a_d;
	void *a_p;
	signed char *a_sc;
	unsigned char *a_uc;
	signed short *a_ss;
	unsigned short *a_us;
	signed int *a_si;
	unsigned int *a_ui;
	signed long *a_sl;
	unsigned long *a_ul;
	uintptr_t *a_w;
	clo_t *a_fn;
} val_t;

/*
 * The type of all closures. The first arg is a structure pointer for multiargument functions.
 */
typedef union fun {
	val_t(*fn0)();
	val_t(*fn1)(val_t arg0);
	val_t(*fn2)(val_t arg0, val_t arg1);
	val_t(*fn3)(val_t arg0, val_t arg1, val_t arg2);
	val_t(*fn4)(val_t arg0, val_t arg1, val_t arg2, val_t arg3);
	val_t(*fn5)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4);
	val_t(*fn6)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5);
	val_t(*fn7)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6);
	val_t(*fn8)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7);
	val_t(*fn9)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8);
	val_t(*fn10)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9);
	val_t(*fn11)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10);
	val_t(*fn12)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11);
	val_t(*fn13)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12);
	val_t(*fn14)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12, val_t arg13);
	val_t(*fn15)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12, val_t arg13, val_t arg14);
	val_t(*fn16)(val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12, val_t arg13, val_t arg14, val_t arg15);
} fn_t;

/*
 * The closure type.
 */
struct clo {
	fn_t fn;	   /* function to apply */
	unsigned argc; /* # of args in fn */
	unsigned argn; /* # of args in env */
	val_t env[]; /* environment entries start here */
};

/*
 * Applying closures.
 */
#define clo_invoke(clo) clo->fn.fn0()
#define clo_apply0(clo) (assert(clo->argc - clo->argn == 0),\
	clo->argc == 0 ? clo->fn.fn0():\
	clo->argc == 1 ? clo->fn.fn1(clo->env[0]):\
	clo->argc == 2 ? clo->fn.fn2(clo->env[0], clo->env[1]):\
	clo->argc == 3 ? clo->fn.fn3(clo->env[0], clo->env[1], clo->env[2]):\
	clo->argc == 4 ? clo->fn.fn4(clo->env[0], clo->env[1], clo->env[2], clo->env[3]):\
	clo->argc == 5 ? clo->fn.fn5(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4]):\
	clo->argc == 6 ? clo->fn.fn6(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5]):\
	clo->argc == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6]):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7]):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8]):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9]):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10]):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11]):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12]):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13]):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], clo->env[14]):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], clo->env[14], clo->env[15])\
)
#define clo_apply1(clo, arg0) (assert(clo->argc - clo->argn == 1),\
	clo->argc == 1 ? clo->fn.fn1(arg0):\
	clo->argc == 2 ? clo->fn.fn2(clo->env[0], arg0):\
	clo->argc == 3 ? clo->fn.fn3(clo->env[0], clo->env[1], arg0):\
	clo->argc == 4 ? clo->fn.fn4(clo->env[0], clo->env[1], clo->env[2], arg0):\
	clo->argc == 5 ? clo->fn.fn5(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0):\
	clo->argc == 6 ? clo->fn.fn6(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0):\
	clo->argc == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], arg0):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], arg0):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], clo->env[14], arg0)\
)
#define clo_apply2(clo, arg0, arg1) (assert(clo->argc - clo->argn == 2),\
	clo->argc == 2 ? clo->fn.fn2(arg0, arg1):\
	clo->argc == 3 ? clo->fn.fn3(clo->env[0], arg0, arg1):\
	clo->argc == 4 ? clo->fn.fn4(clo->env[0], clo->env[1], arg0, arg1):\
	clo->argc == 5 ? clo->fn.fn5(clo->env[0], clo->env[1], clo->env[2], arg0, arg1):\
	clo->argc == 6 ? clo->fn.fn6(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1):\
	clo->argc == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9],  arg0, arg1):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0, arg1):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], arg0, arg1):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], arg0, arg1)\
)
#define clo_apply3(clo, arg0, arg1, arg2) (assert(clo->argc - clo->argn == 3),\
	clo->argc == 3 ? clo->fn.fn3(arg0, arg1, arg2):\
	clo->argc == 4 ? clo->fn.fn4(clo->env[0], arg0, arg1, arg2):\
	clo->argc == 5 ? clo->fn.fn5(clo->env[0], clo->env[1], arg0, arg1, arg2):\
	clo->argc == 6 ? clo->fn.fn6(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2):\
	clo->argc == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1, arg2):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1, arg2):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11],  arg0, arg1, arg2):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], arg0, arg1, arg2)\
)
#define clo_apply4(clo, arg0, arg1, arg2, arg3) (assert(clo->argc - clo->argn == 4),\
	clo->argc == 4 ? clo->fn.fn4(arg0, arg1, arg2, arg3):\
	clo->argc == 5 ? clo->fn.fn5(clo->env[0], arg0, arg1, arg2, arg3):\
	clo->argc == 6 ? clo->fn.fn6(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3):\
	clo->argc == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1, arg2, arg3):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1, arg2, arg3):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0, arg1, arg2, arg3)\
)
#define clo_apply5(clo, arg0, arg1, arg2, arg3, arg4) (assert(clo->argc - clo->argn == 5),\
	clo->argc == 5 ? clo->fn.fn5(arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 6 ? clo->fn.fn6(clo->env[0], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3, arg4):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1, arg2, arg3, arg4):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1, arg2, arg3, arg4)\
)
#define clo_apply6(clo, arg0, arg1, arg2, arg3, arg4, arg5) (assert(clo->argc - clo->argn == 6),\
	clo->argc == 6 ? clo->fn.fn6(arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 7 ? clo->fn.fn7(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3, arg4, arg5):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1, arg2, arg3, arg4, arg5)\
)
#define clo_apply7(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6) (assert(clo->argc - clo->argn == 7),\
	clo->argc == 7 ? clo->fn.fn7(arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 8 ? clo->fn.fn8(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3, arg4, arg5, arg6)\
)
#define clo_apply8(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) (assert(clo->argc - clo->argn == 8),\
	clo->argc == 8 ? clo->fn.fn8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo->argc == 9 ? clo->fn.fn9(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)\
)
#define clo_apply9(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) (assert(clo->argc - clo->argn == 9),\
	clo->argc == 9 ? clo->fn.fn9(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo->argc == 10 ? clo->fn.fn10(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)\
)
#define clo_apply10(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) (assert(clo->argc - clo->argn == 10),\
	clo->argc == 10 ? clo->fn.fn10(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo->argc == 11 ? clo->fn.fn11(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)\
)
#define clo_apply11(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) (assert(clo->argc - clo->argn == 11),\
	clo->argc == 11 ? clo->fn.fn11(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo->argc == 12 ? clo->fn.fn12(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)\
)
#define clo_apply12(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) (assert(clo->argc - clo->argn == 12),\
	clo->argc == 12 ? clo->fn.fn12(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
	clo->argc == 13 ? clo->fn.fn13(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)\
)
#define clo_apply13(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) (assert(clo->argc - clo->argn == 13),\
	clo->argc == 14 ? clo->fn.fn14(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12):\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12):\
                      clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)\
)
#define clo_apply14(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) (assert(clo->argc - clo->argn == 14),\
	clo->argc == 15 ? clo->fn.fn15(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13):\
                      clo->fn.fn16(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)\
)
#define clo_apply15(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) (assert(clo->argc - clo->argn == 15),\
	clo->fn.fn16(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)\
)
#define clo_apply16(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) (assert(clo->argc - clo->argn == 16),\
	clo->fn.fn16(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)\
)

/*
 * Lift a C function pointer and its context to a closure.
 */
clo_t clo_lift(fn_t fn, unsigned argc, unsigned argn, ...);


/*
 * Partial application can be a set of macros like apply that simple invoke clo_lift.
 * Or perhaps make them functions?
 */
#define clo_papply1(clo, arg0) (assert(clo->argc - clo->argn >= 1),\
	clo->argc == 1 ? clo_lift(clo->fn, clo->argc, 1, arg0):\
	clo->argc == 2 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], arg0):\
	clo->argc == 3 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], arg0):\
	clo->argc == 4 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], arg0):\
	clo->argc == 5 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0):\
	clo->argc == 6 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0):\
	clo->argc == 7 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0):\
	clo->argc == 8 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0):\
	clo->argc == 9 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0):\
	clo->argc == 10 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0):\
	clo->argc == 11 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0):\
	clo->argc == 12 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0):\
	clo->argc == 13 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0):\
	clo->argc == 14 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], arg0):\
	clo->argc == 15 ? clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], arg0):\
					  clo_lift(clo->fn, clo->argc, 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], clo->env[14], arg0):\
)
#define clo_papply2(clo, arg0, arg1) (assert(clo->argc - clo->argn >= 2),\
	clo->argc == 2 ? clo_lift(clo->fn, clo->argc, 2, arg0, arg1):\
	clo->argc == 3 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], arg0, arg1):\
	clo->argc == 4 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], arg0, arg1):\
	clo->argc == 5 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], arg0, arg1):\
	clo->argc == 6 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1):\
	clo->argc == 7 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1):\
	clo->argc == 8 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1):\
	clo->argc == 9 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1):\
	clo->argc == 10 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1):\
	clo->argc == 11 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1):\
	clo->argc == 12 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1):\
	clo->argc == 13 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1):\
	clo->argc == 14 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0, arg1):\
	clo->argc == 15 ? clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], arg0, arg1):\
					  clo_lift(clo->fn, clo->argc, 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], arg0, arg1):\
)
//...

/*
 * Compose two closures with the given argument counts.
 */
//clo_t clo_compose(clo_t f, unsigned fargc, clo_t g, unsigned gargc);

//#define clo_lift0(fn) clo_lift({ fn }, { 0 }, 0)
//#define clo_lift1(fn, arg0) clo_lift({ fn }, struct { arg0 }, sizeof(val_t))
//#define clo_lift2(fn, arg0) clo_lift({ fn }, { arg0 }, 2 * sizeof(val_t))

#endif /* __DANDY_H__ */
