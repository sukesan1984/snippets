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

int main()
{
	int		fd;
	size_t	size;
	char	buf[10];

	fd = open("emptyfile", O_RDONLY);
	size = read(fd, buf, 10);
	printf("%ld\n", size);

	return (0);
}
