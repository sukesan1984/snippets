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

#include <stdlib.h>
#include <stdio.h>

#define DOUBLE_PLUS_ZERO		0x0000000000000000ULL
#define DOUBLE_MINUS_ZERO		0x8000000000000000ULL
#define DOUBLE_PLUS_INFINITY	0x7FF0000000000000ULL
#define DOUBLE_MINUS_INFINITY	0xFFF0000000000000ULL

int	main()
{
	union {
		unsigned long long a;
		double b;
	} hoge;
	double c;
	printf("plus zero :%f\n", (double)DOUBLE_PLUS_ZERO);
	printf("minus zero:%f\n", (double)0x8000000000000000ULL);
	printf("plus inf  :%f\n", (double)DOUBLE_PLUS_INFINITY);
	printf("minus  inf:%f\n", (double)DOUBLE_MINUS_INFINITY);

	hoge.a = DOUBLE_PLUS_ZERO;
	printf("plus zero :%f\n", hoge.b);
	hoge.a = DOUBLE_MINUS_ZERO;
	printf("minus zero: %f\n", hoge.b);
	c = DOUBLE_MINUS_ZERO;
	hoge.a = DOUBLE_PLUS_INFINITY;
	printf("plus inf  :%f\n", hoge.b);
	hoge.a = DOUBLE_MINUS_INFINITY;
	printf("minus  inf:%f\n", hoge.b);

	hoge.b = (double)DOUBLE_MINUS_ZERO;
	printf("%#llx\n", hoge.a);

	hoge.a = 0x3ff8000000000000;
	printf("%f\n", hoge.b);

	return (0);
}
