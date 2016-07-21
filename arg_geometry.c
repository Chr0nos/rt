/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_geometry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 19:12:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/21 19:13:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "arguments.h"
#include "libft.h"

int			arg_geometry(t_rt *rt, int ac, char **av)
{
	(void)ac;
	rt->sys.geometry = arg_getgeo(*av);
	ft_printf("geometry set: x: %d y: %d\n", rt->sys.geometry.x,
		rt->sys.geometry.y);
	return (1);
}
