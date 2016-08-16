/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 17:41:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/16 12:44:54 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"

int		yolo_setup_type(t_obj *obj, int mode, void *userdata)
{
	unsigned int				p;
	const t_parser_internal		cfg[] = {
		(t_parser_internal){SPHERE, &rt_sphere_inter, &rt_sphere_normal},
		(t_parser_internal){PLAN, &rt_plane_inter, &rt_plane_normale},
		(t_parser_internal){CONE, &rt_cone_inter, &rt_cone_normale},
		(t_parser_internal){CONE_INF, &rt_cone_inf_inter, &rt_cone_inf_normale},
		(t_parser_internal){CYL, &rt_cyl_inter, &rt_cyl_normale},
		(t_parser_internal){CUBE, &rt_cube_inter, &rt_cube_normale},
		(t_parser_internal){TRIANGLE, &rt_triangle_inter, &rt_triangle_normale}
	};

	(void)mode;
	(void)userdata;
	p = 7;
	while (p--)
	{
		if (cfg[p].type == obj->type)
		{
			obj->inters = cfg[p].inters;
			obj->normal = cfg[p].normal;
			return (OK);
		}
	}
	return (OK);
}
