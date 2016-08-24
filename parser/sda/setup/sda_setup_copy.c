/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 11:50:16 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 16:42:39 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"
#include <stdlib.h>

static int	sda_setup_copy_error(const char *err, int ret)
{
	ft_putendl_fd(err, 2);
	return (ret);
}

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

static int	sda_setup_copy_isname(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int			sda_setup_copy(t_sda *e, t_obj *obj, char **av)
{
	t_obj				*src;
	char				*name;
	unsigned int		id;

	if (!sda_setup_copy_isname(av[0]))
	{
		id = (unsigned int)ft_atoi(av[0]);
		if (!id)
			return (sda_setup_copy_error("error: refusing to copy id 0", -1));
		if (!(src = rt_obj_byid(e->root, id)))
			return (sda_setup_copy_error("error: invalid id", -2));
	}
	else
	{
		name = ft_strunsplit((const char **)(unsigned long)av, ' ');
		src = rt_obj_byname(e->root, (const char *)name);
		free(name);
		if (!src)
			return (sda_setup_copy_error("error: name not found", -4));
	}
	if (!sda_setup_copy_check(obj, src))
		return (sda_setup_copy_error("error: infinite copy", -3));
	rt_obj_copy_node(src, obj);
	return (1);
}
