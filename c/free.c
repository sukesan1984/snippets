/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 12:34:37 by ktakami           #+#    #+#             */
/*   Updated: 2020/07/25 12:34:37 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void free_with_null(void **target)
{
	if (!target)
		return ;
	free(*target);
	*target = NULL;
}

int main() {
	char *hoge = malloc(5 * sizeof(char));
	printf("%p\n", hoge);
	free_with_null((void*)&hoge);
	if (hoge == NULL)
		printf("hoge is NULL\n");
	else
		printf("hoge is not NULL\n");
	printf("%p\n", hoge);
	free_with_null((void*)&hoge);
	free_with_null(NULL);
	return (0);
}
