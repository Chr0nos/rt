/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:33:44 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 15:25:21 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_rot(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	rt_obj_rotate(obj,
		(t_v4d){deg2rad(ft_atod(av[0])),
		deg2rad(ft_atod(av[1])),
		deg2rad(ft_atod(av[2])),
		1.0});
	return (1);
}
