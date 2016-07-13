/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 18:17:49 by alhote            #+#    #+#             */
/*   Updated: 2016/07/13 21:24:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "draw.h"
# include "objects.h"
# include "texture.h"
# include "tree.h"

# define PREFIX 1
# define INFIX 2
# define SUFFIX 4

typedef enum	e_rendflag
{
	RTMODE = 1,
	GLPREVMODE = 2,
	GLRENDMODE = 3,
	PTMODE = 4,
	MODE = 0xff,
	AO = 1 << 8,
	ALT_LIGHT_EQ = 1 << 9
}				t_rendflag;

typedef struct	s_rtcfg
{
	double		ambiant_light;
	t_rendflag	mode;
	char		max_reflects;
}				t_rtcfg;

typedef struct	s_menu
{
	t_point		items;
	t_point		thumb;
	SDL_Rect	*positions;
	SDL_Surface	*background;
}				t_menu;

typedef struct	s_rt
{
	t_draw		sys;
	t_obj		*root;
	t_rtree		tree;
	int			keyboard;
	int			mouse;
	t_rtcfg		settings;
	struct s_rt	*rts;
	size_t		rts_size;
	t_menu		menu;
	t_texture	*textures;
}				t_rt;

void			rt_putbits(unsigned int bits);
void			rt_configure(t_rt *rt);
int				rt_create_window(t_rt *rt);
int				rt_start(t_rt *rt);
void			rt_puttype(int type);
t_type			rt_gettype(const char *str);

int				getkeybit(const int keycode);
int				keydown(int keycode, t_rt *rt);
int				keyrlz(int keycode, t_rt *rt);
int				mouseclick(SDL_Event *event, t_rt *rt);
int				sdl_event(SDL_Event *event, t_rt *rt);
int				rt_event_resize(SDL_Event *event, t_rt *rt);

void			rt_putbounds(t_obj *obj, unsigned int p);
void			rt_debug(t_obj *item, unsigned int level);
t_obj			*rt_factory_alloc(enum e_type type, t_obj *parent);
unsigned int	rt_factory_getuid(void);
t_uint			rt_sizeobj(t_type type);

t_uint			rt_render(t_rt *rt, t_ray *ray);

int				rt_checkcamera(t_rt *rt);
int				check_cube(const t_box *a, const t_box *b);
void			update_cube(t_box *a, const t_box *b);

void			rt_update_camera(t_v2i geometry, t_camera *cam);
int				camera_reset(t_rt *rt);
void			camera_save(t_rt *rt);

void			rt_box_update(t_obj *obj);
void			rt_bounds_update(t_obj *node);
int				raybox_check(t_ray *r, t_box *box);

void			rt_rays(t_rt *rt);

void			rt_node_free(t_obj *node);
int				rt_node_foreach(t_obj *node, int mode,
int				(*f)(t_obj*, int, void*), void *userdata);
int				rt_node_count(t_obj *node, int mode, void *userdata);
int				rt_node_display(t_obj *obj, int mode, void *userdata);
int				yolo_setup_realpos(t_obj *obj, int mode, void *userdata);
int				yolo_setup_type(t_obj *obj, int mode, void *userdata);

double			rad2deg(double rad);
float			rad2degf(float rad);
double			deg2rad(double deg);
float			deg2radf(float deg);

int				display(t_rt *rt);
int				movemyass(t_rt *rt);
void			camera_rotate(t_rt *rt, const double x, const int dir);

int				rt_sphere_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_sphere_normal(t_obj *obj, t_v4d *v);
int				rt_plane_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_plane_normale(t_obj *obj, t_v4d *v);
int				rt_cube_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_cube_normale(t_obj *obj, t_v4d *v);
int				rt_cone_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_cone_normale(t_obj *obj, t_v4d *v);
int				rt_cone_inf_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_cone_inf_normale(t_obj *obj, t_v4d *v);
int				rt_cyl_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_cyl_normale(t_obj *obj, t_v4d *v);
int				rt_tore_inter(t_obj *obj, t_ray *r, t_v4d *v);
t_v4d			rt_tore_normale(t_obj *obj, t_v4d *v);

#endif
