/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 20:51:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/28 03:26:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <math.h>
#define PROP_SIZE 0
#define S_COLOR_POS 4
#define CAMERA_OR_X 3
#define CAMERA_OR_Y 4
#define CAMERA_OR_Z 5

static unsigned int	yolo_setup_color(const char *strcolor)
{
	char			**split;
	unsigned int	color;
	size_t			splitsize;

	if (ft_strcount(strcolor, ':') != 2)
		return (COLOR_BLACK);
	split = ft_strsplit(strcolor, ':');
	splitsize = ft_tabcount((void**)split);
	if (splitsize != 4)
		return (COLOR_BLACK);
	color = (unsigned int)((((ft_atoi(split[0]) & 0xff) << 16) |
			(ft_atoi(split[1]) & 0xff) << 8) | (ft_atoi(split[2]) & 0xff));
	ft_free_tab(split, splitsize);
	free(split);
	return (color);
}

static int			yolo_setup_camera(t_obj *obj, size_t ac, char **av)
{
	t_mattf		m;
	t_mattf		mtmp;
	t_v3f		tmp;
	t_v3f		scale;
	t_v3f		offset;

	if (ac < CAMERA_OR_Z)
	{
		ft_printf("error: failed to setup camera\n");
		return (1);
	}
	tmp.x = (float)(ft_atod(av[CAMERA_OR_X]) / 180.0 * M_PI_2);
	tmp.y = (float)(ft_atod(av[CAMERA_OR_Y]) / 180.0 * M_PI_2);
	tmp.z = (float)(ft_atod(av[CAMERA_OR_Z]) / 180.0 * M_PI_2);
	scale = (t_v3f){1.0, 1.0, 1.0};
	offset = (t_v3f){0.0, 0.0, 0.0};
	m = draw_make_matrix_x(offset, tmp.x, scale);
	mtmp = draw_make_matrix_y(offset, tmp.y, scale);
	m = draw_matrix_multiply_matrix(m, &mtmp);
	mtmp = draw_make_matrix_z(offset, tmp.z, scale);
	m = draw_matrix_multiply_matrix(m, &mtmp);
	m.offset = obj->trans.offset;
	obj->trans = m;
	return (0);
}

int					yolo_setup(t_obj *obj, size_t ac, char **av)
{
	if (!ac)
		return (1);
	if (obj->type & (SPHERE | CUBE))
	{
		if (ac < 4)
			return (1);
		((t_sphere*)obj->content)->radius = (float)ft_atod(av[PROP_SIZE]);
		((t_sphere*)obj->content)->color = yolo_setup_color(av[S_COLOR_POS]);
	}
	else if (obj->type == CAMERA)
		return (yolo_setup_camera(obj, ac, av));
	return (0);
}
