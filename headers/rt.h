/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 18:17:49 by alhote            #+#    #+#             */
/*   Updated: 2016/09/12 15:54:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "draw.h"
# include "objects.h"
# include "texture.h"
# include "interface.h"
# include "tree.h"
# include <pthread.h>

# define PREFIX 1
# define INFIX 2
# define SUFFIX 4
# define RT_CFGB_FREESCREEN 	1u
# define RT_CFGB_FULLSCREEN		(1u << 1)
# define RT_CFGB_NOREFRESHX 	(1u << 2)
# define RT_CFGB_INMENU			(1u << 3)
# define RT_CFGB_REFRESHINTER	(1u << 4)
# define RT_CFGB_INTERFEDIT		(1u << 5)

typedef enum	e_rendflag
{
	RTMODE = 1,
	GLPREVMODE = 2,
	GLRENDMODE = 3,
	PTMODE = 4,
	ALTERNATIVEMODE = 5,
	MODE = 0xff,
	MODEFLAG = 0x7fffff00,
	AO = 1 << 8,
	ALT_LIGHT_EQ = 1 << 9
}				t_rendflag;

typedef struct	s_menu_id
{
	void			*dest;
	const void		*src;
	const char		*file;
	int				id;
	int				enabled;
	pthread_t		thread;
}				t_menu_id;

typedef struct	s_menu
{
	t_v2i			items;
	t_v2i			thumb;
	SDL_Rect		*positions;
	SDL_Surface		*background;
	t_menu_id		*id;
}				t_menu;

typedef struct	s_rtcfg
{
	unsigned int	cfgbits;
	unsigned int	ambiant_light;
	t_rendflag		mode;
	char			max_reflects;
	unsigned int	bgcolor;
	unsigned int	default_color;
	unsigned char	default_reflect;
	float			default_size;
	unsigned char	fake_texture_load;
	t_texture		*skybox;
}				t_rtcfg;

typedef struct s_interface	t_interf;

typedef struct	s_rt
{
	t_draw			sys;
	t_obj			*root;
	t_rtree			tree;
	int				keyboard;
	int				mouse;
	t_rtcfg			settings;
	struct s_rt		*rts;
	size_t			rts_size;
	t_menu			menu;
	t_texture		**textures;
	t_interf		interf;
	t_uint			(*rayfunc)(struct s_rt *rt, t_ray *ray);
	SDL_Surface		*render_screen;
}				t_rt;

void			rt_putbits(size_t bits);
void			rt_configure(t_rt *rt);
int				rt_create_window(t_rt *rt);
int				rt_start(t_rt *rt);
char			*search_str_type(int type);
void			rt_puttype(int type, const int fd);
t_type			rt_gettype(const char *str);

/*
** events
*/

int				getkeybit(const int keycode);
int				keydown(int keycode, t_rt *rt);
int				keyrlz(int keycode, t_rt *rt);
int				mouseclick(SDL_Event *event, t_rt *rt);
int				sdl_event(SDL_Event *event, t_rt *rt);
int				rt_event_resize(SDL_Event *event, t_rt *rt);
int				toggle_key(int keycode, t_rt *rt);

void			rt_putbounds(t_obj *obj, unsigned int p);
void			rt_debug(t_obj *item, unsigned int level);
t_obj			*rt_factory_alloc(enum e_type type, t_obj *parent);
unsigned int	rt_factory_getuid(void);
t_uint			rt_sizeobj(t_type type);

void			rt_render(t_rt *rt);
t_uint			rt_render_ray(t_rt *rt, t_ray *ray);
t_uint			rt_render_bray(t_rt *rt, t_ray *ray);

int				rt_checkcamera(t_rt *rt);
int				check_cube(const t_box *a, const t_box *b);
void			update_cube(t_box *a, const t_box *b);

void			rt_update_camera(t_v2i geometry, t_camera *cam);
int				camera_reset(t_rt *rt);
void			camera_save(t_rt *rt);
int				camera_switch(t_rt *rt);

void			rt_box_update(t_obj *obj);
void			rt_bounds_update(t_obj *node);
int				raybox_cube_check(t_ray *r, t_box *box);

void			rt_rays(t_rt *rt);

void			rt_node_free(t_obj *node);
int				rt_node_foreach(t_obj *node, int mode,
	int (*f)(t_obj*, int, void*), void *userdata);
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

int				rt_sphere_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_sphere_normal(t_obj *obj, t_v4d *v);
int				rt_plane_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_plane_normale(t_obj *obj, t_v4d *v);
int				rt_cube_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_cube_normale(t_obj *obj, t_v4d *v);
int				rt_cone_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_cone_normale(t_obj *obj, t_v4d *v);
int				rt_cone_inf_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_cone_inf_normale(t_obj *obj, t_v4d *v);
int				rt_cyl_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_cyl_normale(t_obj *obj, t_v4d *v);
int				rt_tore_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_tore_normale(t_obj *obj, t_v4d *v);
int				rt_triangle_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_triangle_normale(t_obj *obj, t_v4d *v);
int				rt_mesh_inter(t_obj *obj, t_ray *r, t_intersect *v);
t_v4d			rt_mesh_normale(t_obj *obj, t_v4d *v);

int				rt_export_bmp(t_rt *rt, int ac, char **av);
int				rt_export(t_rt *rt, int ac, char **av);
int				rt_normal(t_rt *rt, const char *path);

int				rt_quit(t_rt *rt, int retcode);
int				sdl_flush(const t_rt *rt);
int				togglefs(t_rt *rt);
char			rt_rays_pc(const t_v2i *geometry,
	const t_v2i *px);
int				rt_event_resize_force(t_v2i geometry, t_rt *rt);
void			rt_configure_interface(t_interf *interf);
int				main(int ac, char **av);

#endif
