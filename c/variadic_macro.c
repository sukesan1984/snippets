/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variadic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 10:55:54 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/05 10:55:54 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define test(a, ...) printf(a, __VA_ARGS__)

int main()
{
	test("hoge%s\n", "fuga");
	return (0);
}
