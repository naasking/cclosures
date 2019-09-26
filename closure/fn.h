#ifndef FN_H
#define FN_H

#define VAL_EXTRA \
fn8* fn8; \
fn7* fn7; \
fn3* fn3; \
fn2* fn2; \
fn1* fn1;
#include "val.h"


#ifndef fn_fail
#include <stdio.h>
#include <stdlib.h>
#define fn_fail(argn) \
fprintf(stderr, "%s: required %d args but called with %d\r\n", __func__, f->envc, argn); \
abort()
#endif

/*
 * The closure types.
 */
typedef struct {
	unsigned envc;
	union {
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn8;

typedef struct {
	unsigned envc;
	union {
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn7;

typedef struct {
	unsigned envc;
	union {
		val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn6;

typedef struct {
	unsigned envc;
	union {
		val(*fn5)(val arg0, val arg1, val arg2, val arg3, val arg4);
		val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn5;

typedef struct {
	unsigned envc;
	union {
		val(*fn4)(val arg0, val arg1, val arg2, val arg3);
		val(*fn5)(val arg0, val arg1, val arg2, val arg3, val arg4);
		val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn4;

typedef struct {
	unsigned envc;
	union {
		val(*fn3)(val arg0, val arg1, val arg2);
		val(*fn4)(val arg0, val arg1, val arg2, val arg3);
		val(*fn5)(val arg0, val arg1, val arg2, val arg3, val arg4);
		val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn3;

typedef struct {
	unsigned envc;
	union {
		val(*fn2)(val arg0, val arg1);
		val(*fn3)(val arg0, val arg1, val arg2);
		val(*fn4)(val arg0, val arg1, val arg2, val arg3);
		val(*fn5)(val arg0, val arg1, val arg2, val arg3, val arg4);
		val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn2;

typedef struct {
	unsigned envc;
	union {
		val(*fn1)(val arg0);
		val(*fn2)(val arg0, val arg1);
		val(*fn3)(val arg0, val arg1, val arg2);
		val(*fn4)(val arg0, val arg1, val arg2, val arg3);
		val(*fn5)(val arg0, val arg1, val arg2, val arg3, val arg4);
		val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn1;

typedef struct {
	unsigned envc;
	union {
		val(*fn0)();
		val(*fn1)(val arg0);
		val(*fn2)(val arg0, val arg1);
		val(*fn3)(val arg0, val arg1, val arg2);
		val(*fn4)(val arg0, val arg1, val arg2, val arg3);
		val(*fn5)(val arg0, val arg1, val arg2, val arg3, val arg4);
		val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
		val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
		val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
	};
	val env;  /* environment entries start here */
} fn0;

/* union of all function types */
typedef union {
	fn8 fn8;
	fn7 fn7;
	fn6 fn6;
	fn5 fn5;
	fn4 fn4;
	fn3 fn3;
	fn2 fn2;
	fn1 fn1;
	fn0 fn0;
} fnx;

/**
 * Call an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: the value returned by the enclosed function.
 */
inline val fn8_call(fn8* f, val x0, val x1, val x2, val x3, val x4, val x5, val x6, val x7) {
	return f->fn8(x0, x1, x2, x3, x4, x5, x6, x7);
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 7 argument function.
 */
inline fn7* fn8_wrap1(fn8* f, val x0) {
	fnx* tmp = { f }, *x = fnx_papp(tmp, 1);
	x->fn7.env = x0;
	return &x->fn7;
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 6 argument function.
 */
inline fn6* fn8_wrap2(fn8* f, val x0, val x1) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 2);
	fn6* x = &fn->fn6;
	(&x->env)[0] = x0;
	(&x->env)[1] = x1;
	return x;
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 5 argument function.
 */
inline fn5* fn8_wrap3(fn8* f, val x0, val x1, val x2) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn6* x = &fn->fn6;
	(&x->env)[0] = x0;
	(&x->env)[1] = x1;
	(&x->env)[2] = x2;
	return x;
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 4 argument function.
 */
inline fn4* fn8_wrap4(fn8* f, val x0, val x1, val x2, val x3) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn5* x = &fn->fn5;
	(&x->env)[0] = x0;
	(&x->env)[1] = x1;
	(&x->env)[2] = x2;
	(&x->env)[3] = x3;
	return x;
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn3* fn8_wrap5(fn8* f, val x0, val x1, val x2, val x3, val x4) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 5);
	fn3* x = &fn->fn3;
	(&x->env)[0] = x0;
	(&x->env)[1] = x1;
	(&x->env)[2] = x2;
	(&x->env)[3] = x3;
	(&x->env)[4] = x4;
	return x;
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 2 argument function.
 */
inline fn2* fn8_wrap6(fn8* f, val x0, val x1, val x2, val x3, val x4, val x5) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 6);
	fn2* x = &fn->fn2;
	(&x->env)[0] = x0;
	(&x->env)[1] = x1;
	(&x->env)[2] = x2;
	(&x->env)[3] = x3;
	(&x->env)[4] = x4;
	(&x->env)[5] = x5;
	return x;
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 1 argument function.
 */
inline fn1* fn8_wrap7(fn8* f, val x0, val x1, val x2, val x3, val x4, val x5, val x6) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 7);
	fn1* x = &fn->fn1;
	(&x->env)[0] = x0;
	(&x->env)[1] = x1;
	(&x->env)[2] = x2;
	(&x->env)[3] = x3;
	(&x->env)[4] = x4;
	(&x->env)[5] = x5;
	(&x->env)[6] = x6;
	return x;
}

/**
 * Partially apply an 8-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 1 argument function.
 */
inline fn0* fn8_wrap8(fn8* f, val x0, val x1, val x2, val x3, val x4, val x5, val x6, val x7) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 8);
	fn1* x = &fn->fn1;
	(&x->env)[0] = x0;
	(&x->env)[1] = x1;
	(&x->env)[2] = x2;
	(&x->env)[3] = x3;
	(&x->env)[4] = x4;
	(&x->env)[5] = x5;
	(&x->env)[6] = x6;
	(&x->env)[7] = x7;
	return x;
}


/**
 * Call a 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 6 argument function.
 */
inline val fn7_call(fn7* f, val x0, val x1, val x2, val x3, val x4, val x5, val x6) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn7(x0, x1, x2, x3, x4, x5, x6);
	case 1: return f->fn8(env[0], x0, x1, x2, x3, x4, x5, x6);
	default:
		fn_fail(6);
	}
}

/**
 * Partially apply an 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 6 argument function.
 */
inline fn6* fn7_wrap1(fn7* f, val x0) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 1);
	fn6* x = &fn->fn6;
	(&x->env)[f->envc] = x0;
	return &x->fn6;
}

/**
 * Partially apply an 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 5 argument function.
 */
inline fn5* fn7_wrap2(fn7* f, val x0, val x1) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 2);
	fn5* x = &fn->fn5;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	return x;
}

/**
 * Partially apply an 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 4 argument function.
 */
inline fn4* fn7_wrap3(fn7* f, val x0, val x1, val x2) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn4* x = &fn->fn4;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	return x;
}

/**
 * Partially apply an 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn3* fn7_wrap4(fn7* f, val x0, val x1, val x2, val x3) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn3* x = &fn->fn3;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	return x;
}

/**
 * Partially apply an 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 2 argument function.
 */
inline fn2* fn7_wrap5(fn7* f, val x0, val x1, val x2, val x3, val x4) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 5);
	fn2* x = &fn->fn2;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	(&x->env)[f->envc + 4] = x4;
	return x;
}

/**
 * Partially apply an 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 1 argument function.
 */
inline fn1* fn7_wrap6(fn7* f, val x0, val x1, val x2, val x3, val x4, val x5) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 6);
	fn1* x = &fn->fn1;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	(&x->env)[f->envc + 4] = x4;
	(&x->env)[f->envc + 5] = x5;
	return x;
}

