/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 10:52:55 by ktakami           #+#    #+#             */
/*   Updated: 2020/09/02 10:52:55 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	do_something_ptr(const int *p)
{
	int	*a;

	a = (int*) p;
	*a = 4;
}

void	do_something_pptr(const int **pp)
{
	int	*p;
	p = (int*)*pp;
	*p = 5;
}

int		main()
{
	int	a;
	int	*p;

	a = 3;
	p = &a;
	do_something_ptr(&a);
	printf("%d\n", a);
	do_something_pptr((const int**)&p);
	printf("%d\n", a);
	return (0);
}
