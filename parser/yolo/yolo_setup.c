/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 20:51:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 18:23:11 by alhote           ###   ########.fr       */
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
	obj->trans = draw_matrix_multiply_axes_m4(
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
		(t_parser_cfg){CYL, &yolo_setup_cyl},
		(t_parser_cfg){LIGHTTYPE, &yolo_setup_plight}
	};

	obj->shader = init_shader(1);
	obj->shader->fragment_shader[0] = &rt_light_pow;
	if (!ac)
		return (1);
	p = 6;
	while (p--)
		if (obj->type & parse[p].type)
			return (parse[p].config(obj, ac, av));
	return (0);
}
