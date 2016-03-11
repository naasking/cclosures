/*
 * Closure combinators.
 */

#include "closure.h"
#include <string.h>
#include <math.h>
#include <stdarg.h>


clo_t clo_init(clo_t c, fn_t fn, unsigned argc, unsigned argn, ...) {
	if (argc > CLO_ARGS_MAX) {
		errno = E2BIG;
		return NULL;
	}
	va_list args;
	va_start(args, argn);
	c->fn = fn;
	c->hdr = (argc << CLO_ARGC_OFF) | ((argc - argn) << (CLO_ARGC_OFF - 4));
	val_t *env = c->env;
	for (int i = 0; i < argn; ++i)
		env[i] = va_arg(args, val_t);
	va_end(args);
	return c;
}

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