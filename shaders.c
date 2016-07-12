/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:57:51 by alhote            #+#    #+#             */
/*   Updated: 2016/07/11 18:22:13 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_shaders			*init_shaders(void)
{
	t_shaders	*s;

	if ((s = malloc(sizeof(t_shaders))))
	{
		s->shader = 0;
		s->vertex_shader = 0;
		return (s);
	}
	return (0);
}

t_shader			*init_shader(t_shaders *shaders,
	void (*shader)(t_shader *s, t_render *r,
	t_obj *o), unsigned int color, unsigned int
	(*blend)(unsigned int a, unsigned int b))
{
	t_shader	*s;
	t_shader	*sh;

	if ((s = malloc(sizeof(t_shader))))
	{
		s->enabled = 1;
		s->color_base = color;
		s->color_render = color;
		s->blend = blend;
		s->exec = shader;
		s->next = 0;
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

int					exec_fshaders(t_shaders *s, t_render *r, t_obj *o)
{
	t_shader		*shader;

	if (!s)
		return (1);
	r->light_power = 0;
	r->specular_power = 0;
	shader = s->shader;
	while (shader)
	{
		shader->exec(shader, r, o);
		shader = shader->next;
	}
	return (0);
}

unsigned int		compute_color_shaders(t_shaders *s)
{
	unsigned int	color;
	t_shader		*shader;

	if (!s)
		return (1);
	color = 0;
	shader = s->shader;
	if (shader)
		color = shader->color_render;
	shader = shader->next;
	while (shader)
	{
		if (shader->enabled)
		{
			color = shader->blend(shader->color_render, color) & 0x00FFFFFF;
			shader->color_render = shader->color_base;
		}
		shader->enabled = 1;
		shader = shader->next;
	}
	return (color);
}

void			disable_nexts(t_shader *s)
{
	t_shader	*shader;
	
	shader = 0;	
	if (s->next)
		shader = s->next;
	while (shader)
	{
		shader->enabled = 0;
		shader = shader->next;
	}
}
