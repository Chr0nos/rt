/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_cube.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:16:32 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:49:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_cube(t_obj *obj, size_t ac, char **av)
{
	if (ac < 4)
		return (1);
	ft_strtoupper(av[S_COLOR_POS]);
	((t_sphere*)obj->content)->radius = (float)ft_atod(av[PROP_SIZE]);
	((t_sphere*)obj->content)->color = yolo_setup_color(av[S_COLOR_POS]);
	obj->cfgbits |= SDB_COLOR | SDB_SIZE;
	return (0);
}