/**
 * Partially apply an 7-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 0 argument function.
 */
inline fn0* fn7_wrap7(fn7* f, val x0, val x1, val x2, val x3, val x4, val x5, val x6) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 6);
	fn0* x = &fn->fn0;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	(&x->env)[f->envc + 4] = x4;
	(&x->env)[f->envc + 5] = x5;
	return x;
}




/**
 * Call a 6-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: value from applying the function.
 */
inline val fn6_call(fn6* f, val x0, val x1, val x2, val x3, val x4, val x5) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn6(x0, x1, x2, x3, x4, x5);
	case 1: return f->fn7(env[0], x0, x1, x2, x3, x4, x5);
	case 2: return f->fn8(env[0], env[1], x0, x1, x2, x3, x4, x5);
	default:
		fn_fail(6);
	}
}

/**
 * Partially apply an 6-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 5 argument function.
 */
inline fn5* fn6_wrap1(fn6* f, val x0) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 1);
	fn5* x = &fn->fn5;
	(&x->env)[f->envc] = x0;
	return &x->fn5;
}

/**
 * Partially apply an 6-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 4 argument function.
 */
inline fn4* fn6_wrap2(fn6* f, val x0, val x1) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 2);
	fn4* x = &fn->fn4;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	return x;
}

/**
 * Partially apply an 6-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn3* fn6_wrap3(fn6* f, val x0, val x1, val x2) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn3* x = &fn->fn3;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	return x;
}

/**
 * Partially apply an 6-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 2 argument function.
 */
