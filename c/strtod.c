/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:54:37 by ktakami           #+#    #+#             */
/*   Updated: 2020/10/12 17:54:37 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strtod.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define DOUBLE_PLUS_ZERO		0x0000000000000000ULL
#define DOUBLE_MINUS_ZERO		0x8000000000000000ULL
#define DOUBLE_PLUS_INFINITY	0x7FF0000000000000ULL
#define DOUBLE_MINUS_INFINITY	0xFFF0000000000000ULL

#define FSM_WS 0
#define FSM_SON 1
#define FSM_LZOM 2
#define FSM_LZOF 3
#define FSM_MIP 4
#define FSM_MFP 5
#define FSM_ES 6
#define FSM_ELZ 7
#define FSM_E 8
#define FSM_STOP 9

#define PARSER_OK 0
#define PARSER_PZERO 1
#define PARSER_MZERO 2
#define PARSER_PINF 3
#define PARSER_MINF 4

#define DIGITS 18

t_bit96	add96(t_bit96 s, t_bit96 d)
{
	uint64_t	w;
	t_bit96		new;

	w = (uint64_t)s.s0 + (uint64_t)d.s0;
	new.s0 = w;
	w >>= 32;
	w += (uint64_t)s.s1 + (uint64_t)d.s1;
	new.s1 = w;
	w >>= 32;
	w += (uint64_t)s.s2 + (uint64_t)d.s2;
	new.s2 = w;
	return (new);
}

t_bit96	sub96(t_bit96 s, t_bit96 d)
{
	uint64_t	w;
	t_bit96		new;

	w = (uint64_t)s.s0 - (uint64_t)d.s0;
	new.s0 = w;
	w >>= 32;
	w += (uint64_t)s.s1 - (uint64_t)d.s1;
	new.s1 = w;
	w >>= 32;
	w += (uint64_t)s.s2 - (uint64_t)d.s2;
	new.s2 = w;
	return (new);
}

t_bit96	lsr96(t_bit96 s)
{
	t_bit96	new;

	new.s0 = (s.s0 >> 1) | ((s.s1 & 1) << 31);
	new.s1 = (s.s1 >> 1) | ((s.s2 & 1) << 31);
	new.s2 = (s.s2 >> 1);
	return (new);
}

t_bit96	lsl96(t_bit96 s)
{
	t_bit96	new;

	new.s0 = (s.s0 << 1);
	new.s1 = (s.s1 << 1) | ((s.s0 & 0x80000000) >> 31);
	new.s2 = (s.s2 << 1) | ((s.s1 & 0x80000000) >> 31);
	return (new);
}

char*			skip_white_space(char *str, int *state)
{
	if (isspace(*str))
	{
		*state = FSM_WS;
		return (++str);
	}
	*state = FSM_SON;
	return (str);
}

char*			sign_of_number(char *str, t_prep_number *pn, int *state)
{
	if (*str == '-' || *str == '+')
	{
		pn->negative = (*str == '-') ? 1 : 0;
		*state = FSM_LZOM;
		return (++str);
	}
	else if (isdigit(*str))
	{
		*state = FSM_LZOM;
		return (str);
	}
	*state = FSM_STOP;
	return (str);
}

char*			leading_zero_of_mantissa(char *str, int *state)
{
	if (*str == '0')
		return (++str);
	if (*str == '.')
	{
		*state = FSM_LZOF;
		return (++str);
	}
	*state = FSM_MIP;
	return (str);
}

char*			leading_zero_of_frac(char *str, t_prep_number *pn, int *state)
{
	if (*str == '0')
	{
		if (pn->exponent > -2147483648)
			pn->exponent--;
		return (++str);
	}
	*state = FSM_MFP;
	return (str);
}

char*			mantissa_int_part(char *str, t_prep_number *pn, int *state, int *digix)
{
	if (isdigit(*str))
	{
		if (*digix < DIGITS)
		{
			pn->mantissa = pn->mantissa * 10 + (*str - '0');
			(*digix)++;
		}
		else if (pn->exponent < 2147483647)
			pn->exponent++;
		return (++str);
	}
	if (*str == '.')
	{
		*state = FSM_MFP;
		return (++str);
	}
	*state = FSM_MFP;
	return (str);
}

char*			mantissa_frac_part(char *str, t_prep_number *pn, int *state, int *digix)
{
	if (isdigit(*str))
	{
		if (*digix < DIGITS)
		{
			pn->mantissa = pn->mantissa * 10 + (*str - '0');
			pn->exponent--;
			(*digix)++;
		}
		return (++str);
	}
	if (*str == 'e' || *str == 'E')
	{
		*state = FSM_ES;
		return (++str);
	}
	*state = FSM_ES;
	return (str);
}

char*			exponent_sign(char *str, int *state, int *exneg)
{
	if (*str == '+' || *str == '-')
	{
		*exneg = (*str == '-') ? 1 : 0;
		*state = FSM_ELZ;
		return (++str);
	}
	*state = FSM_ELZ;
	return (str);
}

char*			exponent_leading_zeros(char *str, int *state)
{
	if (*str == '0')
		return (++str);
	*state = FSM_E;
	return (str);
}

char*			exponent(char *str, int *expexp, int *state)
{
	if (isdigit(*str))
	{
		if (*expexp <= 2147483647 - (*str - '0') / 10)
			*expexp = *expexp * 10 + (*str - '0');
		else
			*expexp = 2147483647;
		return (++str);
	}
	*state = FSM_STOP;
	return (str);
}

static int	parse(char *str, t_prep_number *pn)
{
	int	state;
	int	digix;
	int	exneg;
	int	expexp;
	int	result;

	state = FSM_WS;
	digix = 0;
	exneg = 0;
	expexp = 0;
	result = PARSER_OK;
	while (state != FSM_STOP)
	{
		// skip white space
		if (state == FSM_WS)
			str = skip_white_space(str, &state);
		// read sign
		else if (state == FSM_SON)
			str = sign_of_number(str, pn, &state);
		else if (state == FSM_LZOM)
			str = leading_zero_of_mantissa(str, &state);
		else if (state == FSM_LZOF)
			str = leading_zero_of_frac(str, pn, &state);
		else if (state == FSM_MIP)
			str = mantissa_int_part(str, pn, &state, &digix);
		else if (state == FSM_MFP)
			str = mantissa_frac_part(str, pn, &state, &digix);
		else if (state == FSM_ES)
			str = exponent_sign(str, &state, &exneg);
		else if (state == FSM_ELZ)
			str = exponent_leading_zeros(str, &state);
		else if (state == FSM_E)
			str = exponent(str, &expexp, &state);
		else
			break;
	}
	if (exneg) expexp = -expexp;
	pn->exponent += expexp;

	if (pn->mantissa == 0)
	{
		if (pn->negative)
			result = PARSER_MZERO;
		else
			result = PARSER_PZERO;
	}
	else if (pn->exponent > 309)
	{
		if (pn->negative)
			result = PARSER_MINF;
		else
			result = PARSER_PINF;
	}
	else if (pn->exponent < -340)
	{
		if (pn->negative)
			result = PARSER_MZERO;
		else
			result = PARSER_PZERO;
	}
	return (result);
}

static double converter(t_prep_number *pn)
{
	int				binexp;
	uint64_t		binexs2;
	t_hex_double	hd;
	t_bit96			s;
	t_bit96			q;
	t_bit96			r;
	uint64_t		t;
	uint32_t		mask28;

	binexp = 92;
	mask28 = 0xF << 28;
	// sign, exp, mantissa
	// mantissa to 96bit
	s.s2 = 0;
	s.s1 = (uint32_t)(pn->mantissa >> 32);
	s.s0 = (uint32_t)(pn->mantissa & 0xffffffff);
	while (pn->exponent > 0)
	{
		// mantissa * 10 = mantissa * (2 + 2^3)
		q = lsl96(s); // mantissa << 1
		r = lsl96(q); // mantissa << 2
		s = lsl96(r); // mantissa << 3
		s = add96(s, q); // mantissa * (2 + 2^3)
		pn->exponent--;

		while (s.s2 & mask28)
		{
			binexp++;
			s = lsr96(s);
		}
	}

	while (pn->exponent < 0)
	{
		while (!(s.s2 & (1 << 31)))
		{
			s = lsl96(s);
			binexp--;
		}
		q.s2 = s.s2 / 10;
		r.s1 = s.s2 % 10;
		r.s2 = (r.s1 << 24) | (s.s1 >> 8);
		q.s1 = r.s2 / 10;
		r.s1 = r.s2 % 10;
		r.s2 = (r.s1 << 24) | ((s.s1 & 0xFF) << 16) | (s.s0 >> 16);
		r.s0 = r.s2 / 10;
		r.s1 = r.s2 % 10;
		q.s0 = ((r.s1 << 16)| (s.s0 & 0xFFFF)) / 10 | (r.s0 << 16);
		q.s1 = ((r.s0 & 0x00FF0000) >> 16) | (q.s1 << 8);
		s.s2 = q.s2;
		s.s1 = q.s1;
		s.s0 = q.s0;

		pn->exponent++;
	}

	if (s.s2 || s.s1 || s.s0)
	{
		while (!(s.s2 & mask28))
		{
			s = lsl96(s);
			binexp--;
		}
	}
	binexp += 1023;
	//printf("binexp: %d\n", binexp);
	//printf("manttissa: %#x, %#x, %#x\n", s.s2, s.s1, s.s0);

	if (binexp > 2046)
	{
		if (pn->negative)
			hd.u = DOUBLE_MINUS_INFINITY;
		else
			hd.u = DOUBLE_PLUS_INFINITY;
	}
	else if (binexp < 1)
	{
		if (pn->negative)
			hd.u = DOUBLE_MINUS_ZERO;
	}
	else if (s.s2)
	{
		binexs2 = (uint64_t)binexp;
		// 完全に等しい時
		if (s.s1 & 0x00000080 && (!(s.s1 & 0x0000007f) && !(s.s0)))
		{
			if ((s.s1 >> 8) & 1)
				t = (s.s1 >> 8) + 1; // 偶数方向に1足す
			else
				t = (s.s1 >> 8); // すでに最下位ビットが0
		}
		else if (!(s.s1 & 0x00000080)) // 0x10000000のビットが立ってない時は切り捨てればよい
			t = (s.s1 >> 8);
		// 下位40ビットが0x10000000 00000000000000000000000000000000より大きい場合s1のビットを一つ大きくする
		else
			t = (s.s1 >> 8) + 1;
		hd.u = (binexs2 << 52) | ((uint64_t)(s.s2 & ~mask28) << 24) | t;
		if (pn->negative)
			hd.u |= (1ULL << 63);
	}

	//printf("encoded: %#llx\n", hd.u);
	return hd.d;
}

double	ft_strtod(char *s)
{
	t_prep_number	*pn;
	t_hex_double	hd;
	int				i;
	double			result;

	hd.u = DOUBLE_PLUS_ZERO;
	pn = calloc(1, sizeof(t_prep_number));
	i = parse(s, pn);
	if (i == PARSER_OK)
		result = converter(pn);
	else if (i == PARSER_PZERO)
		result = hd.d;
	else if (i == PARSER_MZERO)
		result = DOUBLE_MINUS_ZERO;
	else if (i == PARSER_PINF)
		result = DOUBLE_PLUS_INFINITY;
	else if (i == PARSER_MINF)
		result = DOUBLE_MINUS_INFINITY;
	return (result);
}

void	test(char *str)
{
	int				result;
	t_prep_number	*pn;

	printf("input : %s\n", str);
	//pn = calloc(1, sizeof(t_prep_number));
	//result = parse(str, pn);
	//if (result == PARSER_MZERO)
	//	printf("result: -0\n");
	//else if (result == PARSER_PZERO)
	//	printf("result: +0\n");
	//else if (result == PARSER_MINF)
	//	printf("result: -inf\n");
	//else if (result == PARSER_PINF)
	//	printf("result: +inf\n");
	//else
	//{
	//	printf("result: OK\n");
	//	printf("negative: %d, exponent: %d, mantissa: %lld(%#llx)\n", pn->negative, pn->exponent, pn->mantissa, pn->mantissa);
	//}
	if (ft_strtod(str) == strtod(str, NULL))
	{
		printf("\033[0;32m");
		printf("[ok]\n");
		printf("\033[0m");
	}
	else
	{
		printf("\033[1;31m");
		printf("[ng]: my: %1.17g, lib: %1.17g\n", ft_strtod(str), strtod(str, NULL));
		printf("\033[0m");
	}
}

int		main(void)
{
	t_bit96			c;
	int				result;
	t_prep_number	pn;

	c.s0 = 0;
	c.s1 = 0;
	c.s2 = 0xffffffff;
	c = lsr96(c);
	printf("%#x, %#x, %#x\n", c.s2, c.s1, c.s0);
	c = lsl96(c);
	printf("%#x, %#x, %#x\n", c.s2, c.s1, c.s0);

	test("0.00000123456");
	test("0.123456");
	test("1.23456");
	test("12.3456");
	test("123.456");
	test("-0.123456");
	test("-1.23456");
	test("-12.3456");
	test("-123.456");
	test("-123.456e12");
	test("123.456e13");
	test("18014398509482008");
	test("18014398509482009");
	test("18014398509482010");
	test("18014398509482011");
	test("18014398509482012");
	test("18014398509482013");
	test("18014398509482014");
	test("18014398509482015");
	test("18014398509482016");
	test("18014398509482017");
	test("18014398509482018");
	test("18014398509482019");
	test("18014398509482020");
	test("18014398509482021");
	test("2251799813685248");
	test("2251799813685248.1");
	test("2251799813685248.2");
	test("2251799813685248.21");
	test("2251799813685248.22");
	test("2251799813685248.23");
	test("2251799813685248.24");
	test("2251799813685248.25");
	test("2251799813685248.26");
	test("2251799813685248.27");
	test("2251799813685248.28");
	test("2251799813685248.29");
	test("2251799813685248.3");
	test("2251799813685248.4");
	test("2251799813685248.5");
	test("2251799813685248.6");
	test("2251799813685248.7");
	test("2251799813685248.74");
	test("2251799813685248.75");
	test("2251799813685248.76");
	test("2251799813685248.8");
	test("2251799813685248.9");
	test("2251799813685249");
	test("0.00000123456e-123");
	test("1.7976931348623157e308");
	test("4.9406564584124654e-324");
	test("2.2250738585072014e-308");
	test("2.2250738585072001e-308");
	return (0);
}
