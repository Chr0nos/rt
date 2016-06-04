/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:31:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/04 19:16:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

void	rt_node_display(t_obj *obj, int mode, void *userdata)
{
	(void)userdata;
	(void)mode;
	rt_puttype(obj->type);
	ft_printf("[%d] ", (int)obj->id);
}

void	rt_node_foreach(t_obj *node, int mode, void (*f)(t_obj*, int, void*),
	void *userdata)
{
	t_obj		*obj;

	if (!node)
		return ;
	if (mode & PREFIX)
		f(node, PREFIX, userdata);
	obj = node->childs;
	while (obj)
	{
		if (mode & INFIX)
			f(obj, INFIX, userdata);
		rt_node_foreach(obj, mode, f, userdata);
		obj = obj->next;
	}
	if (mode & SUFFIX)
		f(node, SUFFIX, userdata);
}
