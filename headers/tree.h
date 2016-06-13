/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 15:18:31 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/13 17:02:07 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H
# include "forms.h"

typedef struct		s_rendertree
{
	unsigned int	bnum;
	unsigned int	ubnum;
	unsigned int	lnum;
	unsigned int	memlen;
	t_obj			*bounded;
	t_obj			*unbounded;
	t_obj			*light;
	t_obj			*m_biter;
	t_obj			*m_ubiter;
	t_obj			*m_liter;
}					t_rtree;

int					rt_rtree_count(t_obj *node, int mode, void *userdata);
t_obj				*rt_rtree_push(t_obj **iter, t_obj *obj, t_obj *parent,
						t_m4 *mat);
void				rt_rtree_fill(t_obj *node, t_rtree *rtree, t_obj *parent,
						t_m4 mat);
t_rtree				rt_render_tree(t_obj *node);

#endif
