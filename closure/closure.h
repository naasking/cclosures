#pragma once
#ifndef __CLOSURE_H__
#define __CLOSURE_H__

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <meta.h>
#include <errno.h>

#if defined(_WIN64) || defined(WIN64) || defined(__sparc64__) || defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(__ppc64__) || defined(__PPC64__) || defined(__ppc64) || defined(__LP__) || defined(_LP64) || defined(_AMD64_) || defined(_____LP64_____) || defined(__LP64__)
#define WD64BIT
#endif

/* alloca.h is not provided by MSVC */
//#ifdef _MSC_VER
//#include <malloc.h>
//#define alloca _alloca
//#else
//#include <alloca.h>
//#endif

typedef struct clo *clo_t;

/* native machine word type */
typedef uintptr_t word_t;

/*
* The universal representation for all values.
*/
typedef union val {
	/* platform-specific types */
	void *p;
	signed   char sc;
	unsigned char uc;
	signed   short ss;
	unsigned short us;
	signed   int si;
	unsigned int ui;
	signed   long long sl;
	unsigned long long ul;
	word_t w;

	/* fixed width types */
	float f;
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	int8_t i8;
	int16_t i16;
	int32_t i32;

	/* 64-bit types are either inlined, or pointed to */
#ifdef WD64BIT
	double d;
	uint64_t u64;
	int64_t i64;
#else
	double *d;
	uint64_t *u64;
	int64_t *i64;
#endif // WD64BIT

	/* pointers/arrays of the primitive types */
	union val *a;
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
	uint8_t *a_u8;
	uint16_t *a_u16;
	uint32_t *a_u32;
	uint64_t *a_u64;
	int8_t *a_i8;
	int16_t *a_i16;
	int32_t *a_i32;
	int64_t *a_i64;
	word_t *a_w;
	struct clo **a_fn;
} val_t;

/*
 * The type of all closures. The first arg is a structure pointer for multiargument functions.
 */
typedef union fun {
	val_t(*fn0)();
	val_t(*fn1)(register val_t arg0);
	val_t(*fn2)(register val_t arg0, val_t arg1);
	val_t(*fn3)(register val_t arg0, val_t arg1, val_t arg2);
	val_t(*fn4)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3);
	val_t(*fn5)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4);
	val_t(*fn6)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5);
	val_t(*fn7)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6);
	val_t(*fn8)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7);
	val_t(*fn9)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8);
	val_t(*fn10)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9);
	val_t(*fn11)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10);
	val_t(*fn12)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11);
	val_t(*fn13)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12);
	val_t(*fn14)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12, val_t arg13);
	val_t(*fn15)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12, val_t arg13, val_t arg14);
	val_t(*fn16)(register val_t arg0, val_t arg1, val_t arg2, val_t arg3, val_t arg4, val_t arg5, val_t arg6, val_t arg7, val_t arg8, val_t arg9, val_t arg10, val_t arg11, val_t arg12, val_t arg13, val_t arg14, val_t arg15);
} fn_t;

/*
 * The closure type.
 */
struct clo {
	word_t hdr;  /* header word containing number of args */
	fn_t fn;	 /* function to apply */
	val_t env[]; /* environment entries start here */
};

/*
 * The offset of the argument counts in the header.
 */
#define CLO_ARGC_OFF 4

/*
 * The maximum number of arguments.
 */
#define CLO_ARGS_MAX 16

/*
 * The number of function arguments.
 */
#define clo_argc(c) (((c)->hdr >> CLO_ARGC_OFF) & 0x07)

/*
 * The number of remaining arguments to apply.
 */
#define clo_argr(c) (((c)->hdr >> (CLO_ARGC_OFF - 4)) & 0x07)

/*
 * The number of applied arguments.
 */
#define clo_arga(c) (clo_argc(c) - clo_argr(c))

/* 
 * Closure environment size for the given number of arguments.
 */
#define clo_esize(argn) sizeof(val_t) * (argn)

/*
 * The size of a closure for the given number of arguments.
 */
