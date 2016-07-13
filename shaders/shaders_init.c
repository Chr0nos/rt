/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:20:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 15:21:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_shaders			*init_shaders(void)
{
	t_shaders	*s;

	if ((s = malloc(sizeof(t_shaders))))
	{
		s->shader = NULL;
		s->vertex_shader = NULL;
		return (s);
	}
	return (NULL);
}

t_shader			*init_shader(t_shaders *shaders,
	void (*shader)(t_shader *s, t_render *r,
	t_obj *o), void *data, unsigned int color, unsigned int
	(*blend)(unsigned int a, unsigned int b))
{
	t_shader	*s;
	t_shader	*sh;

	if ((s = malloc(sizeof(t_shader))))
	{
		s->enabled = 1;
		s->color_base = color;
		s->color_render = color;
		s->content = data;
		s->blend = blend;
		s->exec = shader;
		s->next = NULL;
		if (!shaders->shader)
			shaders->shader = s;
		else
		{
			sh = shaders->shader;
			while (sh->next)
				sh = sh->next;
			sh->next = s;
		}
		return (s);
	}
	return (NULL);
}
