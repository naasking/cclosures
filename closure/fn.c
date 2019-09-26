/*
 * Closure combinators.
 */

#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <errno.h>

#include "fn.h"

fn* fn_init(fn* c, fp f, unsigned argr, unsigned argn, ...) {
	if (argr + argn > FN_ARGS_MAX) {
		errno = E2BIG;
		return NULL;
	}
	va_list args;
	va_start(args, argn);
	c->f = f;
	c->argp = argn;
	c->argr = argr;
	val *env = &c->env;
	for (int i = 0; i < argn; ++i)
		env[i] = va_arg(args, val);
	va_end(args);
	//val x;
	//x.fn = c;
	//return x;
	return c;
}

val fn_papp(fn* f, unsigned argn) {
	/*if (argn + f->argp > FN_ARGS_MAX) {
		errno = E2BIG;
		return NULL;
	}*/
	fn* x = (fn*)malloc(sizeof(fn) + (argn + f->argp - 1) * sizeof(val));
	val *fenv = &f->env, *xenv = &x->env;
	x->argr = f->argr - argn;
	x->argp = f->argp + argn;
	//memcpy(&x->env, f->env, sizeof(val) * f->argp);
	switch (f->argp) {
	default:
		fprintf(stderr, "fn_papp: required %d args but called with %d\r\n", f->argr, argn + f->argp);
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
	val y = { x };
	return y;
}
