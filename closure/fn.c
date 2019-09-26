#include "fn.h"

fnx* fnx_papp(fnx* f, unsigned argn) {
	fnx* x = (fnx*)malloc(sizeof(fnx) + (f->fn2.envc - 1) * sizeof(val));
	val *fenv = &f->fn2.env, *xenv = &x->fn2.env;
	x->fn2.envc = f->fn2.envc + argn;
	switch (f->fn2.envc) {
	default:
		fprintf(stderr, "fnx_papp: invalid environment size %d\r\n", f->fn2.envc);
		abort();
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
