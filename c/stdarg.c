/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdarg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 14:55:06 by ktakami           #+#    #+#             */
/*   Updated: 2020/07/29 14:55:06 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

void foo(char *fmt, ...)
{
	va_list ap;
	int d;
	char c, *s;

	va_start(ap, fmt);
	while (*fmt)
			switch(*fmt++) {
			case 's':                       /* string */
					s = va_arg(ap, char *);
					printf("string %s\n", s);
					break;
			case 'd':                       /* int */
					d = va_arg(ap, int);
					printf("int %d\n", d);
					break;
			case 'c':                       /* char */
					/* Note: char is promoted to int. */
					c = va_arg(ap, int);
					printf("char %c\n", c);
					break;
			}
	va_end(ap);
}

int	main()
{
	int		i;
	char	*s;
	char	c;

	i = 100;
	s  = "hoge";
	c = 'k';
	foo("dsc", i, s, c);
	return (0);
}
