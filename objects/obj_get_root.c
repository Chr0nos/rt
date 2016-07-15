/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_get_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 23:57:38 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 23:58:21 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_obj	*rt_obj_get_root(t_obj *obj)
{
	while (obj->parent)
		obj = obj->parent;
	return (obj);
}
