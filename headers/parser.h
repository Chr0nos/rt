/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:55:23 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/16 12:42:52 by snicolet         ###   ########.fr       */
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
# define CYL_COLOR_POS 4
# define CYL_OR_X 5
# define CYL_OR_Y 6
# define CYL_OR_Z 7
# define CYL_HEIGHT 8
# define CYL_TEXTURE 9
# define MINFOV 5.0
# define MAXFOV 180.0
# include "rt.h"

typedef struct		s_parser_cfg
{
	unsigned int	type;
	int				(*config)(t_obj *, size_t, char **);
}					t_parser_cfg;

typedef struct		s_parser_internal
{
	unsigned int	type;
	int				(*inters)(struct s_obj *, t_ray *, t_v4d *);
	t_v4d			(*normal)(struct s_obj *, t_v4d *);
}					t_parser_internal;

t_obj				*yolo_parse(const char *filepath);
int					yolo_setup(t_obj *obj, size_t ac, char **av);
int					yolo_setup_cube(t_obj *obj, size_t ac, char **av);
int					yolo_setup_plan(t_obj *obj, size_t ac, char **av);
int					yolo_setup_cone(t_obj *obj, size_t ac, char **av);
int					yolo_setup_cyl(t_obj *obj, size_t ac, char **av);
int					yolo_setup_camera(t_obj *obj, size_t ac, char **av);
unsigned int		yolo_setup_color(const char *strcolor);

#endif
