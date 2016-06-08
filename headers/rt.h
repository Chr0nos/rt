/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:37:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 18:53:52 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "draw.h"
# include "forms.h"
# define PREFIX 1
# define INFIX 2
# define SUFFIX 4

typedef struct	s_rt
{
	t_draw		sys;
	t_obj		*root;
	int			keyboard;
	int			mouse;
}				t_rt;

void			rt_puttype(int type);

int				keydown(int keycode, t_rt *rt);
int				keyrlz(int keycode, t_rt *rt);
int				mouseclick(SDL_Event *event, t_rt *rt);
int				sdl_event(SDL_Event *event, t_rt *rt);

void			rt_debug(t_obj *item, unsigned int level);
t_obj			*rt_factory_alloc(enum e_type type, t_obj *parent);
t_uint			rt_sizeobj(t_type type);

int				check_cube(const t_box *a, const t_box *b);
void			update_cube(t_box *a, const t_box *b);

t_obj			*rt_obj_nparent(t_obj *obj, unsigned int n);
t_obj			*rt_obj_addchild(t_obj *parent, t_obj *child);
void			rt_obj_free(t_obj *obj, unsigned int level);
t_obj			*rt_obj_makeroot(void);
t_obj			*rt_obj_delchild(t_obj *parent, t_obj *child);
t_obj			*rt_obj_getcamera(t_obj *obj);
void			rt_update_camera(t_v2i geometry, t_camera *cam);

t_obj			*parse_yolo(const char *filepath);
int				yolo_setup(t_obj *obj, size_t ac, char **av);

void			rt_box_update(t_obj *obj);
void			rt_bounds_update(t_obj *node);
int				raybox_check(t_ray *r, t_box *box);

void			rt_rays(t_rt *rt);

int				rt_node_foreach(t_obj *node, int mode,
	int (*f)(t_obj*, int, void*), void *userdata);
void			rt_putbounds(t_obj *obj, void *userdata);
int				rt_node_count(t_obj *node, int mode, void *userdata);
int				rt_node_display(t_obj *obj, int mode, void *userdata);
int				rt_render_foreach(t_obj *obj, int mode, void *userdata);
int				yolo_setup_realpos(t_obj *obj, int mode, void *userdata);
int				yolo_setup_type(t_obj *obj, int mode, void *userdata);

t_uint			rt_render(t_rt *rt, t_ray *ray);

double			rad2deg(double rad);
float			rad2degf(float rad);
double			deg2rad(double deg);
float			deg2radf(float deg);

int				display(t_rt *rt);
int				movemyass(t_rt *rt);
void			camera_rotate(t_rt *rt, const double x, const int dir);

int				rt_sphere_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_sphere_normal(t_obj *obj, t_v4d *v);

#endif
