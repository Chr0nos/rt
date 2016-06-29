/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:14:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 11:38:38 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "draw.h"
# include "forms.h"

struct s_shaders;

typedef struct			s_obj
{
	t_type				type;
	t_uint				id;
	t_mattf				trans;
	t_v4d				rotation;
	t_box				bounds;
	t_box				hitbox;
	struct s_obj		*parent;
	struct s_obj		*childs;
	struct s_obj		*next;
	void				*content;
	int					(*inters)(struct s_obj *, t_ray *, t_v4d *);
	t_v4d				(*normal)(struct s_obj *, t_v4d *inter);
	struct s_shaders	*shader;
	double				refractive_index;
}						t_obj;

t_obj					*rt_obj_init(t_obj *obj, int type);
t_obj					*rt_obj_nparent(t_obj *obj, unsigned int n);
t_obj					*rt_obj_addchild(t_obj *parent, t_obj *child);
t_obj					*rt_obj_delchild(t_obj *parent, t_obj *child);
t_obj					*rt_obj_getcamera(t_obj *obj);
t_obj					*rt_obj_rotate(t_obj *obj, const t_v4d radians);
t_obj					*rt_obj_byid(t_obj *node, const unsigned int id);

#endif
