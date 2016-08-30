/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:20:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/30 21:01:30 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_shaders	*shaders_init(void)
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

t_shader	*shader_init(t_shaders *shaders,
	void (*shader)(t_shader *s, t_render *r, t_obj *o, unsigned int *color),
	unsigned int color,
	unsigned int (*blend)(unsigned int a, unsigned int b))
{
	t_shader	*s;
	t_shader	*sh;

	if ((s = malloc(sizeof(t_shader))))
	{
		s->enabled = 1;
		s->color_base = color;
		s->color_render = color;
		s->content = NULL;
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
