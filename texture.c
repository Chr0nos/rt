/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 14:42:09 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/28 17:11:19 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "libft.h"

double		rt_checker(t_render *r, t_obj *light)
{
	t_uint p[3];
	t_uint	color[2];

	(void)light;
	color[0] = (t_uint)(r->ray->color - r->ray->color * 0.5);
	color[1] = (t_uint)(r->ray->color + r->ray->color * 0.5);
	p[0] = (t_uint)(r->intersection.x / 2);
	p[1] = (t_uint)(r->intersection.y / 2);
	p[2] = (t_uint)(r->intersection.z / 2);
	if ((p[2] % 2))
	{
		if ((p[0] % 2 && p[1] % 2) || (!(p[0] % 2) && !(p[1] % 2)))
			r->ray->color = color[0];
		else
			r->ray->color = color[1];
	}
	else
	{
		if ((p[0] % 2 && p[1] % 2) || (!(p[0] % 2) && !(p[1] % 2)))
			r->ray->color = color[1];
		else
			r->ray->color = color[0];
	}
	return (0);
}
