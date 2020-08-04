/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:57:43 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/03 11:57:43 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		main()
{
	union  { float f; int i; } a;
	float	original;

	printf("数字を入力してください\n");
	scanf("%f", &original);
	a.f = original;
	for (int i = 0; i < 32; i++)
	{
		if (a.i >> (31 - i) & 1)
			printf("1");
		else
			printf("0");
		if (i == 0 || i == 8)
			printf(".");
	}
	printf("\n");

	return (0);
}
