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
	val_t env;	   /* empty array is a pointer to itself in the struct */
	val_t data[];  /* empty array is a pointer to itself in the struct */
};

#define clo_invoke(clo) clo->fn.fn0()
#define clo_apply0(clo) (assert(clo->argc == 1), clo->fn.fn1(clo->env))
#define clo_apply1(clo, arg0) (assert(clo->argc == 2), clo->fn.fn2(clo->env, arg0))
#define clo_apply2(clo, arg0, arg1) (assert(clo->argc == 3), clo->fn.fn3(clo->env, arg0, arg1))
#define clo_apply3(clo, arg0, arg1, arg2) (assert(clo->argc == 4), clo->fn.fn4(clo->env, arg0, arg1, arg2))
#define clo_apply4(clo, arg0, arg1, arg2, arg3) (assert(clo->argc == 5), clo->fn.fn5(clo->env, arg0, arg1, arg2, arg3))
#define clo_apply5(clo, arg0, arg1, arg2, arg3, arg4) (assert(clo->argc == 6), clo->fn.fn6(clo->env, arg0, arg1, arg2, arg3, arg4))
#define clo_apply6(clo, arg0, arg1, arg2, arg3, arg4, arg5) (assert(clo->argc == 7), clo->fn.fn7(clo->env, arg0, arg1, arg2, arg3, arg4, arg5))
#define clo_apply7(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6) (assert(clo->argc == 8), clo->fn.fn8(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6))
#define clo_apply8(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) (assert(clo->argc == 9), clo->fn.fn9(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7))
#define clo_apply9(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) (assert(clo->argc == 10), clo->fn.fn10(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8))
#define clo_apply10(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) (assert(clo->argc == 11), clo->fn.fn11(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9))
#define clo_apply11(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) (assert(clo->argc == 12), clo->fn.fn12(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10))
#define clo_apply12(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) (assert(clo->argc == 13), clo->fn.fn13(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11))
#define clo_apply13(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) (assert(clo->argc == 14), clo->fn.fn14(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12))
#define clo_apply14(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) (assert(clo->argc == 15), clo->fn.fn15(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13))
#define clo_apply15(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) (assert(clo->argc == 16), clo->fn.fn16(clo->env, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14))


/*
 * Lift a C function pointer and its context to a closure.
 */
clo_t clo_lift(fn_t fn, unsigned argc, unsigned argn, ...);


/*
 * Compose two closures with the given argument counts.
 */
//clo_t clo_compose(clo_t f, unsigned fargc, clo_t g, unsigned gargc);

//#define clo_lift0(fn) clo_lift({ fn }, { 0 }, 0)
//#define clo_lift1(fn, arg0) clo_lift({ fn }, struct { arg0 }, sizeof(val_t))
//#define clo_lift2(fn, arg0) clo_lift({ fn }, { arg0 }, 2 * sizeof(val_t))

#endif /* __DANDY_H__ */
