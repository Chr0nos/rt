/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:42:49 by alhote            #+#    #+#             */
/*   Updated: 2018/12/28 02:11:59 by snicolet         ###   ########.fr       */
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
	t_v4d					bary;
	t_v2f					result;
	const struct s_triangle	*tri = obj->content;

	bary = geo_barycentric_coordinates(
		geo_addv4(obj->trans.w, tri->v1.pos),
		geo_addv4(obj->trans.w, tri->v2.pos),
		geo_addv4(obj->trans.w, tri->v3.pos),
		p);
	result = (t_v2f){
		(float)(bary.x * (double)tri->v1.uv.x +
		bary.y * (double)tri->v2.uv.x + bary.z *
		(double)tri->v3.uv.x), (float)(bary.x *
			(double)tri->v1.uv.y + bary.y *
			(double)tri->v2.uv.y + bary.z *
			(double)tri->v3.uv.y)
	};
	result.y = 1.0f - result.y;
	return (result);
}
