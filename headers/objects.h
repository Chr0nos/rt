/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:14:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 19:12:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "draw.h"
# include "forms.h"
# include "rt.h"

struct s_shaders;
struct s_rt;

enum	e_obj_flags
{
	FLAG_CSG_NEGATIVE = 1,
	FLAG_CSG_NONE = 1 << 1
};

enum	e_flag_intersect
{
	INTER_IN = 1,
	INTER_OUT = 1 << 2
};

typedef struct			s_obj
{
	t_type				type;
	t_uint				id;
	size_t				cfgbits;
	int					flags;
	t_mattf				trans;
	t_v4d				rotation;
	t_box				bounds;
	t_box				hitbox;
	struct s_obj		*parent;
	struct s_obj		*childs;
	struct s_obj		*next;
	void				*content;
	int					(*inters)(struct s_obj *, t_ray *, t_intersect *);
	t_v4d				(*normal)(struct s_obj *, t_v4d *inter);
	struct s_shaders	*shader;
	double				refractive_index;
	char				*name;
	t_limit				*limits;
}						t_obj;

typedef struct			s_obj_lookup
{
	unsigned int		type;
	unsigned int		lock;
	t_obj				*current;
	t_obj				*next;
}						t_obj_lookup;

struct s_rt;

t_obj					*rt_obj_init(t_obj *obj, int type);
t_obj					*rt_obj_nparent(t_obj *obj, unsigned int n);
t_obj					*rt_obj_addchild(t_obj *parent, t_obj *child);
t_obj					*rt_obj_delchild(t_obj *parent, t_obj *child);
t_obj					*rt_obj_getcamera(t_obj *obj);
t_obj					*rt_obj_rotate(t_obj *obj, const t_v4d radians);
t_obj					*rt_obj_rotate_force(t_obj *obj, const t_v4d radians);
t_obj					*rt_obj_byid(t_obj *node, const unsigned int id);
t_obj					*rt_obj_byname(t_obj *node, const char *name);
t_obj					*rt_obj_copy(const t_obj *src, t_obj *parent);
t_obj					*rt_obj_copy_node(t_obj *node, t_obj *parent);
void					rt_obj_init_shader(t_obj *obj);
int						rt_obj_set_reflect(t_obj *obj, unsigned char reflect);
unsigned char			rt_obj_get_reflect(const t_obj *obj);
t_texture				*rt_obj_get_texture(t_obj *obj);
int						rt_obj_set_texture(t_obj *obj, t_texture *tex);
t_texture				*rt_obj_get_normal(t_obj *obj);
int						rt_obj_set_normal(t_obj *obj, t_texture *tex);
unsigned int			rt_obj_get_lvl(t_obj *obj);
t_obj					*rt_obj_get_root(t_obj *obj);
unsigned int			rt_obj_count(t_obj *obj, unsigned int type_mask);
t_obj					*rt_obj_atpx(struct s_rt *rt, t_v2i px);
t_obj					*rt_obj_atpx_real(struct s_rt *rt, t_ray *ray);
t_obj					*rt_obj_nexttype(t_obj *node, t_obj *current,
	unsigned int type);

#endif
