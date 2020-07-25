/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   override.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 19:34:20 by ktakami           #+#    #+#             */
/*   Updated: 2020/07/25 19:34:20 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>

void	*malloc(unsigned long size)
{
	errno = ENOMEM;
	return NULL;
}

int main()
{
	char	*copied;
	copied = malloc(5 * sizeof(char));
	if (!copied)
	{
		perror("malloc failed");
		return (1);
	}
	strcpy(copied, "hoge");
	printf("%s\n", copied);
	return (0);
}
