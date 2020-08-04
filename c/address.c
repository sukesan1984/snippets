/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:09:12 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/01 20:09:12 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main()
{
	unsigned long max_address = 0xffffffffffffffff;
	unsigned long diff;
	char array[3] = {1, 2, 3};
	diff = max_address - (unsigned long)array;
	printf("array(address)             : %p\n", array);
	printf("array(unsigned long)       : %lx\n", (unsigned long)array);
	printf("diff                       : %lx\n", diff);
	printf("diff + array(address)      : %p\n", diff + array);
	printf("diff + array(unsigned long): %lx\n", diff + (unsigned long)array);
	return (0);
}
