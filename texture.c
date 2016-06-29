/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 14:42:09 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/29 14:21:23 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "texture.h"
#include "libft.h"
#include <math.h>

//CODE ILLISIBLE : a modifier !!! (ou delete)
//NE COMPILE PAS !!@!@
/*
static t_uint		rt_checker(t_obj *obj, t_render *r)
{
	t_v4d	tmp;

	tmp = (t_v4d){fabs(r->intersection.x / TILE_SIZE),
		ft_fabs(r->intersection.y / TILE_SIZE),
		ft_fabs(r->intersection.z / TILE_SIZE), 0};
	if (ft_ispair((int)tmp.z))
	{
		if ((ft_isodd((int)tmp.x) && ft_isodd((int)tmp.y))
				|| (ft_ispair((int)tmp.x) && ft_ispair((int)tmp.y)))
			return (((t_text *)obj->content)->color1);
		else
			return (((t_text *)obj->content)->color2);
	}
	else
	{
		if ((ft_isodd((int)tmp.x) && ft_isodd((int)tmp.y))
				|| (ft_ispair((int)tmp.x) && ft_ispair((int)tmp.y)))
			return (((t_text *)obj->content)->color2);
		else
			return (((t_text *)obj->content)->color1);
	}
}

t_uint	apply_texture(t_obj *obj, t_render *r)
{
	if (((t_text *)obj->content)->type == CHECKER)
		return (rt_checker(obj, r));
	else
		return (r->ray->color);
}
*/
