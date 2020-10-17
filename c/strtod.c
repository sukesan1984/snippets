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

void	test_parse(char *str)
{
	int				result;
	t_prep_number	*pn;

	printf("%s\n", str);
	pn = calloc(1, sizeof(t_prep_number));
	result = parse(str, pn);
	if (result == PARSER_MZERO)
		printf("result: -0\n");
	else if (result == PARSER_PZERO)
		printf("result: +0\n");
	else if (result == PARSER_MINF)
		printf("result: -inf\n");
	else if (result == PARSER_PINF)
		printf("result: +inf\n");
	else
	{
		printf("result: OK\n");
		printf("negative: %d, exponent: %d, mantissa: %lld(%#llx)\n", pn->negative, pn->exponent, pn->mantissa, pn->mantissa);
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

	test_parse("0.00000123456");
	test_parse("0.123456");
	test_parse("1.23456");
	test_parse("12.3456");
	test_parse("123.456");
	test_parse("-0.123456");
	test_parse("-1.23456");
	test_parse("-12.3456");
	test_parse("-123.456");
	test_parse("-123.456e12");
	test_parse("123.456e13");
	test_parse("0.00000123456e-123");
	test_parse("1.7976931348623157e308");
	test_parse("4.9406564584124654e-324");
	test_parse("2.2250738585072014e-308");
	test_parse("2.2250738585072001e-308");
	return (0);
}
