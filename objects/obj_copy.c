/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 11:58:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 19:18:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"
#include "shaders.h"
#include "libft.h"
#include "sda.h"

/*
** this function does a copy of an object BUT dont care about childs/brothers
** id's are differents from the source
** childs is set to NULL
** shaders are malloced too to prevent special cases in memory liberation
*/

t_obj		*rt_obj_copy(const t_obj *src, t_obj *parent)
{
	t_obj		*obj;

	if (!(obj = ft_memdup(src, rt_sizeobj(src->type))))
		return (NULL);
	rt_obj_addchild(parent, obj);
	obj->parent = parent;
	obj->childs = NULL;
	obj->content = (void*)((unsigned long)obj + sizeof(t_obj));
	obj->next = NULL;
	obj->name = NULL;
	obj->cfgbits = src->cfgbits & ~SDB_NAME;
	rt_obj_init_shader(obj);
	obj->id = rt_factory_getuid();
	return (obj);
}

/*
** this function copy a node and his childs
*/

t_obj		*rt_obj_copy_node(t_obj *node, t_obj *parent)
{
	t_obj	*node_copy;
	t_obj	*copy;
	t_obj	*obj;

	copy = rt_obj_copy(node, parent);
	node_copy = copy;
	obj = node->childs;
	while (obj)
	{
		copy = rt_obj_copy_node(obj, node_copy);
		obj = obj->next;
	}
	return (node_copy);
}
