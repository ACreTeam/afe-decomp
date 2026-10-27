#include "PowerPC_EABI_Support/MSL_C/MSL_Common/arith.h"

int abs(int x)
{
	return x > 0 ? x : -x;
}

long labs(long x)
{
	return x > 0 ? x : -x;
}

div_t div(int numer, int denom)
{
	int n_sign, d_sign;
	div_t value;

	n_sign = 1;
	d_sign = 1;

	if (numer < 0) {
		numer  = -numer;
		n_sign = -1;
	}

	if (denom < 0) {
		denom  = -denom;
		d_sign = -1;
	}

	value.quot = (numer / denom) * (n_sign * d_sign);
	value.rem  = (numer * n_sign) - (d_sign * (value.quot * denom));
	return value;
}

ldiv_t ldiv(long numer, long denom)
{
	long n_sign, d_sign;
	ldiv_t value;

	n_sign = 1;
	d_sign = 1;

	if (numer < 0) {
		numer  = -numer;
		n_sign = -1;
	}

	if (denom < 0) {
		denom  = -denom;
		d_sign = -1;
	}

	value.quot = (numer / denom) * (n_sign * d_sign);
	value.rem  = (numer * n_sign) - (d_sign * (value.quot * denom));
	return value;
}

lldiv_t lldiv(long long numer, long long denom)
{
	long long n_sign, d_sign;
	lldiv_t value;

	n_sign = 1;
	d_sign = 1;

	if (numer < 0) {
		numer  = -numer;
		n_sign = -1;
	}

	if (denom < 0) {
		denom  = -denom;
		d_sign = -1;
	}

	value.quot = (numer / denom) * (n_sign * d_sign);
	value.rem  = (numer * n_sign) - (d_sign * (value.quot * denom));
	return value;
}
