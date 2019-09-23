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
	if (argn + f->argp > FN_ARGS_MAX) {
		errno = E2BIG;
		return NULL;
	}
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

//fn* fn_new(fp f, unsigned argr, unsigned argn, ...) {
//	if (argc > FN_ARGS_MAX) {
//		errno = E2BIG;
//		return NULL;
//	}
//	va_list args;
//	va_start(args, argn);
//	fn* c = (fn*)malloc(sizeof(fn) + (argn - 1) * sizeof(val));
//	c->f = f;
//	c->argr = argn;
//	c->argr = argc - argn;
//	val *env = &c->env;
//	for (int i = 0; i < argn; ++i)
//		env[i] = va_arg(args, val);
//	va_end(args);
//	return c;
//}

//val_t compose0_1(val_t env) {
//	val_t x = clo_apply0(env.a_fn[0]);
//	return clo_apply1(env.a_fn[1], x);
//}
//val_t compose1_1(val_t env, val_t arg0) {
//	val_t x = clo_apply1(env.a_fn[0], arg0);
//	return clo_apply1(env.a_fn[1], x);
//}
//val_t compose2_1(val_t env, val_t arg0, val_t arg1) {
//	val_t x = clo_apply2(env.a_fn[0], arg0, arg1);
//	return clo_apply1(env.a_fn[1], x);
//}
//val_t compose3_1(val_t env, val_t arg0, val_t arg1, val_t arg2) {
//	val_t x = clo_apply3(env.a_fn[0], arg0, arg1, arg2);
//	return clo_apply1(env.a_fn[1], x);
//}
//val_t compose4_1(val_t env, val_t arg0, val_t arg1, val_t arg2, val_t arg3) {
//	val_t x = clo_apply4(env.a_fn[0], arg0, arg1, arg2, arg3);
//	return clo_apply1(env.a_fn[1], x);
//}
//val_t compose1_2(val_t env, val_t arg0, val_t arg1) {
//	val_t x = clo_apply1(env.a_fn[0], arg0);
//	return clo_apply1(env.a_fn[1], x);
//}
//
//clo_t clo_compose(clo_t f, unsigned fargc, clo_t g, unsigned gargc) {
//	clo_t c = (clo_t)malloc(sizeof(struct clo) + 2 * sizeof(clo_t));
//	clo_t* a = c->env.a_fn;
//	// switch on fargc and gargc
//	c->fn.fn2 = compose1_1;
//	a[0] = f;
//	a[1] = g;
//	return c;
//}