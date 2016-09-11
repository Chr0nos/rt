/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 03:53:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 03:54:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"

int		sda_setup_alpha(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (!(obj->type & SDA_COLOR))
		return (0);
	((t_cube*)obj->content)->color = (sda_setup_color_text(av[0], 0x00ffffff,
		((t_cube*)obj->content)->color, 24));
	return (1);
}
