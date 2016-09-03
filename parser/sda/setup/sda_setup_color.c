/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:06:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:55:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "rt.h"

int			sda_setup_color(t_sda *e, t_obj *obj, char **av)
{
	unsigned long	raw_color;
	unsigned int	color;

	if (av[0][0] != '#')
		return (0);
	ft_strtoupper(av[0]);
	raw_color = (unsigned int)ft_basetoul((const char*)&av[0][1],
		"0123456789ABCDEF");
	if (raw_color > 0xffffffff)
		color = 0xffffffff;
	else
		color = (unsigned int)raw_color;
	if (obj->type == SETTING)
	{
		e->rt->settings.default_color = color;
		((t_setting*)obj->content)->color = color;
	}
	else
		((t_cube*)obj->content)->color = color;
	return (1);
}
