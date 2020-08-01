/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:02:20 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/01 19:02:20 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main()
{
	int a;
	int b;

	printf("a for %%d:\n");
	scanf("%d", &a);
	printf("b for %%i:\n");
	scanf("%i", &b);

	printf("a: %d\n", a);
	printf("b: %d\n", b);
	return (0);
}
