/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:57:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/10 01:42:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDA_H
# define SDA_H
# define SDA_SETUP_TYPES 26
# define SDA_COUNT_SHADER 6
# define SDA_COUNT_DEFAULTS 8
# define T t_sda_cfg
# define FLOATCMP(x, y) ((x > y) || (x < y))
# include "forms_bits.h"
# include "sda_bits.h"

typedef	struct s_rt			t_rt;
typedef struct s_triangle	t_triangle;
typedef struct s_mesh		t_mesh;
typedef struct s_shader		t_shader;

typedef struct			s_sda_eval
{
	int					fd;
	t_rt				*rt;
	t_obj				*root;
	t_obj				*current_obj;
	int					last_lvl;
	int					lvl_offset;
}						t_sda;

typedef struct			s_sda_export
{
	const struct s_sda_cfg	*cfg;
	t_setting				*setting;
	t_obj					*setting_obj;
	char					*tbl;
	const int				fd;
}						t_sda_export;

typedef	struct			s_sda_shader
{
	const char			*name;
	void				*shader;
}						t_sda_shader;

typedef struct			s_sda_cfg
{
	const char			*str;
	int					(*config)(t_sda *, t_obj *, char **);
	char				*(*export)(t_obj *, t_sda_export *);
	enum e_sda_setting	obj_valid_type;
	int					argc;
	size_t				bit;
}						t_sda_cfg;

typedef struct			s_sda_obj
{
	int					ac;
	char				**av;
	t_v4d				*v;
	t_v4d				*n;
	t_v2f				*uv;
	size_t				size_v;
	size_t				select_v;
	size_t				size_n;
	size_t				select_n;
	size_t				size_uv;
	size_t				select_uv;
	t_obj				*parent;
	t_mesh				*mesh;
	t_obj				*mesh_obj;
}						t_sda_obj;

typedef struct			s_sda_default
{
	unsigned int		type_mask;
	void				(*exec)(struct s_rt *, t_obj *);
}						t_sda_default;

int						sda_lvl(char *line);
t_obj					*sda_parse(const char *filepath, t_rt *rt);
int						sda_eval(const char *line, t_sda *e,
	const int lvl);
int						sda_settings(t_sda *e, int ac, char **av);
void					sda_settings_stack(t_obj *stack, t_obj *s);
void					sda_set_defaults(t_obj *root, t_rt *rt);
t_obj					*sda_parse_rawtree(const char *filepath, t_rt *rt,
	t_obj *root, int lvl_offset);
char					*sda_double_short(char *s);
void					sda_sdisable_init(t_sda_shader *x);
t_texture				*sda_setup_texture_fake(char *filepath,
	t_texture **textures);
char					*sda_export_bitmap(SDL_Surface *surface,
		unsigned int *size);
int						sda_export_bitmap_file(const char *filepath,
	SDL_Surface *surface);
int						sda_setup_sdisable_real(t_shader *shader, void *target);
int						sda_spliter(const char *line, char ***av, int *ac);
void					*sda_setup_getshader_addr(t_shader *s, void *item);
const t_sda_cfg			*sda_settings_bysetup(const void *setup);
t_uint					sda_setup_color_text(const char *str, unsigned int mask,
	unsigned int color, int deca);
/*
** exporter
*/

int						sda_export_file(const char *filepath);
void					sda_export_color_raw(unsigned int color,
	char *color_str);
void					sda_export(const t_rt *rt, const int fd);
char					*sda_export_ntab(unsigned int lvl);
char					*sda_export_xyz(const t_v4d *v, char radians);
char					*sda_export_pos(t_obj *obj, t_sda_export *e);
char					*sda_export_rot(t_obj *obj, t_sda_export *e);
char					*sda_export_color(t_obj *obj, t_sda_export *e);
char					*sda_export_color_r(t_obj *obj, t_sda_export *e);
char					*sda_export_color_g(t_obj *obj, t_sda_export *e);
char					*sda_export_color_b(t_obj *obj, t_sda_export *e);
char					*sda_export_size(t_obj *obj, t_sda_export *e);
char					*sda_export_texture(t_obj *obj, t_sda_export *e);
char					*sda_export_normal(t_obj *obj, t_sda_export *e);
char					*sda_export_refract(t_obj *obj, t_sda_export *e);
char					*sda_export_intensity(t_obj *obj, t_sda_export *e);
char					*sda_export_name(t_obj *obj, t_sda_export *e);
char					*sda_export_angle(t_obj *obj, t_sda_export *e);
char					*sda_export_reflect(t_obj *obj, t_sda_export *e);
char					*sda_export_skybox(t_obj *obj, t_sda_export *e);
char					*sda_export_sdisable(t_obj *obj, t_sda_export *e);
char					*sda_export_al(t_obj *obj, t_sda_export *e);
char					*sda_export_vertex0(t_obj *obj, t_sda_export *e);
char					*sda_export_vertex1(t_obj *obj, t_sda_export *e);
char					*sda_export_vertex2(t_obj *obj, t_sda_export *e);
char					*sda_export_obj(t_obj *obj, t_sda_export *e);
char					*sda_export_background(t_obj *obj, t_sda_export *e);
char					*sda_export_senable(t_obj *obj, t_sda_export *e);

