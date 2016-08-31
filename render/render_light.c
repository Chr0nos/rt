/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 17:47:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/31 16:51:33 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rt.h"
#include "shaders.h"

/*
** called on EACH spot
** by rt_render_foreach
*/

int				rt_render_light(t_obj *obj, int mode, void *userdata)
{
	t_render	*r;
	t_ray		origin;

	(void)mode;
	r = userdata;
	origin = *r->ray;
	shaders_exec(r->obj_intersect->shader, r, obj, r->colors_renders);
	*r->ray = origin;
	return (OK);
}
