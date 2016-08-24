/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_al.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:02:24 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/15 16:04:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "render.h"
#include <math.h>

int			sda_setup_al(t_sda *e, t_obj *obj, char **av)
{
	const double		al = ft_atod(av[0]);
	unsigned char		c;

	c = (unsigned char)((float)0xff * geo_clamp((float)al, 0.0f, 1.0f));
	e->rt->settings.ambiant_light = (unsigned int)(c | (c << 8) | (c << 16));
	e->rt->settings.ambiant_light |= 0xff000000;
	((t_setting*)obj->content)->al = al;
	return (1);
}
