/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_cyl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 11:19:24 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/13 11:19:51 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_cyl(t_obj *obj, size_t ac, char **av)
{
	if (ac < 4)
		return (1);
	ft_strtoupper(av[S_COLOR_POS]);
	((t_cyl*)obj->content)->radius = (float)ft_atod(av[PROP_SIZE]);
	((t_cyl*)obj->content)->color = yolo_setup_color(av[S_COLOR_POS]);
	return (0);
}
