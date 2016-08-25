/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 21:22:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 21:22:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sda.h"

int				parse_obj_v(t_sda_obj *s)
{
	if ((s->select_v >= s->size_v) || (!s->v))
	{
		s->size_v += 3;
		s->v = (t_v4d*)ft_realloc(s->v,
			(unsigned int)(sizeof(t_v4d) * (s->size_v - 3)),
			(unsigned int)(sizeof(t_v4d) * s->size_v));
	}
	s->v[s->select_v] = (t_v4d){ft_atod(s->av[1]),
								ft_atod(s->av[2]),
								ft_atod(s->av[3]),
								0.0};
	s->select_v++;
	return (1);
}
