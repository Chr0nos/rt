/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:57:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/26 15:03:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDA_H
# define SDA_H
# define SDA_SETUP_TYPES 25
# define SDA_COUNT_SHADER 6
# define SDA_COUNT_DEFAULTS 8
# define FLOATCMP(x, y) ((x > y) || (x < y))
# include "objects.h"
# include "rt.h"
# include "forms.h"
# include "shaders.h"
# include "mesh.h"

enum					e_sda_cfgbit
{
	SDB_COLOR = 1,
	SDB_POS = 1 << 1,
	SDB_ROT = 1 << 2,
	SDB_FOV = 1 << 3,
	SDB_SIZE = 1 << 4,
	SDB_AL = 1 << 5,
	SDB_INTEN = 1 << 6,
	SDB_REFRACT = 1 << 7,
	SDB_INCLUDE = 1 << 8,
	SDB_ANGLE = 1 << 9,
	SDB_COPY = 1 << 10,
	SDB_NAME = 1 << 11,
	SDB_TEXTURE = 1 << 12,
	SDB_REFLECT = 1 << 13,
	SDB_BACKGROUND = 1 << 14,
	SDB_NORMAL = 1 << 15,
	SDB_SKYBOX = 1 << 16,
	SDB_SDISABLE = 1 << 17,
	SDB_HEIGHTMAP = 1 << 18,
	SDB_TEX_PERLIN = 1 << 19 | SDB_TEXTURE,
	SDB_VERTEX0 = 1 << 20,
	SDB_VERTEX1 = 1 << 21,
	SDB_VERTEX2 = 1 << 22,
	SDB_VERTEX0_UV = 1 << 23,
	SDB_VERTEX1_UV = 1 << 24,
	SDB_VERTEX2_UV = 1 << 25,
	SDB_OBJ = 1 << 26,
	SDB_NOEXPORT = 1 << 27,
	SDB_LIMIT = 1 << 28,
	SDB_CSG = 1 << 29
};

enum					e_sda_setting
{
	SDA_COLOR = VISIBLE | LIGHTTYPE | SETTING,
	SDA_POS = ~0,
	SDA_ROT = ~(CONE),
	SDA_AL = SETTING | CAMERA,
	SDA_FOV = CAMERA,
	SDA_SIZE = (SPHERE | CUBE | CONE | CYL | LIGHTTYPE | CONE_INF | SETTING),
	SDA_INTEN = LIGHTTYPE,
	SDA_REFRACT = VISIBLE,
	SDA_INCLUDE = EMPTY,
	SDA_ANGLE = CONE,
	SDA_COPY = EMPTY,
	SDA_NAME = ~0,
	SDA_TEXTURE = SPHERE | CUBE | PLAN | CONE | TRIANGLE | MESH,
	SDA_REFLECT = VISIBLE | SETTING,
	SDA_BACKGROUND = SETTING,
	SDA_SKYBOX = SETTING,
	SDA_SDISABLE = VISIBLE,
	SDA_HEIGHTMAP = PLAN,
	SDA_TEX_PERLIN = SDA_TEXTURE,
	SDA_VERTEX = TRIANGLE,
	SDA_OBJ = MESH,
	SDA_CSG = VISIBLE
};

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
	struct s_sda_cfg	*cfg;
	t_setting			*setting;
	t_obj				*setting_obj;
	char				*tbl;
	const int			fd;
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
	int					bit;
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
}						t_sda_obj;

typedef struct			s_sda_default
{
	unsigned int		type_mask;
	void				(*exec)(t_rt *, t_obj *);
}						t_sda_default;

typedef struct			s_sda_default_config
{
	t_sda_default		def[SDA_COUNT_DEFAULTS];
	t_rt				*rt;
}						t_sda_default_config;

int						sda_lvl(char *line);
t_obj					*sda_parse(const char *filepath, t_rt *rt);
int						sda_eval(const char *line, t_sda *e,
	const int lvl);
int						sda_settings(t_sda *e, int ac, char **av);
void					sda_settings_stack(t_obj *stack, t_obj *s);
void					sda_settings_init(t_sda_cfg *cfg);
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

/*
** configure functions
*/

int						sda_setup_color(t_sda *e, t_obj *obj, char **av);
int						sda_setup_pos(t_sda *e, t_obj *obj, char **av);
int						sda_setup_al(t_sda *e, t_obj *obj, char **av);
int						sda_setup_rot(t_sda *e, t_obj *obj, char **av);
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

/*
** sda default functions
*/

void					sda_default_lights(t_rt *rt, t_obj *obj);
void					sda_default_camera(t_rt *rt, t_obj *obj);
void					sda_default_setting(t_rt *rt, t_obj *obj);
void					sda_default_triangle(t_rt *rt, t_obj *obj);
void					sda_default_cone(t_rt *rt, t_obj *obj);
void					sda_default_shaders(t_rt *rt, t_obj *obj);
void					sda_default_texture(t_rt *rt, t_obj *obj);
void					sda_default_size(t_rt *rt, t_obj *obj);

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

#endif
