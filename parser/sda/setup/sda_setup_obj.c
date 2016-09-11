/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 18:37:06 by alhote            #+#    #+#             */
/*   Updated: 2016/09/03 21:54:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "parser.h"
#include "libft.h"
#include "mesh.h"
#include <stdlib.h>

int			sda_setup_obj(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	if (parse_obj(obj, av[0]) < 0)
	{
		ft_printf("Can't open %s\n", av[0]);
		return (-1);
	}
	if (!(((t_mesh*)(obj->content))->filepath = ft_strdup(av[0])))
	{
		ft_putstr_fd("error: failed to malloc filepath\n", 2);
		return (-2);
	}
	return (1);
}
