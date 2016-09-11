/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_csg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 14:57:13 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/08 23:06:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

int		sda_setup_csg(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (!ft_strcmp(av[0], "negative"))
		obj->flags |= FLAG_CSG_NEGATIVE;
	else if (!ft_strcmp(av[0], "positive"))
		return (0);
	else
		return (-1);
	return (1);
}
