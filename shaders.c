/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:57:51 by alhote            #+#    #+#             */
/*   Updated: 2016/07/01 20:23:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_shaders			*init_shaders(unsigned int nbr_fshaders)
{
	t_shaders	*s;

	if ((s = malloc(sizeof(t_shaders) + (sizeof(t_shader) * nbr_fshaders))))
	{
		s->shader = (t_shader**)((unsigned long)s + sizeof(t_shaders));
		s->nbr_fshaders = nbr_fshaders;
		s->vertex_shader = 0;
		return (s);
	}
	return (0);
}

t_shader			*init_shader(void (*shader)(t_shader *s, t_render *r,
	t_obj *o), unsigned int color, unsigned int
	(*blend)(unsigned int a, unsigned int b))
{
	t_shader	*s;

	if ((s = malloc(sizeof(t_shader))))
	{
		s->enabled = 1;
		s->color_base = color;
		s->color_render = color;
		s->blend = blend;
		s->exec = shader;
		return (s);
	}
	return (NULL);
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
	{
		s->shader[i]->exec(s->shader[i], r, o);
		++i;
	}
	return ((i != 0));
}

unsigned int		compute_color_shaders(t_shaders *s)
{
	unsigned int	i;
	unsigned int	color;

	if (!s)
		return (1);
	i = 0;
	color = 0;
	while (i < s->nbr_fshaders)
	{
		if (s->shader[i]->enabled)
		{
			if (!i)
				color = s->shader[i]->color_render;
			else
			{
				color = s->shader[i]->blend(color,
					s->shader[i]->color_render);
			}
			s->shader[i]->color_render = s->shader[i]->color_base;
		}
		++i;
	}
	return ((color > 0xFFFFFF ? 0xFFFFFF : color));
}

void				shaders_activate_all(t_shaders *s)
{
	unsigned int	i;

	i = 0;
	while (i < s->nbr_fshaders)
		s->shader[i++]->enabled = 1;
}

void				shaders_activate_only(t_shaders *s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < s->nbr_fshaders)
	{
		s->shader[i]->enabled = (i == n) ? 1 : 0;
		i++;
	}
}
