/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_lvl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 15:33:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 15:34:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

unsigned int	rt_obj_get_lvl(t_obj *obj)
{
	unsigned int	lvl;

	lvl = 0;
	while (obj->parent)
	{
		lvl++;
		obj = obj->parent;
	}
	return (lvl);
}
