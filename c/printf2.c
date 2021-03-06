/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:21:11 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/01 19:21:11 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define abs(x) x > 0 ? (x) : (-x)

#define test(x) printf(x)

int main()
{
	int a = abs(1);
	printf("%*d\n", 5, 10);
	printf("%.*d\n", 5, 10);
	printf("%%4.5d: %4.5d\n", 10);
	printf("%%*.*d: %*.*d\n", 4, 5, 10);
	printf("%%10.5d: %10.5d\n", 10);
	printf("%%-10.5d: %-10.5d(end)\n", 12);
	printf("%%2$-10.5d: %2$-10.5d(next)%1$d\n", 12, 24);
	printf("%%*.*d: %*.*d\n", 10, 5, 10);
	printf("%d\n", a);
	test("hoge");
	return (0);
}
