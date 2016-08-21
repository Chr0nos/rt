/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:29:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/21 15:22:44 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "texture.h"
#include "sda.h"
#include "mesh.h"

t_texture	*rt_obj_get_texture(t_obj *obj)
{
	if (obj->type == PLAN)
		return (((t_plan*)obj->content)->texture);
	if (obj->type == SPHERE)
		return (((t_sphere*)obj->content)->texture);
	if (obj->type == CUBE)
		return (((t_cube*)obj->content)->texture);
	if (obj->type == CONE)
		return (((t_cone*)obj->content)->texture);
	if (obj->type == TRIANGLE)
		return (((t_triangle*)obj->content)->texture);
	if (obj->type == MESH)
		return (((t_mesh*)obj->content)->texture);
	return (NULL);
}

int			rt_obj_set_texture(t_obj *obj, t_texture *tex)
{
	if (obj->type == PLAN)
		((t_plan*)obj->content)->texture = tex;
	else if (obj->type == SPHERE)
		((t_sphere*)obj->content)->texture = tex;
	else if (obj->type == CUBE)
		((t_cube*)obj->content)->texture = tex;
	else if (obj->type == CONE)
		((t_cone*)obj->content)->texture = tex;
	else if (obj->type == TRIANGLE)
		((t_triangle*)obj->content)->texture = tex;
	else if (obj->type == MESH)
		((t_mesh*)obj->content)->texture = tex;
	else
		return (0);
	return (1);
}
