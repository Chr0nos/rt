/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:31:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/29 04:55:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

void	rt_node_display(t_obj *obj, void *userdata)
{
	(void)userdata;
	rt_puttype(obj->type);
	ft_printf("[%d] ", (int)obj->id);
}

void	rt_node_display_bounds(t_obj *obj, void *userdata)
{
	char				*x[6];
	const unsigned int	p = 4;

	rt_node_display(obj, userdata);
	x[0] = ft_dtoa((double)obj->bounds.xmin, p);
	x[1] = ft_dtoa((double)obj->bounds.xmax, p);
	x[2] = ft_dtoa((double)obj->bounds.ymin, p);
	x[3] = ft_dtoa((double)obj->bounds.ymax, p);
	x[4] = ft_dtoa((double)obj->bounds.zmin, p);
	x[5] = ft_dtoa((double)obj->bounds.zmax, p);
	ft_printf("\n\t[%s:%s] [%s:%s] [%s:%s]\n", x[0], x[1], x[2], x[3],x[4],
		x[5]);
	ft_free_tab(x, 6);
}

void	rt_node_foreach(t_obj *node, int mode, void (*f)(t_obj*, void*),
	void *userdata)
{
	t_obj		*obj;

	if (!node)
		return ;
	if (mode & PREFIX)
		f(node, userdata);
	obj = node->childs;
	while (obj)
	{
		if (mode & INFIX)
			f(obj, userdata);
		rt_node_foreach(obj, mode, f, userdata);
		obj = obj->next;
	}
	if (mode & SUFFIX)
		f(node, userdata);
}
