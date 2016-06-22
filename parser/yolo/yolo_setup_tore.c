/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_tore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 17:02:41 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/22 17:09:50 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_tore(t_obj *obj, size_t ac, char **av)
{
	if (ac < TORE_R2)
	{
		ft_putstr("error: failed to setup object type Tore\n");
		return (1);
	}
	ft_strtoupper(av[TORE_COLOR]);
	((t_tore*)obj->content)->radius = (float)ft_atod(av[TORE_R1]);
	((t_tore*)obj->content)->radius_2 = (float)ft_atod(av[TORE_R2]);
	((t_tore*)obj->content)->color = yolo_setup_color(av[TORE_COLOR]);
	return (0);
}
