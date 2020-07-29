/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 18:28:26 by ktakami           #+#    #+#             */
/*   Updated: 2020/07/18 18:28:26 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int		fd;
	size_t	size;
	//char	buf[10];
	char	*buf;
	int		i;

	buf = calloc(10, sizeof(char));
	fd = open("test", O_RDONLY);
	size = read(fd, buf, 10);
	i = 0;
	printf("%ld\n", size);
	while (i < 10)
	{
		printf("i: %d, ascii: %d, char: %c\n", i, buf[i], buf[i]);
		i++;
	}
	//printf("%ld\n", size);

	return (0);
}
