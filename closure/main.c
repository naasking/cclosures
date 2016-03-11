#include "closure.h"
#include <stdio.h>

val_t foo(val_t arg0) {
	return arg0;
}

int main(int argc, char** argv) {
	val_t arg = { .si = 99789 };
	clo_t c = clo_lift((fn_t){ .fn1 = foo }, 1, 1, arg);

	printf("c->env = %d\n", c->env[0].si);
	val_t x = clo_call(c);

	printf("x = %u\n", x.si);

	clo_t c2 = clo_lift((fn_t) { .fn1 = foo }, 1, 0);
	x = clo_call(c2, arg);
	printf("x = %u\n", x.si);
	return 0;
}
