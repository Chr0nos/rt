/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:42:49 by alhote            #+#    #+#             */
/*   Updated: 2016/08/19 15:53:21 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"
#include "mesh.h"

t_v2f		get_uv_triangle(t_obj *obj, t_v4d i)
{
	t_v4d	f1;
	t_v4d	f2;
	t_v4d	f3;
	double	area;
	t_v4d	bary;

	area = fabs(geo_dotv4(geo_crossv4(
		geo_subv4(((t_triangle*)(obj->content))->v1.pos,
		((t_triangle*)(obj->content))->v2.pos),
		geo_subv4(((t_triangle*)(obj->content))->v3.pos,
		((t_triangle*)(obj->content))->v1.pos)), rt_triangle_normale(obj, &i)));
	f1 = geo_subv4(((t_triangle*)(obj->content))->v1.pos, i);
	f2 = geo_subv4(((t_triangle*)(obj->content))->v2.pos, i);
	f3 = geo_subv4(((t_triangle*)(obj->content))->v3.pos, i);
	bary.x = fabs(geo_dotv4(geo_crossv4(f2, f3),
	rt_triangle_normale(obj, &i))) / area;
	bary.y = fabs(geo_dotv4(geo_crossv4(f3, f1),
	rt_triangle_normale(obj, &i))) / area;
	bary.z = fabs(geo_dotv4(geo_crossv4(f1, f2),
	rt_triangle_normale(obj, &i))) / area;
	return ((t_v2f){
		(float)(bary.x * (double)((t_triangle*)(obj->content))->v1.uv.x +
		bary.y * (double)((t_triangle*)(obj->content))->v2.uv.x + bary.z *
		(double)((t_triangle*)(obj->content))->v3.uv.x), (float)(bary.x *
			(double)((t_triangle*)(obj->content))->v1.uv.y + bary.y *
			(double)((t_triangle*)(obj->content))->v2.uv.y + bary.z *
			(double)((t_triangle*)(obj->content))->v3.uv.y)
	});
}
