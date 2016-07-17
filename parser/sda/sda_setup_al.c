/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_al.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:02:24 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 18:21:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "render.h"
#include <math.h>

int			sda_setup_al(t_sda *e, t_obj *obj, char **av)
{
	const double		al = ft_atod(av[0]);

	((t_setting*)obj->content)->al = al;
	e->rt->settings.ambiant_light = fmin(1.0, al / MID_LIGHT_POWER);
	return (1);
}
