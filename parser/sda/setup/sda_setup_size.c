/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:57:31 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 10:45:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "rt.h"

int			sda_setup_size(t_sda *e, t_obj *obj, char **av)
{
	const float		size = (float)ft_atod(av[0]);

	if (obj->type == SETTING)
	{
		((t_setting*)obj->content)->size = size;
		e->rt->settings.default_size = size;
	}
	else
		((t_cube*)obj->content)->size = size;
	return (1);
}