/*
** configure functions
*/

int						sda_setup_alpha(t_sda *e, t_obj *obj, char **av);
int						sda_setup_color_r(t_sda *e, t_obj *obj, char **av);
int						sda_setup_color_g(t_sda *e, t_obj *obj, char **av);
int						sda_setup_color_b(t_sda *e, t_obj *obj, char **av);
int						sda_setup_color(t_sda *e, t_obj *obj, char **av);
int						sda_setup_pos(t_sda *e, t_obj *obj, char **av);
int						sda_setup_pos_x(t_sda *e, t_obj *obj, char **av);
int						sda_setup_pos_y(t_sda *e, t_obj *obj, char **av);
int						sda_setup_pos_z(t_sda *e, t_obj *obj, char **av);
int						sda_setup_al(t_sda *e, t_obj *obj, char **av);
int						sda_setup_rot(t_sda *e, t_obj *obj, char **av);
int						sda_setup_rot_x(t_sda *e, t_obj *obj, char **av);
int						sda_setup_rot_y(t_sda *e, t_obj *obj, char **av);
int						sda_setup_rot_z(t_sda *e, t_obj *obj, char **av);
int						sda_setup_fov(t_sda *e, t_obj *obj, char **av);
int						sda_setup_size(t_sda *e, t_obj *obj, char **av);
int						sda_setup_intensity(t_sda *e, t_obj *obj, char **av);
int						sda_setup_refract(t_sda *e, t_obj *obj, char **av);
int						sda_setup_include(t_sda *e, t_obj *obj, char **av);
int						sda_setup_angle(t_sda *e, t_obj *obj, char **av);
int						sda_setup_copy(t_sda *e, t_obj *obj, char **av);
int						sda_setup_name(t_sda *e, t_obj *obj, char **av);
int						sda_setup_texture(t_sda *e, t_obj *obj, char **av);
int						sda_setup_normal(t_sda *e, t_obj *obj, char **av);
int						sda_setup_reflect(t_sda *e, t_obj *obj, char **av);
int						sda_setup_background(t_sda *e, t_obj *obj, char **av);
int						sda_setup_skybox(t_sda *e, t_obj *obj, char **av);
int						sda_setup_sdisable(t_sda *e, t_obj *obj, char **av);
int						sda_setup_heightmap(t_sda *e, t_obj *obj, char **av);
int						sda_setup_texture_perlin(t_sda *e, t_obj *obj,
	char **av);
int						sda_setup_vertex_0(t_sda *e, t_obj *obj, char **av);
int						sda_setup_vertex_1(t_sda *e, t_obj *obj, char **av);
int						sda_setup_vertex_2(t_sda *e, t_obj *obj, char **av);
int						sda_setup_obj(t_sda *e, t_obj *obj, char **av);
int						sda_setup_csg(t_sda *e, t_obj *obj, char **av);
int						sda_setup_senable(t_sda *e, t_obj *obj, char **av);

/*
** sda default functions
*/

void					sda_default_lights(struct s_rt *rt, t_obj *obj);
void					sda_default_camera(struct s_rt *rt, t_obj *obj);
void					sda_default_setting(struct s_rt *rt, t_obj *obj);
void					sda_default_triangle(struct s_rt *rt, t_obj *obj);
void					sda_default_cone(struct s_rt *rt, t_obj *obj);
void					sda_default_shaders(struct s_rt *rt, t_obj *obj);
void					sda_default_texture(struct s_rt *rt, t_obj *obj);
void					sda_default_size(struct s_rt *rt, t_obj *obj);

/*
** Obj parser, it is in the sda because of his strong implication with the
** sda configurations bits system
*/

