/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:57:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 15:15:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDA_H
# define SDA_H
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
		SDB_COPY = 1 << 10
};

enum					e_sda_setting
{
		SDA_COLOR = VISIBLE | LIGHTTYPE,
		SDA_POS = ~0,
		SDA_ROT = ~(CONE),
		SDA_AL = SETTING | CAMERA,
		SDA_FOV = CAMERA,
		SDA_SIZE = (SPHERE | CUBE | CONE | CYL | LIGHTTYPE | CONE_INF),
		SDA_INTEN = LIGHTTYPE,
		SDA_REFRACT = VISIBLE,
		SDA_INCLUDE = EMPTY,
		SDA_ANGLE = CONE,
		SDA_COPY = EMPTY
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
void					sda_set_defaults(t_obj *root);
t_obj					*sda_parse_rawtree(const char *filepath, t_rt *rt,
	t_obj *root, int lvl_offset);

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

#endif
