/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 15:15:21 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/16 13:59:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

t_obj	*rt_rtree_push(t_obj **iter, t_obj *obj, t_obj *parent, t_m4 *mat)
{
	t_obj		*ob;

	*iter = &((*iter)[1]);
	ob = rt_obj_init(*iter, obj->type);
	rt_obj_addchild(parent, ob)->trans = *mat;
	// draw_putv4d(ob->trans.w, 3);
	// ft_putchar('\n');
	ob->content = obj->content;
	ob->inters = obj->inters;
	ob->normal = obj->normal;
	ob->id = obj->id;
	ob->rotation = obj->rotation;
	ob->parent = parent;
	ob->hitbox = obj->hitbox;
	ob->bounds = obj->hitbox;
	rt_box_update(ob);
	return (ob);
}

int		rt_rtree_count(t_obj *node, int mode, void *userdata)
{
	t_rtree		*c;

	(void)mode;
	c = (t_rtree *)userdata;
	if (node->type & BOUNDED)
		c->bnum += 1;
	else if (node->type & NOCHECKBOX)
		c->ubnum += 1;
	else if (node->type & LIGHTTYPE)
		c->lnum += 1;
	return (0);
}

void	rt_rtree_fill(t_obj *node, t_rtree *rtree, t_obj *parent, t_m4 mat)
{
	t_obj		*obj;

	obj = parent;
	mat = draw_matrix_multiply_matrix_m4(mat, &node->trans);
	if (node->type & BOUNDED)
		obj = rt_rtree_push(&(rtree->m_biter), node, parent, &mat);
	else if (node->type & NOCHECKBOX)
		rt_rtree_push(&(rtree->m_ubiter), node, rtree->unbounded, &mat);
	else if (node->type & LIGHTTYPE)
		rt_rtree_push(&(rtree->m_liter), node, rtree->light, &mat);
	node = node->childs;
	while (node)
	{
		rt_rtree_fill(node, rtree, obj, mat);
		node = node->next;
	}
}

t_rtree	rt_render_tree(t_obj *node)
{
	t_obj		*tree;
	t_rtree		rtree;

	rtree.bnum = 0;
	rtree.lnum = 0;
	rtree.ubnum = 0;
	rt_node_foreach(node, INFIX, &rt_rtree_count, &rtree);
	rtree.memlen = (rtree.bnum + rtree.ubnum + rtree.lnum + 5) * sizeof(t_obj);
	if (!(tree = (t_obj *)malloc(rtree.memlen)))
	{
		rtree.memlen = 0;
		return (rtree);
	}
	rtree.bounded = rt_obj_init(tree, ROOT);
	rtree.unbounded = rt_obj_init(&tree[rtree.bnum + 1], ROOT);
	rtree.light = rt_obj_init(&tree[rtree.bnum + rtree.ubnum + 3], ROOT);
	rtree.m_biter = rtree.bounded;
	rtree.m_ubiter = &(rtree.unbounded[1]);
	rtree.m_liter = &(rtree.light[1]);
	rt_rtree_fill(node, &rtree, rtree.bounded, draw_make_matrix_m4_identity());
	rt_bounds_update(rtree.bounded);
	//rt_debug(rtree.bounded, 0);
	//ft_putendl("The End !");
	return (rtree);
}
