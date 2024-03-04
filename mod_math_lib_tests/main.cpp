#include <ios>
#include "mod_math_lib.h"

void test(bool success);

int main()
{
	test(mod_add(6, 24, 4) == 2);
	test(mod_add(24, 6, 4) == 2);

	test(mod_sub(13, 4, 6) == 3);
	test(mod_sub(13, 3, 6) == 4);

	test(mod_mul(5, 8, 17) == 6);

	test(mod_div(17, 5, 7) == 2);
	test(mod_div(17, 2, 7) == 5);
}

void test(bool success)
{
	if (success)
	{
		puts("Passed!");
	}
	else
	{
		puts("ERROR!");
	}
}
