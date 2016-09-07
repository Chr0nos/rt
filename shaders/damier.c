/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 15:26:30 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/06 15:00:31 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "draw.h"
#include <math.h>

void		shader_damier(t_shader *s, t_render *r, t_obj *light,
		t_uint *color_render)
{
	t_uint	p[3];
	t_uint	color[2];

	(void)s;
	(void)light;
	color[0] = blend_multiply(((t_cube*)r->obj_intersect->content)->color,
			0x00e0e0e0);
	color[1] = blend_add(((t_cube*)r->obj_intersect->content)->color, 0x353535);
	p[0] = (t_uint)(round(r->intersection.x * 0.5 + 0.0001));
	p[1] = (t_uint)(round(r->intersection.y * 0.5 + 0.0001));
	p[2] = (t_uint)(round(r->intersection.z * 0.5 + 0.0001));
	if ((p[2] % 2))
	{
		if ((p[0] % 2 && p[1] % 2) || (!(p[0] % 2) && !(p[1] % 2)))
			*color_render = color[0];
		else
			*color_render = color[1];
	}
	else
	{
		if ((p[0] % 2 && p[1] % 2) || (!(p[0] % 2) && !(p[1] % 2)))
			*color_render = color[1];
		else
			*color_render = color[0];
	}
}
