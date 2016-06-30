/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:00:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 18:16:36 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

t_obj		*rt_obj_init(t_obj *obj, int type)
{
	obj->id = 0;
	obj->cfgbits = 0;
	obj->type = (t_type)(type & ~NOSHADER);
	obj->next = NULL;
	obj->childs = NULL;
	obj->content = NULL;
	obj->trans = geo_mk4_identity();
	obj->bounds = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->rotation = (t_v4d){0.0, 0.0, 0.0, 0.0};
	obj->inters = NULL;
	obj->normal = NULL;
	obj->parent = NULL;
	obj->refractive_index = 1.05;
	if (!(type & VISIBLE))
		type |= NOSHADER;
	if (!(type & NOSHADER))
	{
		obj->shader = init_shaders(3);
		obj->shader->shader[2] = init_shader(&rt_specular_pow, 0x000000,
			&blend_lighten);
		obj->shader->shader[1] = init_shader(&rt_light_pow, 0x000000,
			&blend_multiply);
		obj->shader->shader[0] = init_shader(&shader_ambiant, 0x000000,
			&blend_add);
	}
	else
		obj->shader = NULL;
	return (obj);
}
