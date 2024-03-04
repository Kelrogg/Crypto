#include "mod_math_lib_pch.h"
#include "mod_math_lib.h"

int mod_inv(int x, int mod);
int mod_pow(int base, int p, int mod);
int gcd(int x, int y);

int mod_add(int x, int y, int mod)
{
	return (x % mod + y % mod) % mod;
}

int mod_sub(int x, int y, int mod)
{
	return ((x - y) + mod) % mod;
}

int mod_mul(int x, int y, int mod)
{
	return (x % mod * y % mod) % mod;
}

int mod_div(int x, int y, int mod)
{
	return x * mod_inv(y, mod) % mod;
}

int mod_inv(int x, int mod)
{
	if (gcd(x, mod) != 1)
	    throw ("is not invertible");
	return x % mod;
}

int gcd(int x, int y)
{
    if (x == 0)
        return y;
    return gcd(y % x, x);
}

int mod_pow(int base, int p, int mod)
{
	if (p == 1)	{
		return base;
	}

	if (p & 1 == 0) {
		long long t = mod_pow(base, p >> 1, mod);
		return t * t % mod;
	}

	return mod_pow(base, p - 1, mod) * base % mod;
}