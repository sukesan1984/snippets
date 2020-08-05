/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:02:08 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/05 18:02:08 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main()
{
	printf("double size: %ld\n", sizeof(double));
	printf("double* size: %ld\n", sizeof(double*));
	return (0);
}
