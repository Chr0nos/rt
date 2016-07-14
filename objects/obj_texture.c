/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:29:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 17:34:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "texture.h"

t_texture	*rt_obj_get_texture(t_obj *obj)
{
	if (obj->type == PLAN)
		return (((t_plan*)obj->content)->texture);
	if (obj->type == SPHERE)
		return (((t_sphere*)obj->content)->texture);
	return (NULL);
}

int			rt_obj_set_texture(t_obj *obj, t_texture *tex)
{
	if (obj->type == PLAN)
		((t_plan*)obj->content)->texture = tex;
	else if (obj->type == SPHERE)
		((t_sphere*)obj->content)->texture = tex;
	else
		return (0);
	return (1);
}
