/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 14:42:09 by dboudy            #+#    #+#             */
/*   Updated: 2016/07/13 17:59:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "texture.h"
#include "libft.h"
#include "shaders.h"
#define TILE_SIZE 2.0

void			shader_damier(t_shader *s, t_render *r, t_obj *light)
{
	t_v4d	tmp;

	(void)light;
	tmp = (t_v4d){fabs(r->intersection.x / TILE_SIZE),
		fabs(r->intersection.y / TILE_SIZE),
		fabs(r->intersection.z / TILE_SIZE), 0};
	if ((int)tmp.z % 2)
	{
		if ((!((int)tmp.x % 2) && !((int)tmp.y % 2))
				|| ((int)tmp.x % 2 && (int)tmp.y % 2))
			s->color_render = 0xFFFFFF;//((t_text *)r->obj_intersect->content)->color1;
		else
			s->color_render = 0;//((t_text *)r->obj_intersect->content)->color2;
	}
	else
	{
		if ((!((int)tmp.x % 2) && !((int)tmp.y % 2))
				|| ((int)tmp.x % 2 && (int)tmp.y % 2))
			s->color_render = 0;//((t_text *)r->obj_intersect->content)->color2;
		else
			s->color_render = 0xFFFFFF;//((t_text *)r->obj_intersect->content)->color1;
	}
}
