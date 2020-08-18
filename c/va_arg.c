/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 20:25:32 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/06 20:25:32 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

void test(char *fmt, ...)
{
	va_list ap;
	double *i;
	int		*j;
	void	*k;

	va_start(ap, fmt);
	i = ap->reg_save_area + ap->fp_offset;
	j = ap->reg_save_area + ap->gp_offset;
	printf("%f\n", *i);
	printf("%d\n", *j);
	k = va_arg(ap, void*);
	printf("%p\n", k);
	va_end(ap);
}

void test_double(char *fmt, ...)
{
	va_list	ap;
	double	i;
	int		j;

	va_start(ap, fmt);
	i = va_arg(ap, double);
	printf("%f\n", i);

	j = va_arg(ap, int);
	printf("%d\n", j);

	va_end(ap);
}

int main()
{
	test("hoge", 1.23, 4);
	test("hoge", 1.43, 1.24, 42);
	test("hoge", 42);
	test_double("hoge", 42, 10, 4.32);
	return (0);
}
