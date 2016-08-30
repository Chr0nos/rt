/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:57:51 by alhote            #+#    #+#             */
/*   Updated: 2016/08/30 21:45:46 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

int					shaders_exec(t_shaders *s, t_render *r, t_obj *o, unsigned int *res)
{
	t_shader		*shader;
	unsigned int	color;
	if (!s)
		return (1);
	shader = s->shader;
	color = shader->color_render;
	while (shader)
	{
		if (shader->enabled) {
			shader->exec(shader, r, o, &color);
			*res = shader->blend(color, *res);
		}
		shader = shader->next;
	}
	return (0);
}
/*
unsigned int		shaders_compute_color(t_shaders *s, unsigned int color)
{
	t_shader		*shader;

	if (!s)
		return (1);
	shader = s->shader;
	while (shader)
	{
		if (shader->enabled)
		{
			color = shader->blend(shader->color_render, color);
//			shader->color_render = shader->color_base;
		}
		shader = shader->next;
	}
	return (color);
}
*/
void				shaders_disable_nexts(t_shader *s)
{
	t_shader	*shader;

	shader = NULL;
	if (s->next)
		shader = s->next;
	while (shader)
	{
		shader->enabled = 0;
		shader = shader->next;
	}
}
