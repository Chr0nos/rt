/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 20:51:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 11:05:08 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "parser.h"
#include "shaders.h"

int					yolo_setup_realpos(t_obj *obj, int mode, void *userdata)
{
	(void)userdata;
	(void)mode;
	if ((!obj->parent) || (obj->type == CAMERA))
		return (OK);
	obj->trans = geo_mk4_rotxyz(
		obj->rotation,
		(t_v4d){1.0, 1.0, 1.0, 1.0}, obj->trans.w);
	rt_box_update(obj);
	return (OK);
}

int					yolo_setup(t_obj *obj, size_t ac, char **av)
{
	int					p;
	const t_parser_cfg	parse[] = {
		(t_parser_cfg){SPHERE | CUBE, &yolo_setup_cube},
		(t_parser_cfg){CAMERA, &yolo_setup_camera},
		(t_parser_cfg){PLAN, &yolo_setup_plan},
		(t_parser_cfg){CONE, &yolo_setup_cone},
		(t_parser_cfg){CONE_INF, &yolo_setup_cone_inf},
		(t_parser_cfg){CYL, &yolo_setup_cyl},
		(t_parser_cfg){LIGHTTYPE, &yolo_setup_plight}
	};

	if (!ac)
		return (1);
	p = 7;
	while (p--)
		if (obj->type & parse[p].type)
			return (parse[p].config(obj, ac, av));
	return (0);
}
