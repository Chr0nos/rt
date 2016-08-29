/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 19:38:02 by qloubier          #+#    #+#             */
/*   Updated: 2016/08/29 16:34:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H
# define NODE_TYPE struct s_node

typedef struct		s_node
{
	NODE_TYPE		*parent;
	NODE_TYPE		*childs;
	NODE_TYPE		*next;
	unsigned int	len;
	unsigned int	id;
}					t_node;

#endif
