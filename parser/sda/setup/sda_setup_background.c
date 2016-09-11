/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_background.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 21:00:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 16:34:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

int			sda_setup_background(t_sda *e, t_obj *obj, char **av)
{
	if (av[0][0] == '#')
	{
		e->rt->settings.bgcolor = (unsigned int)ft_basetoul(
			(const char*)ft_strtoupper(&av[0][1]), "0123456789ABCDEF");
		((t_setting*)obj->content)->bgcolor = e->rt->settings.bgcolor;
		return (1);
	}
	return (0);
}
