/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:57:51 by alhote            #+#    #+#             */
/*   Updated: 2016/06/28 10:42:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_shaders			*init_shader(unsigned int nbr_fshaders)
{
	t_shaders	*s;

	if ((s = malloc(sizeof(t_shaders) + (sizeof(void*) * nbr_fshaders))))
	{
		s->fragment_shader = \
		(double(**)(t_render*, t_obj*))((unsigned long)s + sizeof(t_shaders));
		s->nbr_fshaders = nbr_fshaders;
		s->vertex_shader = 0;
		return (s);
	}
	return (0);
}

int					exec_fshaders(t_shaders *s, t_render *r, t_obj *o)
{
	unsigned int	i;

	if (!s)
		return (1);
	i = 0;
	r->light_power = 0;
	r->specular_power = 0;
	while (i < s->nbr_fshaders)
		s->fragment_shader[i++](r, o);
	return ((i != 0));
}
