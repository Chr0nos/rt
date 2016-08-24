/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 18:17:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:18:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"

void	sda_default_size(t_rt *rt, t_obj *obj)
{
	(void)rt;
	if (!(obj->cfgbits & SDB_SIZE))
		((t_cube*)obj->content)->size = 1.0;
}
