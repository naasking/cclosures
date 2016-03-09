
#include "closure.h"
#include <stdio.h>
#include <assert.h>

val_t foo(val_t arg0) {
	return arg0;
}

int main(int argc, char** argv) {
	clo_t c = clo_lift((fn_t){ .fn1 = foo }, 1, 1, (val_t){ .si = 99789 });
	printf("c->env = %d\n", c->env.si);
	val_t x = clo_apply0(c);
	printf("x = %u\n", x.si);
	return 0;
}