inline fn2* fn6_wrap4(fn6* f, val x0, val x1, val x2, val x3) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn2* x = &fn->fn2;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	return x;
}

/**
 * Partially apply an 6-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 1 argument function.
 */
inline fn1* fn6_wrap5(fn6* f, val x0, val x1, val x2, val x3, val x4) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 5);
	fn1* x = &fn->fn1;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	(&x->env)[f->envc + 4] = x4;
	return x;
}

/**
 * Partially apply an 6-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 0 argument function.
 */
inline fn0* fn6_wrap6(fn6* f, val x0, val x1, val x2, val x3, val x4, val x5) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 6);
	fn0* x = &fn->fn0;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	(&x->env)[f->envc + 4] = x4;
	(&x->env)[f->envc + 5] = x5;
	return x;
}


/**
 * Call a 5-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: value from applying the function.
 */
inline val fn5_call(fn5* f, val x0, val x1, val x2, val x3, val x4) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn5(x0, x1, x2, x3, x4);
	case 1: return f->fn5(env[0], x0, x1, x2, x3, x4);
	case 2: return f->fn7(env[0], env[1], x0, x1, x2, x3, x4);
	case 3: return f->fn8(env[0], env[1], env[2], x0, x1, x2, x3, x4);
	default:
		fn_fail(5);
	}
}

/**
 * Partially apply an 5-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 4 argument function.
 */
inline fn4* fn5_wrap1(fn5* f, val x0) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 1);
	fn4* x = &fn->fn4;
	(&x->env)[f->envc] = x0;
	return &x->fn4;
}

/**
 * Partially apply an 5-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 4 argument function.
 */
inline fn3* fn5_wrap2(fn5* f, val x0, val x1) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 2);
	fn3* x = &fn->fn3;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	return x;
}

/**
 * Partially apply an 5-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn2* fn5_wrap3(fn5* f, val x0, val x1, val x2) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn2* x = &fn->fn2;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	return x;
}

/**
 * Partially apply an 5-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 2 argument function.
 */
inline fn1* fn5_wrap4(fn5* f, val x0, val x1, val x2, val x3) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn1* x = &fn->fn1;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	return x;
}

/**
 * Partially apply an 5-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 1 argument function.
 */
inline fn0* fn5_wrap5(fn5* f, val x0, val x1, val x2, val x3, val x4) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 5);
	fn0* x = &fn->fn0;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	(&x->env)[f->envc + 4] = x4;
	return x;
}

/**
 * Call a 4-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: value from applying the function.
 */
inline val fn4_call(fn4* f, val x0, val x1, val x2, val x3) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn4(x0, x1, x2, x3);
	case 1: return f->fn5(env[0], x0, x1, x2, x3);
	case 2: return f->fn6(env[0], env[1], x0, x1, x2, x3);
	case 3: return f->fn7(env[0], env[1], env[2], x0, x1, x2, x3);
	case 4: return f->fn8(env[0], env[1], env[2], env[3], x0, x1, x2, x3);
	default:
		fn_fail(4);
	}
}

/**
 * Partially apply an 4-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 4 argument function.
 */
inline fn3* fn4_wrap1(fn4* f, val x0) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 1);
	fn3* x = &fn->fn3;
	(&x->env)[f->envc] = x0;
	return &x->fn4;
}

/**
 * Partially apply an 4-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 4 argument function.
 */
inline fn2* fn4_wrap2(fn4* f, val x0, val x1) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 2);
	fn2* x = &fn->fn2;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	return x;
}

/**
 * Partially apply an 4-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn1* fn4_wrap3(fn4* f, val x0, val x1, val x2) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn1* x = &fn->fn1;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	return x;
}

/**
 * Partially apply an 4-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 2 argument function.
 */
inline fn0* fn4_wrap4(fn4* f, val x0, val x1, val x2, val x3) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn0* x = &fn->fn0;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	(&x->env)[f->envc + 3] = x3;
	return x;
}

/**
 * Call a 3-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: value from applying the function.
 */
