/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 20:51:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/05 00:07:35 by snicolet         ###   ########.fr       */
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
#define MINFOV 5.0f
#define MAXFOV 180.0f

static unsigned int	yolo_setup_color(const char *strcolor)
{
	char			**split;
	unsigned int	color;
	size_t			splitsize;

	if (ft_strcount(strcolor, ':') != 2)
		return (COLOR_BLACK);
	if (!(split = ft_strsplit(strcolor, ':')))
		return (COLOR_BLACK);
	splitsize = ft_tabcount((void**)split);
	color = (splitsize == 4) ? (unsigned int)((((ft_atoi(split[0]) & 0xff) << \
		16) | (ft_atoi(split[1]) & 0xff) << 8) | (ft_atoi(split[2]) & 0xff)) : \
		COLOR_BLACK;
	ft_free_tab(split, splitsize);
	free(split);
	return (color);
}

static int			yolo_setup_camera(t_obj *obj, size_t ac, char **av)
{
	float	fov;

	if (ac < CAMERA_OR_Z)
	{
		ft_printf("error: failed to setup camera\n");
		return (1);
	}
	if ((ac <= 6) || ((fov = (float)ft_atod(av[6])) < MINFOV) || (fov > MAXFOV))
		fov = 49.124f;
	((t_camera*)obj->content)->fov = deg2radf(fov);
	obj->rotation = (t_v4d){deg2rad(ft_atod(av[CAMERA_OR_X])),
		deg2rad(ft_atod(av[CAMERA_OR_Y])),
		deg2rad(ft_atod(av[CAMERA_OR_Z])),
		1.0};
	obj->trans = draw_matrix_multiply_axes_m4(
		obj->rotation,
		(t_v4d){1.0, 1.0, 1.0, 1.0}, obj->trans.w);
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
