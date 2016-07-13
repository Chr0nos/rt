/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_byname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 16:29:17 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 16:32:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "libft.h"

t_obj			*rt_obj_byname(t_obj *node, const char *name)
{
	t_obj	*obj;
	t_obj	*ret;

	if ((!node) || ((node->name) && (!ft_strcmp(node->name, name))))
		return (node);
	obj = node->childs;
	while (obj)
	{
		ret = rt_obj_byname(obj, name);
		if (ret)
			return (ret);
		obj = obj->next;
	}
	return (NULL);
}
