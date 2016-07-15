/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:06:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 11:37:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_color(t_sda *e, t_obj *obj, char **av)
{
	unsigned int	color;

	if (av[0][0] != '#')
		return (0);
	ft_strtoupper(av[0]);
	color = (unsigned int)ft_basetoul((const char*)&av[0][1], "0123456789ABCDEF");
	if (obj->type == SETTING)
		e->rt->settings.default_color = color;
	else
		((t_cube*)obj->content)->color = color;
	return (1);
}
