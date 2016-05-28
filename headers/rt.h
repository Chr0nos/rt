/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:37:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/28 21:15:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "draw.h"
# include "forms.h"

typedef struct	s_rt
{
	t_draw		sys;
	t_obj		*root;
}				t_rt;

int				keydown(int keycode, t_rt *rt);
int				keyrlz(int keycode, t_rt *rt);
int				sdl_event(SDL_Event *event, t_rt *rt);

void			rt_debug(t_obj *item, unsigned int level);
t_obj			*rt_factory_alloc(enum e_type type, t_obj *parent);
t_uint			rt_sizeof(t_type type);

int				check_cube(const t_box *a, const t_box *b);
void			update_cube(t_box *a, const t_box *b);

t_obj			*rt_obj_nparent(t_obj *obj, unsigned int n);
t_obj			*rt_obj_addchild(t_obj *parent, t_obj *child);
void			rt_obj_free(t_obj *obj, unsigned int level);
t_obj			*rt_obj_makeroot(void);
t_obj			*rt_obj_delchild(t_obj *parent, t_obj *child);
t_obj			*rt_obj_getcamera(t_obj *obj);

t_obj			*parse_yolo(const char *filepath);
int				yolo_setup(t_obj *obj, size_t ac, char **av);

void			rt_box_update(t_obj *obj);

#endif
