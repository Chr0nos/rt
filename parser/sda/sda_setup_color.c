/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:06:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 15:24:39 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_color(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (av[0][0] != '#')
		return (0);
	ft_strtoupper(av[0]);
	((t_cube*)obj->content)->color =
		(unsigned int)ft_basetoul((const char*)&av[0][1], "0123456789ABCDEF");
	return (1);
}
