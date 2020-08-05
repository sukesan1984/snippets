/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:30:55 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/05 15:30:55 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

void	show_ap(va_list ap)
{
	printf("gp_offset: %u\n", ap->gp_offset);
	printf("fp_offset: %u\n", ap->fp_offset);
	printf("overflow_arg_area: %p\n", ap->overflow_arg_area);
	printf("reg_save_area: %p\n", ap->reg_save_area);
}

void	show_double(double a)
{
	printf("%f\n", a);
}

void	get_double(char *fmt, ...)
{
	va_list	ap;
	va_list copy;
	double	a;
	void	*b;
	double	*c;
	void	(*show_void)(void *);
	//union { double c; void *d; } e;

	va_start(ap, fmt);
	b = ap->reg_save_area + ap->fp_offset;
	printf("fp_b: %p\n", b);
	b = ap->reg_save_area + ap->gp_offset;
	printf("gp_b: %p\n", b);
	b = va_arg(ap, void*);
	c = (double*) b;
	printf("b: %p\n", b);
	//b = va_arg(ap, void*);
	//printf("%f\n", *(double*)b);
	show_void = (void(*)(void*))show_double;
	show_void(b);
	va_end(ap);
}

void	show_int(int a)
{
	printf("%d\n", a);
}

void	get_int(char *fmt, ...)
{
	va_list	ap;
	int		a;
	void	*b;
	int		*c;
	void	(*show_void)(void *);
	va_start(ap, fmt);
	b = ap->reg_save_area + ap->gp_offset;
	printf("directly: %p\n", b);
	//b = va_arg(ap, void*);
	a = (int)va_arg(ap, void*);
	printf("a:%d\n", a);
	printf("b: %p, c: %p\n", b, c);

	show_void = (void(*)(void*))show_int;
	show_int((int)b);
	//show_void(b);
	va_end(ap);
}

void	test(char *fmt, ...)
{
	int		j;
	int		*i;
	long	l;
	char	**s;
	double	*f;
	double	vf;
	va_list ap;
	va_start(ap, fmt);
	j = 0;
	i = &j;
	i = ap->overflow_arg_area;
	printf("first_arg: %d(%p)\n", *i, i);
	show_ap(ap);
	i = ap->reg_save_area + ap->gp_offset;
	//j = va_arg(ap, int);
	l = (long)va_arg(ap, void*);
	printf("%d\n", (int)l);
	//printf("%d\n", j);
	s = ap->reg_save_area + ap->gp_offset;
	printf("%s: %p\n", *s, *s);
	*s = va_arg(ap, char*);
	printf("%s: %p\n", *s, *s);
	show_ap(ap);
	f = ap->reg_save_area + ap->fp_offset;
	//vf = va_arg(ap, double);
	l = (long) va_arg(ap, void*);
	printf("%f\n", (double)l);
	//printf("%f\n", vf);

	show_ap(ap);
	va_end(ap);
}

int main()
{
//	test("hoge", 42, "fuga", 1.23);
	get_double("hoge", 1.23);
//	get_int("hoge", 42);
	return (0);
}
