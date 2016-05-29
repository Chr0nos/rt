/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:31:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/29 04:39:59 by snicolet         ###   ########.fr       */
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
	const t_box				*b = &obj->bounds;
	char					*min;
	char					*max;
	unsigned int			p;

	rt_node_display(obj, userdata);
	p = 3;
	ft_putstr("\n\t");
	while (p--)
	{
		min = ft_dtoa((double)b->xmin, 4);
		max = ft_dtoa((double)b->xmax, 4);
		ft_printf(" [%s:%s]", min, max);
		ft_mfree(2, min, max);
		b = (t_box*)(unsigned long)b + (sizeof(float) * 2);
	}
	ft_putchar('\n');
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
