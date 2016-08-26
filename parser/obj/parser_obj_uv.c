/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_uv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 21:23:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 21:23:39 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int				parse_obj_uv(t_sda_obj *s)
{
	if ((s->select_uv >= s->size_uv) || (!s->uv))
	{
		s->size_uv += 3;
		s->uv = (t_v2f*)ft_realloc(s->uv,
			(unsigned int)(sizeof(t_v2f) * (s->size_uv - 3)),
			(unsigned int)(sizeof(t_v2f) * s->size_uv));
	}
	s->uv[s->select_uv] = (t_v2f){(float)ft_atod(s->av[1]),
								(float)ft_atod(s->av[2])};
	s->select_uv++;
	return (1);
}
