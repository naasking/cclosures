#include "fn.h"

fnx fnx_papp(fnx f, unsigned argn) {
	fnx x = { { (fn8*)malloc(sizeof(fn8) + (f.fn->envc - 1) * sizeof(val)) } };
	val *fenv = &f.fn8->env, *xenv = &x.fn8->env;
	x.fn->envc = f.fn->envc + argn;
	switch (f.fn2->envc) {
	default:
		fn_fail(x.fn->envc, argn);
	case 8: xenv[7] = fenv[7];
	case 7: xenv[6] = fenv[6];
	case 6: xenv[5] = fenv[5];
	case 5: xenv[4] = fenv[4];
	case 4: xenv[3] = fenv[3];
	case 3: xenv[2] = fenv[2];
	case 2: xenv[1] = fenv[1];
	case 1: xenv[0] = fenv[0];
	}
	return x;
}
