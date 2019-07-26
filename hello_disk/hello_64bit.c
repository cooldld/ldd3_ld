#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int a;
	unsigned long b;
	char *c;

	printf("sizeof(int)=%ld\n", sizeof(a));
	printf("sizeof(unsigned long)=%ld\n", sizeof(b));
	printf("sizeof(char *)=%ld\n", sizeof(c));

	printf("&a(p)=%p\n", &a);
	printf("&a(x)=0x%lx\n", (unsigned long)&a);
	b = (unsigned long)&a;
	printf("b(x)=0x%lx\n", b);

	c = malloc(100);
	printf("c(p)=%p\n", c);
	printf("c(x)=0x%lx\n", (unsigned long)c);
	b = (unsigned long)c;
	printf("b(x)=0x%lx\n", b);

	exit(0);
}
