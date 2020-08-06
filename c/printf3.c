/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:52:18 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/03 16:52:18 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

void	put(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}

int main()
{
	char *fmt;
	printf("%020d\n", 1);
	printf("%20c\n", 'h');
	printf("%20s\n", "h");
	printf("%20p\n", "h");
	return(0);
}
