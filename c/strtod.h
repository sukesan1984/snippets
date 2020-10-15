/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakami <ktakami@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:21:52 by ktakami           #+#    #+#             */
/*   Updated: 2020/10/12 19:21:52 by ktakami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOD_H
# define STRTOD_H
# include <stdint.h>

typedef struct	s_bit96 {
	uint32_t	s2;
	uint32_t	s1;
	uint32_t	s0;
}				t_bit96;
#endif