int						parse_obj(t_obj *obj, const char *filepath);
int						parse_obj_dispatch(t_sda_obj *s, char *line);
int						parse_obj_n(t_sda_obj *s);
int						parse_obj_uv(t_sda_obj *s);
int						parse_obj_v(t_sda_obj *s);
int						parse_obj_f(t_sda_obj *s);
unsigned int			obj_max(int x, const unsigned int max);
void					parse_obj_setcfgbits(t_obj *t, const t_sda_obj *s,
	t_triangle *c);
int						parse_obj_checksplit(char ***split, int min);

static const t_sda_cfg	g_sda_cfg[SDA_SETUP_TYPES] = {
	(T){"color:", &sda_setup_color, &sda_export_color, SDA_COLOR, 1, SDB_COLOR},
	(T){"pos:", &sda_setup_pos, &sda_export_pos, SDA_POS, 3, SDB_POS},
	(T){"rot:", &sda_setup_rot, &sda_export_rot, SDA_ROT, 3, SDB_ROT},
	(T){"size:", &sda_setup_size, sda_export_size, SDA_SIZE, 1, SDB_SIZE},
	(T){"al:", &sda_setup_al, &sda_export_al, SDA_AL, 1, SDB_AL},
	(T){"fov:", &sda_setup_fov, NULL, SDA_FOV, 1, SDB_FOV},
	(T){"intensity:", &sda_setup_intensity, &sda_export_intensity,
		SDA_INTEN, 1, SDB_INTEN},
	(T){"refract:", &sda_setup_refract, &sda_export_refract, SDA_REFRACT, 1,
		SDB_REFRACT},
	(T){"include:", &sda_setup_include, NULL, SDA_INCLUDE, 1, SDB_INCLUDE},
	(T){"angle:", &sda_setup_angle, &sda_export_angle, SDA_ANGLE, 1, SDB_ANGLE},
	(T){"copy:", &sda_setup_copy, NULL, SDA_COPY, 1, SDB_COPY},
	(T){"name:", &sda_setup_name, &sda_export_name, SDA_NAME, 1, SDB_NAME},
	(T){"texture:", &sda_setup_texture, &sda_export_texture, SDA_TEXTURE, 1,
		SDB_TEXTURE},
	(T){"reflect:", &sda_setup_reflect, &sda_export_reflect, SDA_REFLECT, 1,
		SDB_REFLECT},
	(T){"background:", &sda_setup_background, &sda_export_background,
		SDA_BACKGROUND, 1, SDB_BACKGROUND},
	(T){"normal:", &sda_setup_normal, &sda_export_normal, SDA_TEXTURE, 1,
		SDB_NORMAL},
	(T){"skybox:", &sda_setup_skybox, &sda_export_skybox, SDA_SKYBOX, 1,
		SDB_SKYBOX},
	(T){"sdisable:", &sda_setup_sdisable, &sda_export_sdisable, SDA_SDISABLE, 1,
		SDB_SDISABLE},
	(T){"heightmap:", &sda_setup_heightmap, NULL, SDA_HEIGHTMAP, 1,
		SDB_HEIGHTMAP},
	(T){"texture-perlin:", &sda_setup_texture_perlin, NULL, SDA_TEX_PERLIN, 2,
		SDB_TEX_PERLIN},
	(T){"vertex0:", &sda_setup_vertex_0, &sda_export_vertex0, SDA_VERTEX, 3,
		SDB_VERTEX0},
	(T){"vertex1:", &sda_setup_vertex_1, &sda_export_vertex1, SDA_VERTEX, 3,
		SDB_VERTEX1},
	(T){"vertex2:", &sda_setup_vertex_2, &sda_export_vertex2, SDA_VERTEX, 3,
		SDB_VERTEX2},
	(T){"obj:", &sda_setup_obj, &sda_export_obj, SDA_OBJ, 1, SDB_OBJ},
	(T){"csg:", &sda_setup_csg, NULL, SDA_CSG, 1, SDB_CSG},
	(T){"senable:", &sda_setup_senable, &sda_export_senable, SDA_SENABLE, 1,
		SDB_SENABLE}
};

static const t_sda_default	g_sda_default[SDA_COUNT_DEFAULTS] = {
	(t_sda_default){CAMERA, &sda_default_camera},
	(t_sda_default){LIGHTTYPE, &sda_default_lights},
	(t_sda_default){CONE, &sda_default_cone},
	(t_sda_default){TRIANGLE, &sda_default_triangle},
	(t_sda_default){SETTING, &sda_default_setting},
	(t_sda_default){SDA_SDISABLE, &sda_default_shaders},
	(t_sda_default){SDA_TEXTURE, &sda_default_texture},
	(t_sda_default){SDA_SIZE, &sda_default_size}
};

#endif
