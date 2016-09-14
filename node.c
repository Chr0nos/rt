/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:31:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 17:13:59 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "shaders.h"
#include "mesh.h"

int			rt_node_display(t_obj *obj, int mode, void *userdata)
{
	(void)userdata;
	(void)mode;
	rt_puttype(obj->type, 1);
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

int			rt_node_count(t_obj *node, int mode, void *userdata)
{
	(void)node;
	(void)mode;
	*(unsigned int *)userdata += 1;
	return (0);
}

int			rt_node_foreach(t_obj *node, int mode, int (*f)(t_obj*, int, void*),
	void *userdata)
{
	t_obj		*obj;
	int			ret;

	if (!node)
		return (0);
	if (!(mode & PREFIX))
		ret = OK;
	else if (((ret = f(node, PREFIX, userdata)) & (STOP_ALL | STOP_NODE)))
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

static void	rt_node_free_shaders(t_shaders *shaders)
{
	t_shader	*s;
	t_shader	*next;

	s = shaders->shader;
	while (s)
	{
		next = s->next;
		free(s);
		s = next;
	}
	free(shaders);
}

void		rt_node_free(t_obj *node)
{
	t_obj	*obj;
	t_obj	*tmp;

	if (!node)
		return ;
	obj = node->childs;
	while (obj)
	{
		tmp = obj->next;
		rt_node_free(obj);
		obj = tmp;
	}
	if (node->parent)
		rt_obj_delchild(node->parent, node);
	if (node->shader)
		rt_node_free_shaders(node->shader);
	if (node->name)
		ft_memdel((void**)&node->name);
	if (node->type & MESH)
		ft_strdel(&((t_mesh*)(node->content))->filepath);
	free(node);
}
