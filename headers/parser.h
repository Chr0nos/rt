/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:55:23 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/30 16:42:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define PROP_SIZE 0
# define S_COLOR_POS 4
# define CAMERA_OR_X 3
# define CAMERA_OR_Y 4
# define CAMERA_OR_Z 5
# define PLAN_OR_X 3
# define PLAN_OR_Y 4
# define PLAN_OR_Z 5
# define PLAN_COLOR 6
# define PLAN_TEXTURE 7
# define CONE_COLOR 4
# define CONE_ANGLE 5
# define CYL_COLOR_POS 4
# define CYL_OR_X 5
# define CYL_OR_Y 6
# define CYL_OR_Z 7
# define CYL_TEXTURE 8
# define PLIGHT_POWER 3
# define PLIGHT_RADIUS 4
# define PLIGHT_COLOR 5
# define MINFOV 5.0
# define MAXFOV 180.0
# include "rt.h"
# include "sda.h"

typedef struct		s_parser_cfg
{
	unsigned int	type;
	int				(*config)(t_obj *, size_t, char **);
}					t_parser_cfg;

typedef struct		s_parset_cfg
{
	const char		*name;
	int				(*config)(char **, size_t, t_rtcfg *);
}					t_parset_cfg;

typedef struct		s_parser_internal
{
	unsigned int	type;
	int				(*inters)(struct s_obj *, t_ray *, t_intersect *);
	t_v4d			(*normal)(struct s_obj *, t_v4d *);
}					t_parser_internal;

t_obj				*yolo_parse(const char *filepath, t_rtcfg *rset);
t_obj				*yolo_parse_finalize(t_obj *root);
int					yolo_parse_settings(char *line, t_rtcfg *rset);
int					yolo_setup(t_obj *obj, size_t ac, char **av);
int					yolo_setup_cube(t_obj *obj, size_t ac, char **av);
int					yolo_setup_plan(t_obj *obj, size_t ac, char **av);
int					yolo_setup_cone(t_obj *obj, size_t ac, char **av);
int					yolo_setup_cone_inf(t_obj *obj, size_t ac, char **av);
int					yolo_setup_cyl(t_obj *obj, size_t ac, char **av);
int					yolo_setup_camera(t_obj *obj, size_t ac, char **av);
unsigned int		yolo_setup_color(const char *strcolor);
int					yolo_setup_plight(t_obj *obj, size_t ac, char **av);
int					yolo_setup_texture(t_obj *obj, char **av, int index);
int					yolo_setting_ambiant(char **parms, size_t size,
						t_rtcfg *rset);
void				yolo_camera_save(t_obj *camera);
t_obj				*rt_parser(const char *filepath, t_rt *rt);

#endif
