/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_cone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:38:10 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:58:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"

void	sda_default_cone(t_rt *rt, t_obj *obj)
{
	t_cone	*cone;

	(void)rt;
	cone = obj->content;
	if (!(obj->cfgbits & SDB_ANGLE))
	{
		cone->angle = (t_v4d){
			1.0,
			0.87758256189,
			0.4794255386,
			1.83048772173
		};
	}
}
