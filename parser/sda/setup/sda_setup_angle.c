/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 18:46:15 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:55:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

int		sda_setup_angle(t_sda *e, t_obj *obj, char **av)
{
	t_v4d			bsize;
	const double	angle = deg2rad(ft_atod(av[0]));

	(void)e;
	bsize = (t_v4d){
		angle,
		cos(angle / 2.0),
		sin(angle / 2.0),
		0.0
	};
	bsize.w = bsize.y / bsize.z;
	((t_cone*)obj->content)->angle = bsize;
	return (1);
}
