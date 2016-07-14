/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_reflect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 16:58:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 17:18:36 by snicolet         ###   ########.fr       */
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
	return (rt_obj_set_reflect(obj, (unsigned char)r));
}
