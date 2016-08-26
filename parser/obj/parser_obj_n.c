/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 21:24:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 21:24:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int				parse_obj_n(t_sda_obj *s)
{
	if ((s->select_n >= s->size_n) || (!s->n))
	{
		s->size_n += 3;
		s->n = (t_v4d*)ft_realloc(s->n,
			(unsigned int)(sizeof(t_v4d) * (s->size_n - 3)),
			(unsigned int)(sizeof(t_v4d) * s->size_n));
	}
	s->n[s->select_n] = (t_v4d){ft_atod(s->av[1]),
								ft_atod(s->av[2]),
								ft_atod(s->av[3]),
								0.0};
	s->select_n++;
	return (1);
}
