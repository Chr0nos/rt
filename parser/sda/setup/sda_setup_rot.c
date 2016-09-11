/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:33:44 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/10 05:55:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

int			sda_setup_rot_x(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	rt_obj_rotate_force(obj, (t_v4d){deg2rad(ft_atod(av[0])), obj->rotation.y,
		obj->rotation.z, 1.0});
	return (1);
}

int			sda_setup_rot_y(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	rt_obj_rotate_force(obj, (t_v4d){obj->rotation.x, deg2rad(ft_atod(av[0])),
		obj->rotation.z, 1.0});
	return (1);
}

int			sda_setup_rot_z(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	rt_obj_rotate_force(obj, (t_v4d){obj->rotation.x, obj->rotation.y,
		deg2rad(ft_atod(av[0])), 1.0});
	return (1);
}

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
