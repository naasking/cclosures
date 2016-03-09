/*
* The val interpreter.
*/

#include "closure.h"
#include <stdio.h>

val_t foo(val_t arg0) {
	return arg0;
}

int main(int argc, char** argv) {
	val_t arg = { .si = 99789 };
	clo_t c = clo_lift((fn_t)foo, 1, 1, arg);
	printf("c->env = %d\n", c->env[0].si);
	val_t x = clo_apply0(c);
	printf("x = %u\n", x.si);
	return 0;
}
