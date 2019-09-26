#ifndef FN_H
#define FN_H

/**
 * = Curried Functions for C =
 *
 * This implements eval/apply style closures for C based around a universal value type 'val',
 * which is currently defined to be machine word-sized.
 */

#include <stdio.h>
#include <stdlib.h>
#include "val.h"

/*
 * The type of all closures. The first arg is a structure pointer for multiargument functions.
 */
typedef union {
	val(*fn0)();
	val(*fn1)(val arg0);
	val(*fn2)(val arg0, val arg1);
	val(*fn3)(val arg0, val arg1, val arg2);
	val(*fn4)(val arg0, val arg1, val arg2, val arg3);
	val(*fn5)(val arg0, val arg1, val arg2, val arg3, val arg4);
	val(*fn6)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5);
	val(*fn7)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6);
	val(*fn8)(val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7);
} fp;

/*
 * The closure type.
 */
typedef struct fn {
	union {
		unsigned argr : 3;
		unsigned argp : 3;
	};
	fp f;	   /* function to apply */
	val env;  /* environment entries start here */
} fn;

/*
 * The maximum number of arguments.
 */
#define FN_ARGS_MAX 8

#ifndef fn_fail
#define fn_fail(argn) \
fprintf(stderr, "%s: required %d args but called with %d\r\n", __func__, f->argr, argn); \
abort()
#endif

/*
 * Initialize an existing closure record with the given arguments.
 *
 * ERROR: returns E2BIG if argc exceeds the CLO_ARGS_MAX.
 */
extern fn* fn_init(fn* c, fp f, unsigned argc, unsigned argn, ...);

/**
 * Partially apply a function with the given number of new arguments.
 */
extern val fn_papp(fn* f, unsigned argn);

inline val fn_call0(fn* f) {
	val *env = &f->env;
	switch ((f->argr << 3) | f->argp) {
	case 0: return f->f.fn0();
	case 1: return f->f.fn1(env[0]);
	case 2: return f->f.fn2(env[0], env[1]);
	case 3: return f->f.fn3(env[0], env[1], env[2]);
	case 4: return f->f.fn4(env[0], env[1], env[2], env[3]);
	case 5: return f->f.fn5(env[0], env[1], env[2], env[3], env[4]);
	case 6: return f->f.fn6(env[0], env[1], env[2], env[3], env[4], env[5]);
	case 7: return f->f.fn7(env[0], env[1], env[2], env[3], env[4], env[5], env[6]);
	case 8: return f->f.fn8(env[0], env[1], env[2], env[3], env[4], env[5], env[6], env[7]);
	default:
		fn_fail(0);
	}
}

inline val fn_call1(fn* f, val arg0) {
	val *env = &f->env;
	switch (((f->argr - 1) << 3) | f->argp) {
	case 0: return f->f.fn1(arg0);
	case 1: return f->f.fn2(env[0], arg0);
	case 2: return f->f.fn3(env[0], env[1], arg0);
	case 3: return f->f.fn4(env[0], env[1], env[2], arg0);
	case 4: return f->f.fn5(env[0], env[1], env[2], env[3], arg0);
	case 5: return f->f.fn6(env[0], env[1], env[2], env[3], env[4], arg0);
	case 6: return f->f.fn7(env[0], env[1], env[2], env[3], env[4], env[5], arg0);
	case 7: return f->f.fn8(env[0], env[1], env[2], env[3], env[4], env[5], env[6], arg0);
	default:
		if (f->argr > 1) {
			// partial application: lift argX to env and return lambda
			val x = fn_papp(f, f->argp + 1);
			(&x.fn->env)[f->argp] = arg0;
			return x;
		} else if (f->argr == 0) {
			// over-application: apply as many arguments as possible
			return fn_call1(fn_call0(f).fn, arg0);
		} else {
			fn_fail(1);
		}
	}
}

