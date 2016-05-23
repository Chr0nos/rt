/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 21:03:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/23 21:59:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_box_update(t_obj *obj)
{
	const t_v3f		*p = &obj->trans.offset;
	float			r;

	if (obj->type == CUBE)
	{
		r = ((t_cube*)(obj->content))->size / 2;
		obj->hitbox = (t_box){p->x - r, p->x + r, p->y - r, p->y + r,
			p->z - r, p->z + r};
	}
	else if (obj->type == SPHERE)
	{
		r = ((t_sphere*)(obj->content))->radius;
		obj->hitbox = (t_box){p->x - r, p->x + r, p->y - r, p->y + r,
			p->z - r, p->z + r};
	}
	else
		obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
}
