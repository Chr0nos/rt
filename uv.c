/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:42:49 by alhote            #+#    #+#             */
/*   Updated: 2016/09/14 19:16:14 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "shaders.h"
#include "texture.h"
#include "libft.h"
#include "mesh.h"

t_v2f		get_uv_triangle(t_obj *obj, t_v4d p)
{
	t_v4d	bary;
	t_v2f	result;

	bary = geo_barycentric_coordinates(geo_addv4(obj->trans.w,
		((t_triangle*)(obj->content))->v1.pos),
	geo_addv4(obj->trans.w, ((t_triangle*)(obj->content))->v2.pos),
	geo_addv4(obj->trans.w, ((t_triangle*)(obj->content))->v3.pos), p);
	result = (t_v2f){
		(float)(bary.x * (double)((t_triangle*)(obj->content))->v1.uv.x +
		bary.y * (double)((t_triangle*)(obj->content))->v2.uv.x + bary.z *
		(double)((t_triangle*)(obj->content))->v3.uv.x), (float)(bary.x *
			(double)((t_triangle*)(obj->content))->v1.uv.y + bary.y *
			(double)((t_triangle*)(obj->content))->v2.uv.y + bary.z *
			(double)((t_triangle*)(obj->content))->v3.uv.y)
	};
	result.y = 1.0f - result.y;
	return (result);
}