#define clo_size(argn) sizeof(struct clo) + clo_esize(argn)

/*
 * Lift a C function pointer and its context to a closure with the given allocator.
 *
 * The 'alloc' parameter must conform to malloc's signature.
 */
#define clo_liftw(alloc, fn, argc, ...) clo_init((clo_t)alloc(clo_size(VA_ARG_0(__VA_ARGS__))), fn, (argc), VA_ARG_FMT(VA_ARGC(__VA_ARGS__)-1, __VA_ARGS__))

/*
 * Lift a C function pointer and its context to a closure using alloca.
 */
#define clo_lifta(fn, argc, ...) clo_liftw(alloca, fn, argc, __VA_ARGS__)

/*
 * Lift a C function pointer and its context to a closure using malloc.
 */
#define clo_lift(fn, argc, ...) clo_liftw(malloc, fn, argc, __VA_ARGS__)

/*
 * Initialize an existing closure record with the given arguments.
 *
 * ERROR: returns E2BIG if argc exceeds the CLO_ARGS_MAX.
 */
clo_t clo_init(clo_t c, fn_t fn, unsigned argc, unsigned argn, ...);


/* select the appropriate function signature given the provided arguments */
#define _clo_fn(...) VA_ARG_CAT(VA_ARG_0(__VA_ARGS__)->fn.fn, VA_ARGC(VA_ARG_SKIP_1(__VA_ARGS__)))

/*
 * Invoke the raw function with all parameters given. This macro assumes
 * no closure environment.
 */
#define clo_invoke(...) (assert(clo_argr(VA_ARG(0, __VA_ARGS__)) == VA_ARGC(__VA_ARGS__)-1),\
	_clo_fn(__VA_ARGS__)(VA_ARG_SKIP_1(__VA_ARGS__))\
)

/*
 * Call a closure with an environment and a known number of arguments. The first argument must be the closure parameter.
 * For N args, this generates an expression call of the form:
 *   (assert(clo_argc(clo) == N), clo->fn.fnN(clo->env[0], arg0, ..., argN))
 * in DEBUG mode, the assertion checks that the call is valid, and the subsequent expression actually executes it.
 */
#define clo_call(...) clo_invoke(VA_ARG_0(__VA_ARGS__), VA_ARG_FMT(VA_ARG_0(__VA_ARGS__)->env[0], __VA_ARGS__))

/*
 * Apply a curried closure. The first argument must be the closure parameter.
 * NOTE: currently incomplete, as I need a switch dispatching on the total number of args.
 */
#define clo_apply(out, ...) CAT(CLO_APPLY_, VA_ARGC(VA_ARG_SKIP_1(__VA_ARGS__)))(out, __VA_ARGS__)


/*
 * Closure application overloads.
 */
//#define CLO_CASE(i, out, ...) case i: out = CAT(VA_ARG_0(__VA_ARGS__)->fn.fn, i)(REPEAT(i, CLO_ENV, out, VA_ARG_0(__VA_ARGS__))); break;
//#define CLO_CASE(i, j, out, clo, ...) case i: out = CAT(clo->fn.fn, i)(REPEAT(i, CLO_ENV, out, clo) REPEAT(j, CLO_ARG, VA_EMPTY); break;
//#define CLO_CASE(i, j, out, clo, ...) case i: out = CAT(clo->fn.fn, i)(REPEAT(i, CLO_ENV, out, clo) WHEN(NOT_EQUAL(i,j))REPEAT(j, CLO_ARG)); break;
#define CLO_CASE(i, j, out, clo, ...) case i: out = CAT(clo->fn.fn, i)(REPEAT(i, CLO_ENV, out, clo) CLO_ARG(j, __VA_ARGS__)); break;
#define CLO_ENV(i, out, clo) COMMA_IF(i) clo->env[i]
//#define CLO_ARG(i, _) COMMA_IF(i) CAT(arg,i)
#define CLO_ARG(i, ...) COMMA_IF(i) __VA_ARGS__
#define CLO_ARG_ERR(clo) default:\
	fprintf(stderr, "%s line %d: closures can only accept 16 arguments, but found: %d", __FILE__, __LINE__, clo_argc(clo));\
	exit(1);

