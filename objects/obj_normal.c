/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:29:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/21 15:35:54 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "texture.h"
#include "mesh.h"
#include "sda.h"

t_texture	*rt_obj_get_normal(t_obj *obj)
{
	if (!(obj->cfgbits & SDB_NORMAL))
		return (NULL);
	if (obj->type == PLAN)
		return (((t_plan*)obj->content)->normal);
	if (obj->type == SPHERE)
		return (((t_sphere*)obj->content)->normal);
	if (obj->type == CUBE)
		return (((t_cube*)obj->content)->normal);
	if (obj->type == CONE)
		return (((t_cone*)obj->content)->normal);
	if (obj->type == TRIANGLE)
		return (((t_triangle*)obj->content)->normal);
	if (obj->type == MESH)
		return (((t_mesh*)obj->content)->normal);
	return (NULL);
}

int			rt_obj_set_normal(t_obj *obj, t_texture *tex)
{
	if (obj->type == PLAN)
		((t_plan*)obj->content)->normal = tex;
	else if (obj->type == SPHERE)
		((t_sphere*)obj->content)->normal = tex;
	else if (obj->type == CUBE)
		((t_cube*)obj->content)->normal = tex;
	else if (obj->type == CONE)
		((t_cube*)obj->content)->normal = tex;
	else if (obj->type == TRIANGLE)
		((t_triangle*)obj->content)->normal = tex;
	else if (obj->type == MESH)
		((t_mesh*)obj->content)->normal = tex;
	else
		return (0);
	return (1);
}
