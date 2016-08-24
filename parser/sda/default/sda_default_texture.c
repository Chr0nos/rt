/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 18:13:27 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:15:18 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"

void	sda_default_texture(t_rt *rt, t_obj *obj)
{
	(void)rt;
	if (!(obj->cfgbits & SDB_TEXTURE))
		rt_obj_set_texture(obj, NULL);
}
