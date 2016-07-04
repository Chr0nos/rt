/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hantlowt <hantlowt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:00:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/04 19:34:16 by hantlowt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

static void		rt_obj_init_shader(t_obj *obj)
{
	obj->shader = init_shaders();
	init_shader(obj->shader, &shader_ambiant, 0x000000,
		&blend_add);
	init_shader(obj->shader, &rt_light_pow, 0x000000,
		&blend_multiply);
	init_shader(obj->shader, &rt_specular_pow, 0x000000,
		&blend_add);
	//init_shader(&shader_shadow, 0xFFFFFF,
	//		&blend_darken);
}

t_obj			*rt_obj_init(t_obj *obj, int type)
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
		rt_obj_init_shader(obj);
	else
		obj->shader = NULL;
	return (obj);
}
