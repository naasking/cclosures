#include "cfn.h"
#include "fn.h"
#include <stdio.h>

val foo(val arg0) {
	return arg0;
}

int main(int argc, char** argv) {
	//val arg = { .si = 99789 };
	//fn* c = clo_lift((fn*){ .fn1 = foo }, 1, 1, arg);
	////int f = VA_ARG(8, 1, 2, 3);

	//printf("c->env = %d\n", c->env[0].si);
	//val x = clo_call(c);
	//printf("x = %u\n", x.si);

	////int f = EVAL(ADD(3, 2));

	//fn* c2 = clo_lift((fn_t) { .fn1 = foo }, 1, 0);
	//fn_apply(x, c2, arg, x, x);
	//printf("x = %u\n", x.si);
	return 0;
}
