/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localeconv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:12:46 by ktakami           #+#    #+#             */
/*   Updated: 2020/08/01 17:12:46 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <locale.h>

int	main()
{
	struct lconv *hoge;
	hoge = localeconv();
	setlocale(LC_NUMERIC, "da_DK");
	int i = 12345678;
	printf("%'d\n", i);
	return (0);
}