inline val fn_call2(fn* f, val arg0, val arg1) {
	val *env = &f->env;
	switch (((f->argr - 2) << 3) | f->argp) {
	case 0: return f->f.fn2(arg0, arg1);
	case 1: return f->f.fn3(env[0], arg0, arg1);
	case 2: return f->f.fn4(env[0], env[1], arg0, arg1);
	case 3: return f->f.fn5(env[0], env[1], env[2], arg0, arg1);
	case 4: return f->f.fn6(env[0], env[1], env[2], env[3], arg0, arg1);
	case 5: return f->f.fn7(env[0], env[1], env[2], env[3], env[4], arg0, arg1);
	case 6: return f->f.fn8(env[0], env[1], env[2], env[3], env[4], env[5], arg0, arg1);
	default:
		if (f->argr > 2) {
			val x = fn_papp(f, f->argp + 1);
			(&x.fn->env)[f->argp] = arg0;
			(&x.fn->env)[f->argp + 1] = arg1;
			return x;
		} else {
			// over-application: apply as many arguments as possible
			switch (f->argr) {
			case 0: return fn_call2(fn_call0(f).fn, arg0, arg1);
			case 1: return fn_call1(fn_call1(f, arg0).fn, arg1);
			default:
				fn_fail(2);
			}
		}
	}
}

inline val fn_call3(fn* f, val arg0, val arg1, val arg2) {
	val *env = &f->env;
	switch (((f->argr - 3) << 3) | f->argp) {
	case 0: return f->f.fn3(arg0, arg1, arg2);
	case 1: return f->f.fn4(env[0], arg0, arg1, arg2);
	case 2: return f->f.fn5(env[0], env[1], arg0, arg1, arg2);
	case 3: return f->f.fn6(env[0], env[1], env[2], arg0, arg1, arg2);
	case 4: return f->f.fn7(env[0], env[1], env[2], env[3], arg0, arg1, arg2);
	case 5: return f->f.fn8(env[0], env[1], env[2], env[3], env[4], arg0, arg1, arg2);
	default:
		if (f->argr > 3) {
			val x = fn_papp(f, f->argp + 1);
			(&x.fn->env)[f->argp] = arg0;
			(&x.fn->env)[f->argp + 1] = arg1;
			(&x.fn->env)[f->argp + 2] = arg2;
			return x;
		} else {
			// over-application: apply as many arguments as possible
			switch (f->argr) {
			case 0: return fn_call3(fn_call0(f).fn, arg0, arg1, arg2);
			case 1: return fn_call2(fn_call1(f, arg0).fn, arg1, arg2);
			case 2: return fn_call1(fn_call2(f, arg0, arg1).fn, arg2);
			default:
				fn_fail(3);
			}
		}
	}
}

inline val fn_call4(fn* f, val arg0, val arg1, val arg2, val arg3) {
	val *env = &f->env;
	switch (((f->argr - 4) << 3) | f->argp) {
	case 0: return f->f.fn4(arg0, arg1, arg2, arg3);
	case 1: return f->f.fn5(env[0], arg0, arg1, arg2, arg3);
	case 2: return f->f.fn6(env[0], env[1], arg0, arg1, arg2, arg3);
	case 3: return f->f.fn7(env[0], env[1], env[2], arg0, arg1, arg2, arg3);
	case 4: return f->f.fn8(env[0], env[1], env[2], env[3], arg0, arg1, arg2, arg3);
	default:
		if (f->argr > 4) {
			val x = fn_papp(f, f->argp + 1);
			(&x.fn->env)[f->argp] = arg0;
			(&x.fn->env)[f->argp + 1] = arg1;
			(&x.fn->env)[f->argp + 2] = arg2;
			(&x.fn->env)[f->argp + 3] = arg3;
			return x;
		} else {
			// over-application: apply as many arguments as possible
			switch (f->argr) {
			case 0: return fn_call4(fn_call0(f).fn, arg0, arg1, arg2, arg3);
			case 1: return fn_call3(fn_call1(f, arg0).fn, arg1, arg2, arg3);
			case 2: return fn_call2(fn_call2(f, arg0, arg1).fn, arg2, arg3);
			case 3: return fn_call1(fn_call3(f, arg0, arg1, arg2).fn, arg3);
			default:
				fn_fail(4);
			}
		}
	}
}

