/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_byid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:05:59 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/17 14:17:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj	*rt_obj_byid(t_obj *node, const unsigned int id)
{
	t_obj	*obj;
	t_obj	*ret;

	if ((!node) || (node->id == id))
		return (node);
	obj = node->childs;
	while (obj)
	{
 		ret = rt_obj_byid(obj, id);
		if (ret)
			return (ret);
		obj = obj->next;
	}
	return (NULL);
}