inline val fn3_call(fn3* f, val x0, val x1, val x2) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn3(x0, x1, x2);
	case 1: return f->fn4(env[0], x0, x1, x2);
	case 2: return f->fn5(env[0], env[1], x0, x1, x2);
	case 3: return f->fn6(env[0], env[1], env[2], x0, x1, x2);
	case 4: return f->fn7(env[0], env[1], env[2], env[3], x0, x1, x2);
	case 5: return f->fn8(env[0], env[1], env[2], env[3], env[4], x0, x1, x2);
	default:
		fn_fail(3);
	}
}

/**
 * Partially apply an 3-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn2* fn3_wrap1(fn3* f, val x0) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 1);
	fn2* x = &fn->fn2;
	(&x->env)[f->envc] = x0;
	return &x->fn3;
}

/**
 * Partially apply an 3-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn1* fn3_wrap2(fn3* f, val x0, val x1) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 2);
	fn1* x = &fn->fn1;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	return x;
}

/**
 * Partially apply an 3-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 3 argument function.
 */
inline fn0* fn3_wrap3(fn3* f, val x0, val x1, val x2) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 3);
	fn0* x = &fn->fn0;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	(&x->env)[f->envc + 2] = x2;
	return x;
}


/**
 * Call a 2-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: value from applying the function.
 */
inline val fn2_call(fn2* f, val x0, val x1) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn2(x0, x1);
	case 1: return f->fn3(env[0], x0, x1);
	case 2: return f->fn4(env[0], env[1], x0, x1);
	case 3: return f->fn5(env[0], env[1], env[2], x0, x1);
	case 4: return f->fn6(env[0], env[1], env[2], env[3], x0, x1);
	case 5: return f->fn7(env[0], env[1], env[2], env[3], env[4], x0, x1);
	case 6: return f->fn8(env[0], env[1], env[2], env[3], env[4], env[5], x0, x1);
	default:
		fn_fail(2);
	}
}

/**
 * Partially apply an 2-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 2 argument function.
 */
inline fn2* fn2_wrap1(fn2* f, val x0) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 1);
	fn2* x = &fn->fn2;
	(&x->env)[f->envc] = x0;
	return &x->fn2;
}

/**
 * Partially apply an 2-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 2 argument function.
 */
inline fn1* fn2_wrap2(fn2* f, val x0, val x1) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 2);
	fn1* x = &fn->fn1;
	(&x->env)[f->envc] = x0;
	(&x->env)[f->envc + 1] = x1;
	return x;
}


/**
 * Call a 1-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: value from applying the function.
 */
inline val fn1_call(fn1* f, val x0) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn1(x0);
	case 1: return f->fn2(env[0], x0);
	case 2: return f->fn3(env[0], env[1], x0);
	case 3: return f->fn4(env[0], env[1], env[2], x0);
	case 4: return f->fn5(env[0], env[1], env[2], env[3], x0);
	case 5: return f->fn6(env[0], env[1], env[2], env[3], env[4], x0);
	case 6: return f->fn7(env[0], env[1], env[2], env[3], env[4], env[5], x0);
	case 7: return f->fn8(env[0], env[1], env[2], env[3], env[4], env[5], env[6], x0);
	default:
		fn_fail(1);
	}
}

/**
 * Partially apply an 1-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: a 0 argument function.
 */
inline fn0* fn1_wrap1(fn1* f, val x0) {
	fnx* tmp = { f }, *fn = fnx_papp(tmp, 1);
	fn0* x = &fn->fn0;
	(&x->env)[f->envc] = x0;
	return &x->fn2;
}


/**
 * Call a 1-argument function.
 *
 * f: the function to call.
 * xN: the Nth argument.
 * returns: value from applying the function.
 */
inline val fn0_call(fn0* f) {
	val *env = &f->env;
	switch (f->envc) {
	case 0: return f->fn0();
	case 1: return f->fn1(env[0]);
	case 2: return f->fn2(env[0], env[1]);
	case 3: return f->fn3(env[0], env[1], env[2]);
	case 4: return f->fn4(env[0], env[1], env[2], env[3]);
	case 5: return f->fn5(env[0], env[1], env[2], env[3], env[4]);
	case 6: return f->fn6(env[0], env[1], env[2], env[3], env[4], env[5]);
	case 7: return f->fn7(env[0], env[1], env[2], env[3], env[4], env[5], env[6]);
	case 8: return f->fn8(env[0], env[1], env[2], env[3], env[4], env[5], env[6], env[7]);
	default:
		fn_fail(0);
	}
}

#endif