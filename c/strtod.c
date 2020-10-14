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

int		main(void)
{
	t_bit96	a;
	t_bit96	b;
	t_bit96	c;

	a.s2 = 0;
	a.s1 = 13;
	a.s0 = 0;
	b.s2 = 0;
	b.s1 = 12;
	b.s0 = 0;
	c = sub96(a, b);
	printf("%d, %d, %d\n", c.s2, c.s1, c.s0);
	return (0);
}
