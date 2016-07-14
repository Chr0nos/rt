/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_reflect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 16:58:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 22:22:29 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_reflect(t_sda *e, t_obj *obj, char **av)
{
	int		r;

	(void)e;
	r = ft_atoi(av[0]);
	if (r > 0xff)
		r = 0xff;
	else if (r < 0)
		r = 0;
	if (obj->type == SETTING)
	{
		e->rt->settings.default_reflect = (unsigned char)r;
		return (1);
	}
	return (rt_obj_set_reflect(obj, (unsigned char)r));
}
