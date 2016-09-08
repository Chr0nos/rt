/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:00:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/07 14:46:51 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "libft.h"
#include "sda.h"

void			rt_obj_init_shader(t_obj *obj)
{
	if (!(obj->shader = shaders_init()))
	{
		ft_putendl_fd("error: failed to malloc shaders", 2);
		return ;
	}
	shader_init(obj->shader, &shader_texture, 0xFF000000, &blend_normal);
	shader_init(obj->shader, &shader_normalmap, 0xFF000000, &blend_add);
	shader_init(obj->shader, &rt_light_pow, 0xFF2E2E2E, &blend_multiply);
	shader_init(obj->shader, &shader_reflection, 0xFF000000, &blend_add);
	shader_init(obj->shader, &shader_shadow, 0xFF000000, &blend_normal);
	shader_init(obj->shader, &rt_specular_pow, 0xFF000000, &blend_add);
	shader_init(obj->shader, &shader_damier, 0xFF000000, &blend_multiply);
	sda_setup_sdisable_real(obj->shader->shader,
		(void*)(unsigned long)&shader_damier);
}

t_obj			*rt_obj_init(t_obj *obj, int type)
{
	obj->id = 0;
	obj->cfgbits = 0;
	obj->flags = 0;
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
	obj->name = NULL;
	obj->refractive_index = 1.0;
	if (!(type & VISIBLE))
		type |= NOSHADER;
	if (!(type & NOSHADER))
		rt_obj_init_shader(obj);
	else
		obj->shader = NULL;
	return (obj);
}
