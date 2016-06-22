/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:00:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/22 17:49:01 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"
#include "shaders.h"

t_obj		*rt_obj_init(t_obj *obj, t_type type)
{
	obj->id = 0;
	obj->type = type;
	obj->next = NULL;
	obj->childs = NULL;
	obj->content = NULL;
	obj->trans = draw_make_matrix_m4_identity();
	obj->bounds = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->rotation = (t_v4d){0.0, 0.0, 0.0, 0.0};
	obj->inters = NULL;
	obj->normal = NULL;
	obj->parent = NULL;
	obj->texture = 0;
	obj->shader = init_shader(2);
	obj->shader->fragment_shader[0] = &rt_specular_pow;
	obj->shader->fragment_shader[1] = &rt_light_pow;
	return (obj);
}
