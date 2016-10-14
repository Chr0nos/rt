/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:57:31 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/15 17:32:59 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "rt.h"

int			sda_setup_size(t_sda *e, t_obj *obj, char **av)
{
	float		size;

	size = (float)ft_atod(av[0]);
	if (size < 0.0f)
		size = 0.0f;
	if (obj->type == SETTING)
	{
		((t_setting*)obj->content)->size = size;
		e->rt->settings.default_size = size;
	}
	else
		((t_cube*)obj->content)->size = size;
	return (1);
}