// use repeater macros to generate a switch dispatching on the number of expected arguments
#define CLO_APPLY_0(out, clo) assert(clo_argr(clo) == 0);\
switch(clo_argc(clo)) {\
EVAL(REPEAT(17, CLO_CASE, 0, out, clo, VA_EMPTY))\
CLO_ARG_ERR(clo)\
}

#define CLO_APPLY_1(out, clo, arg0) assert(clo_argr(clo) == 1);\
switch(clo_argc(clo)-1) {\
EVAL(REPEAT(16, CLO_CASE, out, 1, clo, arg0))\
CLO_ARG_ERR(clo)\
}

#define CLO_APPLY_2(out, clo, arg0, arg1) assert(clo_argr(clo) == 2);\
switch(clo_argc(clo)-2) {\
EVAL(REPEAT(15, CLO_CASE, out, 2, clo, arg0, arg1))\
CLO_ARG_ERR(clo)\
}

#define CLO_APPLY_3(out, clo, arg0, arg1, arg2) assert(clo_argr(clo) == 3);\
switch(clo_argc(clo)-3) {\
EVAL(REPEAT(14, CLO_CASE, 3, out, clo, arg0, arg1, arg2))\
CLO_ARG_ERR(clo)\
}

#define clo_apply4(clo, arg0, arg1, arg2, arg3) (assert(clo_argr(clo) == 4),\
	clo_argc(clo) == 4 ? clo->fn.fn4(arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 5 ? clo->fn.fn5(clo->env[0], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 6 ? clo->fn.fn6(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1, arg2, arg3):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1, arg2, arg3):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0, arg1, arg2, arg3)\
)
#define clo_apply5(clo, arg0, arg1, arg2, arg3, arg4) (assert(clo_argr(clo) == 5),\
	clo_argc(clo) == 5 ? clo->fn.fn5(arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 6 ? clo->fn.fn6(clo->env[0], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 7 ? clo->fn.fn7(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3, arg4):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1, arg2, arg3, arg4):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1, arg2, arg3, arg4)\
)
#define clo_apply6(clo, arg0, arg1, arg2, arg3, arg4, arg5) (assert(clo_argr(clo) == 6),\
	clo_argc(clo) == 6 ? clo->fn.fn6(arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 7 ? clo->fn.fn7(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 8 ? clo->fn.fn8(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4, arg5):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3, arg4, arg5):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1, arg2, arg3, arg4, arg5)\
)
#define clo_apply7(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6) (assert(clo_argr(clo) == 7),\
	clo_argc(clo) == 7 ? clo->fn.fn7(arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 8 ? clo->fn.fn8(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 9 ? clo->fn.fn9(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4, arg5, arg6):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1, arg2, arg3, arg4, arg5, arg6)\
)
#define clo_apply8(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) (assert(clo_argr(clo) == 8),\
	clo_argc(clo) == 8 ? clo->fn.fn8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo_argc(clo) == 9 ? clo->fn.fn9(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo_argc(clo) == 10 ? clo->fn.fn10(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo_argc(clo) == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)\
)
#define clo_apply9(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) (assert(clo_argr(clo) == 9),\
	clo_argc(clo) == 9 ? clo->fn.fn9(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo_argc(clo) == 10 ? clo->fn.fn10(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo_argc(clo) == 11 ? clo->fn.fn11(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)\
)
#define clo_apply10(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) (assert(clo_argr(clo) == 10),\
	clo_argc(clo) == 10 ? clo->fn.fn10(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo_argc(clo) == 11 ? clo->fn.fn11(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)\
)
#define clo_apply11(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) (assert(clo_argr(clo) == 11),\
	clo_argc(clo) == 11 ? clo->fn.fn11(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo_argc(clo) == 12 ? clo->fn.fn12(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)\
)
#define clo_apply12(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) (assert(clo_argr(clo) == 12),\
	clo_argc(clo) == 12 ? clo->fn.fn12(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
	clo_argc(clo) == 13 ? clo->fn.fn13(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)\
)
#define clo_apply13(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) (assert(clo_argr(clo) == 13),\
	clo_argc(clo) == 14 ? clo->fn.fn14(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12):\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12):\
                          clo->fn.fn16(clo->env[0], clo->env[1], clo->env[2], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)\
)
#define clo_apply14(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) (assert(clo_argr(clo) == 14),\
	clo_argc(clo) == 15 ? clo->fn.fn15(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13):\
                          clo->fn.fn16(clo->env[0], clo->env[1], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)\
)
#define clo_apply15(clo, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) (assert(clo_argr(clo) == 15),\
	clo->fn.fn16(clo->env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)\
)


