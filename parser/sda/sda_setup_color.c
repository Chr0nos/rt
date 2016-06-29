/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:15:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 17:16:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_color(t_rt *rt, t_obj *obj, char **av)
{
	(void)rt;
	if (av[0][0] != '#')
		return (0);
	ft_strtoupper(av[0]);
	((t_cube*)obj->content)->color =
		(unsigned int)ft_basetoul((const char*)&av[0][1], "0123456789ABCDEF");
	return (1);
}
