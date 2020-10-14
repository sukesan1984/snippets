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

#define DOUBLE_PLUS_ZERO		0x0000000000000000ULL
#define DOUBLE_MINUS_ZERO		0x8000000000000000ULL
#define DOUBLE_PLUS_INFINITY	0x7FF0000000000000ULL
#define DOUBLE_MINUS_INFINITY	0xFFF0000000000000ULL

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

int		main(void)
{
	t_bit96	c;

	c.s0 = 0;
	c.s1 = 0;
	c.s2 = 0xffffffff;
	c = lsr96(c);
	printf("%#x, %#x, %#x\n", c.s2, c.s1, c.s0);
	c = lsl96(c);
	printf("%#x, %#x, %#x\n", c.s2, c.s1, c.s0);
	return (0);
}