/*
 * Partial application can be a set of macros like apply that simple invoke clo_lift.
 * Or perhaps make them functions?
 */
#define clo_papply1(clo, arg0) (assert(clo_argr(clo) >= 1),\
	clo_argc(clo) == 1 ? clo_lift(clo->fn, clo_argc(clo), 1, arg0):\
	clo_argc(clo) == 2 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], arg0):\
	clo_argc(clo) == 3 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], arg0):\
	clo_argc(clo) == 4 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], arg0):\
	clo_argc(clo) == 5 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0):\
	clo_argc(clo) == 6 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0):\
	clo_argc(clo) == 7 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0):\
	clo_argc(clo) == 8 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0):\
	clo_argc(clo) == 9 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0):\
	clo_argc(clo) == 10 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0):\
	clo_argc(clo) == 11 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0):\
	clo_argc(clo) == 12 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0):\
	clo_argc(clo) == 13 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0):\
	clo_argc(clo) == 14 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], arg0):\
	clo_argc(clo) == 15 ? clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], arg0):\
					  clo_lift(clo->fn, clo_argc(clo), 1 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], clo->env[14], arg0):\
)
#define clo_papply2(clo, arg0, arg1) (assert(clo_argr(clo) >= 2),\
	clo_argc(clo) == 2 ? clo_lift(clo->fn, clo_argc(clo), 2, arg0, arg1):\
	clo_argc(clo) == 3 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], arg0, arg1):\
	clo_argc(clo) == 4 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], arg0, arg1):\
	clo_argc(clo) == 5 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], arg0, arg1):\
	clo_argc(clo) == 6 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], arg0, arg1):\
	clo_argc(clo) == 7 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], arg0, arg1):\
	clo_argc(clo) == 8 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], arg0, arg1):\
	clo_argc(clo) == 9 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], arg0, arg1):\
	clo_argc(clo) == 10 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], arg0, arg1):\
	clo_argc(clo) == 11 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], arg0, arg1):\
	clo_argc(clo) == 12 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], arg0, arg1):\
	clo_argc(clo) == 13 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], arg0, arg1):\
	clo_argc(clo) == 14 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], arg0, arg1):\
	clo_argc(clo) == 15 ? clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], arg0, arg1):\
					  clo_lift(clo->fn, clo_argc(clo), 2 + clo->argn, clo->env[0], clo->env[1], clo->env[2], clo->env[3], clo->env[4], clo->env[5], clo->env[6], clo->env[7], clo->env[8], clo->env[9], clo->env[10], clo->env[11], clo->env[12], clo->env[13], arg0, arg1):\
)
//...

/*
 * Compose two closures with the given argument counts.
 */
//clo_t clo_compose(clo_t f, unsigned fargc, clo_t g, unsigned gargc);

//#define clo_lift0(fn) clo_lift({ fn }, { 0 }, 0)
//#define clo_lift1(fn, arg0) clo_lift({ fn }, struct { arg0 }, sizeof(val_t))
//#define clo_lift2(fn, arg0) clo_lift({ fn }, { arg0 }, 2 * sizeof(val_t))

#endif /* __CLOSURE_H__ */
