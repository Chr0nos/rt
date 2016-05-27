/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 20:51:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/27 21:48:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#define PROP_SIZE 0
#define CUBE_COLOR_POS 4
#define S_COLOR_POS 4

static unsigned int yolo_setup_color(const char *strcolor)
{
	char	**split;
	t_rgb	color;
	size_t	splitsize;

	if (ft_strcount(strcolor, ':') != 2)
		return (COLOR_BLACK);
	split = ft_strsplit(strcolor, ':');
	splitsize = ft_tabcount((void**)split);
	if (splitsize != 4)
		return (COLOR_BLACK);
	color.a = 0;
	color.r = ft_atoi(split[0]) & 255;
	color.g = ft_atoi(split[1]) & 255;
	color.b = ft_atoi(split[2]) & 255;
	ft_free_tab(split, splitsize);
	free(split);
	return (*(unsigned int *)(unsigned long)&color);
}

int		yolo_setup(t_obj *obj, size_t ac, char **av)
{
	if (!ac)
		return (1);
	if (obj->type == SPHERE)
	{
		((t_sphere*)obj->content)->radius = (float)ft_atod(av[PROP_SIZE]);
		((t_sphere*)obj->content)->color = yolo_setup_color(av[S_COLOR_POS]);
	}
	else if (obj->type == CUBE)
	{
		((t_cube*)obj->content)->size = (float)ft_atod(av[PROP_SIZE]);
		((t_cube*)obj->content)->color = yolo_setup_color(av[CUBE_COLOR_POS]);
	}
	return (0);
}
