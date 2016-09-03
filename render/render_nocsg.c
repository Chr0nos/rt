/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_nocsg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 10:48:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 10:48:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** standard rendering mode, withous any csg
*/

void				rt_render_nocsg(t_obj *obj, t_render *r, t_intersect *v)
{
	if (r->ray->lenght >= r->lowest_lenght)
		return ;
	r->obj_intersect = obj;
	r->intersection = v->in;
	r->lowest_lenght = r->ray->lenght;
}
