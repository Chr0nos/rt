/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_background.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 21:00:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:56:14 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

int			sda_setup_background(t_sda *e, t_obj *obj, char **av)
{
	(void)obj;
	if (av[0][0] == '#')
	{
		e->rt->settings.bgcolor = (unsigned int)ft_basetoul(
			(const char*)ft_strtoupper(&av[0][1]), "0123456789ABCDEF");
		return (1);
	}
	return (0);
}
