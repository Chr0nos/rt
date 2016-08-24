/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_setting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:33:27 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:07:23 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"

void	sda_default_setting(t_rt *rt, t_obj *obj)
{
	t_setting	*set;

	(void)rt;
	set = obj->content;
	if (!set)
		return ;
	if (!(obj->cfgbits & SDB_COLOR))
		set->color = 0x00000000;
}
