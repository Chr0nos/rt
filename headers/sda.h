/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 12:57:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 20:35:13 by snicolet         ###   ########.fr       */
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
		SDB_INTEN = 1 << 6
};

enum					e_sda_setting
{
		SDA_COLOR = VISIBLE | LIGHTTYPE,
		SDA_POS = ~0,
		SDA_ROT = ~0,
		SDA_AL = SETTING | CAMERA,
		SDA_FOV = CAMERA,
		SDA_SIZE = (SPHERE | CUBE | CONE | CYL | LIGHTTYPE),
		SDA_INTEN = LIGHTTYPE
};

typedef struct			s_sda_cfg
{
	const char			*str;
	int					(*config)(t_rt *, t_obj *, char **);
	enum e_sda_setting	obj_valid_type;
	int					argc;
	int					bit;
}						t_sda_cfg;

int						sda_lvl(char *line);
t_obj					*sda_parse(const char *filepath, t_rt *rt);
int						sda_eval(const char *line, t_rt *rt, t_obj *root,
	const int lvl);
int						sda_settings(t_obj *obj, t_rt *rt, int ac, char **av);

/*
** configure functions
*/

int			sda_setup_color(t_rt *rt, t_obj *obj, char **av);
int			sda_setup_pos(t_rt *rt, t_obj *obj, char **av);
int			sda_setup_al(t_rt *rt, t_obj *obj, char **av);
int			sda_setup_rot(t_rt *rt, t_obj *obj, char **av);
int			sda_setup_fov(t_rt *rt, t_obj *obj, char **av);
int			sda_setup_size(t_rt *rt, t_obj *obj, char **av);
int			sda_setup_intensity(t_rt *rt, t_obj *obj, char **av);

#endif
