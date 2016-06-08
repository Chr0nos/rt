/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 17:41:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 17:45:14 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		yolo_setup_type(t_obj *obj, int mode, void *userdata)
{
	(void)mode;
	(void)userdata;
	if (obj->type == SPHERE)
		obj->inters = &rt_sphere_inter;
	return (OK);
}
