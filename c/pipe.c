/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosuketakami <ktakami@student.42tokyo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:54:44 by kosuketak         #+#    #+#             */
/*   Updated: 2020/07/29 18:54:44 by kosuketak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main()
{
	int		fds[2];
	int		res;
	char	buf[256];
	int		so;

	res = pipe(fds);
	so = fileno(stdout);

	res = dup2(fds[1], so);
	printf("hoge");
	fflush(stdout);
	res = read(fds[0], buf, sizeof(buf) - 1);
	buf[res] = '\0';
	fprintf(stderr, "buf=>%s\n", buf);
	return (0);
}
