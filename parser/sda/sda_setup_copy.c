/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 11:50:16 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 13:32:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

int		sda_setup_copy(t_sda *e, t_obj *obj, char **av)
{
	t_obj				*src;
	t_obj				*copy;
	const unsigned int	id = (unsigned int)ft_atoi(av[0]);

	ft_putendl("copy start");
	if (!id)
	{
		ft_putendl_fd("error: refusing to copy id 0: this is root you idiot !",
			2);
		return (0);
	}
	src = rt_obj_byid(e->root, id);
	if (!src)
		return (0);
	copy = rt_obj_copy_node(src, obj);
	rt_debug(copy, 0);
	ft_putendl("copy ok");
	return (1);
}
