/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_lights.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:24:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:58:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"

void	sda_default_lights(t_rt *rt, t_obj *obj)
{
	(void)rt;
	if (!(obj->cfgbits & SDB_COLOR))
		((t_cube*)obj->content)->color = 0xffffff;
	if (!(obj->cfgbits & SDB_INTEN))
		((t_plight*)obj->content)->intensity = 100.0;
	if (!(obj->cfgbits & SDB_SIZE))
		((t_plight*)obj->content)->radius = 100.0;
}
