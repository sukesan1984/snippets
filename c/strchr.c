/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 15:19:54 by ktakami           #+#    #+#             */
/*   Updated: 2020/07/18 15:19:54 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int main()
{
	printf("%s addr: %p\n", strchr("hoge", '\n'), strchr("hoge", '\n'));
	printf("%s addr: %p\n", strchr("hoge", '\0'), strchr("hoge", '\0'));
	return (0);
}
