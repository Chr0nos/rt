/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 11:50:16 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 15:02:18 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

static int	sda_setup_copy_check(t_obj *node, const t_obj *obj)
{
	while (node)
	{
		if (obj == node)
			return (0);
		node = node->parent;
	}
	return (1);
}

int		sda_setup_copy(t_sda *e, t_obj *obj, char **av)
{
	t_obj				*src;
	const unsigned int	id = (unsigned int)ft_atoi(av[0]);

	if (!id)
	{
		ft_putendl_fd("error: refusing to copy id 0: this is root you idiot !",
			2);
		return (-1);
	}
	src = rt_obj_byid(e->root, id);
	if (!src)
	{
		ft_putendl_fd("error: invalid id", 2);
		return (-2);
	}
	if (!sda_setup_copy_check(obj, src))
	{
		ft_putendl_fd("error: infinite copy", 2);
		return (-3);
	}
	rt_obj_copy_node(src, obj);
	return (1);
}