inline val fn_call5(fn* f, val arg0, val arg1, val arg2, val arg3, val arg4) {
	val *env = &f->env;
	switch (((f->argr - 5) << 3) | f->argp) {
	case 0: return f->f.fn5(arg0, arg1, arg2, arg3, arg4);
	case 1: return f->f.fn6(env[0], arg0, arg1, arg2, arg3, arg4);
	case 2: return f->f.fn7(env[0], env[1], arg0, arg1, arg2, arg3, arg4);
	case 3: return f->f.fn8(env[0], env[1], env[2], arg0, arg1, arg2, arg3, arg4);
	default:
		if (f->argr > 5) {
			val x = fn_papp(f, f->argp + 1);
			(&x.fn->env)[f->argp] = arg0;
			(&x.fn->env)[f->argp + 1] = arg1;
			(&x.fn->env)[f->argp + 2] = arg2;
			(&x.fn->env)[f->argp + 3] = arg3;
			(&x.fn->env)[f->argp + 4] = arg4;
			return x;
		} else {
			// over-application: apply as many arguments as possible
			switch (f->argr) {
			case 0: return fn_call5(fn_call0(f).fn, arg0, arg1, arg2, arg3, arg4);
			case 1: return fn_call4(fn_call1(f, arg0).fn, arg1, arg2, arg3, arg4);
			case 2: return fn_call3(fn_call2(f, arg0, arg1).fn, arg2, arg3, arg4);
			case 3: return fn_call2(fn_call3(f, arg0, arg1, arg2).fn, arg3, arg4);
			case 4: return fn_call1(fn_call4(f, arg0, arg1, arg2, arg3).fn, arg4);
			default:
				fn_fail(5);
			}
		}
	}
}

inline val fn_call6(fn* f, val arg0, val arg1, val arg2, val arg3, val arg4, val arg5) {
	val *env = &f->env;
	switch (((f->argr - 6) << 3) | f->argp) {
	case 0: return f->f.fn6(arg0, arg1, arg2, arg3, arg4, arg5);
	case 1: return f->f.fn7(env[0], arg0, arg1, arg2, arg3, arg4, arg5);
	case 2: return f->f.fn8(env[0], env[1], arg0, arg1, arg2, arg3, arg4, arg5);
	default:
		if (f->argr > 6) {
			val x = fn_papp(f, f->argp + 1);
			(&x.fn->env)[f->argp] = arg0;
			(&x.fn->env)[f->argp + 1] = arg1;
			(&x.fn->env)[f->argp + 2] = arg2;
			(&x.fn->env)[f->argp + 3] = arg3;
			(&x.fn->env)[f->argp + 4] = arg4;
			(&x.fn->env)[f->argp + 5] = arg5;
			return x;
		} else {
			// over-application: apply as many arguments as possible
			switch (f->argr) {
			case 0: return fn_call6(fn_call0(f).fn, arg0, arg1, arg2, arg3, arg4, arg5);
			case 1: return fn_call5(fn_call1(f, arg0).fn, arg1, arg2, arg3, arg4, arg5);
			case 2: return fn_call4(fn_call2(f, arg0, arg1).fn, arg2, arg3, arg4, arg5);
			case 3: return fn_call3(fn_call3(f, arg0, arg1, arg2).fn, arg3, arg4, arg5);
			case 4: return fn_call2(fn_call4(f, arg0, arg1, arg2, arg3).fn, arg4, arg5);
			case 5: return fn_call1(fn_call5(f, arg0, arg1, arg2, arg3, arg4).fn, arg5);
			default:
				fn_fail(6);
			}
		}
	}
}

