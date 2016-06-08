/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:31:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 01:09:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

int		rt_node_display(t_obj *obj, int mode, void *userdata)
{
	(void)userdata;
	(void)mode;
	rt_puttype(obj->type);
	ft_printf("[%d] ", (int)obj->id);
	return (0);
}

/*
** purpose: get the amount of objects in a tree
** usage:
** unsigned int count;
** count = 0;
** rt_node_foreach(root, PREFIX, &count);
*/

int		rt_node_count(t_obj *node, int mode, void *userdata)
{
	(void)node;
	(void)mode;
	*(unsigned int *)userdata += 1;
	return (0);
}

int		rt_node_foreach(t_obj *node, int mode, int (*f)(t_obj*, int, void*),
	void *userdata)
{
	t_obj		*obj;
	int			ret;

	if (!node)
		return (0);
	ret = OK;
	if ((mode & PREFIX) &&
		((ret = f(node, PREFIX, userdata)) & (STOP_ALL | STOP_NODE)))
		return (ret);
	obj = node->childs;
	while (obj)
	{
		if ((mode & INFIX) && ((ret = f(obj, INFIX, userdata)) == STOP_ALL))
			return (1);
		if ((ret != STOP_NODE) &&
			(rt_node_foreach(obj, mode, f, userdata) == STOP_ALL))
			return (STOP_ALL);
		obj = obj->next;
	}
	if (mode & SUFFIX)
		return (f(node, SUFFIX, userdata));
	return (0);
}
