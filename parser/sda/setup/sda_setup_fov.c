/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_fov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:45:59 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:55:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"
#define MINFOV 5.0
#define MAXFOV 180.0

int			sda_setup_fov(t_sda *e, t_obj *obj, char **av)
{
	double	fov;

	(void)e;
	fov = ft_atod(av[0]);
	if ((fov == 0.0) || (fov < MINFOV) || (fov > MAXFOV))
		fov = 49.124;
	((t_camera*)obj->content)->fov = deg2rad(fov);
	return (1);
}
