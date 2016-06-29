/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:00:29 by snicolet          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/06/28 22:57:42 by alhote           ###   ########.fr       */
=======
/*   Updated: 2016/06/29 12:18:22 by dboudy           ###   ########.fr       */
>>>>>>> c588ca7c5ceb4dda59b7add0e22d6de946b2ba18
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"
#include "shaders.h"

t_obj		*rt_obj_init(t_obj *obj, int type)
{
	obj->id = 0;
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
		obj->shader = init_shader(2);
		obj->shader->fragment_shader[1] = &rt_specular_pow;
		obj->shader->fragment_shader[0] = &rt_light_pow;
	}
	else
		obj->shader = NULL;
	return (obj);
}
