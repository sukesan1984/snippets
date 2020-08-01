/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 11:49:59 by ktakami           #+#    #+#             */
/*   Updated: 2020/07/29 11:49:59 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char	buf[4000];
	char	*short_str;

	snprintf(buf, 4000, "hoge %d\n", 100);
	printf("%s", buf);
	printf("%2$d, %3$s, %1$d\n", 1, 2, "hoge");

	short_str = malloc(10 * sizeof(char));
	snprintf(short_str, 12, "abcdefghijklmn");
	printf("%s\n", short_str);

	return (0);
}