inline val fn_call7(fn* f, val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6) {
	val *env = &f->env;
	switch (((f->argr - 7) << 3) | f->argp) {
	case 0: return f->f.fn7(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	case 1: return f->f.fn8(env[0], arg0, arg1, arg2, arg3, arg4, arg5, arg6);
	default:
		//FIXME: 
		if (f->argr > 7) {
			val x = fn_papp(f, f->argp + 1);
			(&x.fn->env)[f->argp] = arg0;
			(&x.fn->env)[f->argp + 1] = arg1;
			(&x.fn->env)[f->argp + 2] = arg2;
			(&x.fn->env)[f->argp + 3] = arg3;
			(&x.fn->env)[f->argp + 4] = arg4;
			(&x.fn->env)[f->argp + 5] = arg5;
			(&x.fn->env)[f->argp + 6] = arg6;
			return x;
		} else {
			// over-application: apply as many arguments as possible
			//FIXME: tmp closure needs to be cleaned up?
			val tmp, x;
			switch (f->argr) {
			case 0: x = fn_call7((tmp = fn_call0(f)).fn, arg0, arg1, arg2, arg3, arg4, arg5, arg6); break;
			case 1: x = fn_call6((tmp = fn_call1(f, arg0)).fn, arg1, arg2, arg3, arg4, arg5, arg6); break;
			case 2: x = fn_call5((tmp = fn_call2(f, arg0, arg1)).fn, arg2, arg3, arg4, arg5, arg6); break;
			case 3: x = fn_call4((tmp = fn_call3(f, arg0, arg1, arg2)).fn, arg3, arg4, arg5, arg6); break;
			case 4: x = fn_call3((tmp = fn_call4(f, arg0, arg1, arg2, arg3)).fn, arg4, arg5, arg6); break;
			case 5: x = fn_call2((tmp = fn_call5(f, arg0, arg1, arg2, arg3, arg4)).fn, arg5, arg6); break;
			case 6: x = fn_call1((tmp = fn_call6(f, arg0, arg1, arg2, arg3, arg4, arg5)).fn, arg6); break;
			default:
				fn_fail(7);
			}
			free(tmp.fn);
			return x;
		}
	}
}

inline val fn_call8(fn* f, val arg0, val arg1, val arg2, val arg3, val arg4, val arg5, val arg6, val arg7) {
	//val *env = &f->env;
	if (!((f->argr - 8) << 3) && f->argp == 0) {
		return f->f.fn8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	} else if (f->argr > 8) {
		val x = fn_papp(f, f->argp + 1);
		(&x.fn->env)[f->argp] = arg0;
		(&x.fn->env)[f->argp + 1] = arg1;
		(&x.fn->env)[f->argp + 2] = arg2;
		(&x.fn->env)[f->argp + 3] = arg3;
		(&x.fn->env)[f->argp + 4] = arg4;
		(&x.fn->env)[f->argp + 5] = arg5;
		(&x.fn->env)[f->argp + 6] = arg6;
		(&x.fn->env)[f->argp + 7] = arg7;
		return x;
	} else {
		// over-application: apply as many arguments as possible
		//FIXME: tmp closure needs to be cleaned up?
		val tmp, x;
		switch (f->argr) {
		case 0: x = fn_call8((tmp = fn_call0(f)).fn, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); break;
		case 1: x = fn_call7((tmp = fn_call1(f, arg0)).fn, arg1, arg2, arg3, arg4, arg5, arg6, arg7); break;
		case 2: x = fn_call6((tmp = fn_call2(f, arg0, arg1)).fn, arg2, arg3, arg4, arg5, arg6, arg7); break;
		case 3: x = fn_call5((tmp = fn_call3(f, arg0, arg1, arg2)).fn, arg3, arg4, arg5, arg6, arg7); break;
		case 4: x = fn_call4((tmp = fn_call4(f, arg0, arg1, arg2, arg3)).fn, arg4, arg5, arg6, arg7); break;
		case 5: x = fn_call3((tmp = fn_call5(f, arg0, arg1, arg2, arg3, arg4)).fn, arg5, arg6, arg7); break;
		case 6: x = fn_call2((tmp = fn_call6(f, arg0, arg1, arg2, arg3, arg4, arg5)).fn, arg6, arg7); break;
		case 7: x = fn_call1((tmp = fn_call7(f, arg0, arg1, arg2, arg3, arg4, arg5, arg6)).fn, arg7); break;
		default:
			fn_fail(8);
		}
		free(tmp.fn);
		return x;
	}
}

#endif /* FN_H */
