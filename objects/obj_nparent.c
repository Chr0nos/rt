/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_nparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:02:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/17 14:02:59 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*rt_obj_nparent(t_obj *obj, unsigned int n)
{
	while ((n--) && (obj->parent))
		obj = obj->parent;
	return (obj);
}
