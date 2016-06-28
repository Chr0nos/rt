/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 15:18:31 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/28 18:55:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H
# include "forms.h"
# include "objects.h"

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

t_rtree				rt_render_tree(t_obj *node);

#endif
