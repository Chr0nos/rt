/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:57:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/16 00:37:17 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDA_H
# define SDA_H
# define SDA_SETUP_TYPES 15
# include "objects.h"
# include "rt.h"
# include "forms.h"

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
	SDB_BACKGROUND = 1 << 14
};

enum					e_sda_setting
{
	SDA_COLOR = VISIBLE | LIGHTTYPE | SETTING,
	SDA_POS = ~0,
	SDA_ROT = ~(CONE),
	SDA_AL = SETTING | CAMERA,
	SDA_FOV = CAMERA,
	SDA_SIZE = (SPHERE | CUBE | CONE | CYL | LIGHTTYPE | CONE_INF),
	SDA_INTEN = LIGHTTYPE,
	SDA_REFRACT = VISIBLE,
	SDA_INCLUDE = EMPTY,
	SDA_ANGLE = CONE,
	SDA_COPY = EMPTY,
	SDA_NAME = ~0,
	SDA_TEXTURE = SPHERE | CUBE | PLAN,
	SDA_REFLECT = VISIBLE | SETTING,
	SDA_BACKGROUND = SETTING
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

typedef struct			s_sda_cfg
{
	const char			*str;
	int					(*config)(t_sda *, t_obj *, char **);
	char				*(*export)(t_obj *);
	enum e_sda_setting	obj_valid_type;
	int					argc;
	int					bit;
}						t_sda_cfg;

int						sda_lvl(char *line);
t_obj					*sda_parse(const char *filepath, t_rt *rt);
int						sda_eval(const char *line, t_sda *e,
	const int lvl);
int						sda_settings(t_sda *e, int ac, char **av);
void					sda_settings_init(t_sda_cfg *cfg);
void					sda_set_defaults(t_obj *root, t_rt *rt);
t_obj					*sda_parse_rawtree(const char *filepath, t_rt *rt,
	t_obj *root, int lvl_offset);

/*
** exporter
*/

char					*sda_export_ntab(unsigned int lvl);
void					sda_export(const t_rt *rt);
void					sda_export_color_raw(unsigned int color, char *color_str);
char					*sda_export_xyz(const t_v4d *v);
char					*sda_export_pos(t_obj *obj);
char					*sda_export_rot(t_obj *obj);
char					*sda_export_color(t_obj *obj);
char					*sda_export_size(t_obj *obj);
char					*sda_export_texture(t_obj *obj);
char					*sda_export_refract(t_obj *obj);
char					*sda_export_intensity(t_obj *obj);

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
int						sda_setup_reflect(t_sda *e, t_obj *obj, char **av);
int						sda_setup_background(t_sda *e, t_obj *obj, char **av);

#endif
