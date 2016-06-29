/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 15:19:21 by alhote            #+#    #+#             */
/*   Updated: 2016/06/29 21:38:14 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"
#include "shaders.h"

void			shader_ambiant(t_shader *s, t_render *r, t_obj *light)
{
	(void)light;
	s->color_render =
	((((((t_cube*)(r->obj_intersect->content))->color & 0xFF0000)
	>> 16) / 1) << 16) +
	((((((t_cube*)(r->obj_intersect->content))->color & 0x00FF00)
	>> 8) / 1) << 8) +
	(((t_cube*)(r->obj_intersect->content))->color & 0x0000FF) / 1;
}
