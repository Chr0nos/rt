/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 10:57:42 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/29 12:17:53 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int		yolo_setup_texture(t_obj *obj, char **av, int index)
{
	if (av[index] && av[index + 1] && av[index +2])
	{
		((t_text *)obj->content)->type = ft_atoi(av[index]);
		ft_strtoupper(av[index + 1]);
		((t_text *)obj->content)->color1 = yolo_setup_color(av[index + 1]);
		ft_strtoupper(av[index + 2]);
		((t_text *)obj->content)->color2 = yolo_setup_color(av[index + 2]);
	}
	return (0);
}
