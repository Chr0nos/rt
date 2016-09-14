/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_geometry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 19:12:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 08:16:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "arguments.h"
#include "libft.h"

int			arg_geometry(t_rt *rt, int ac, char **av)
{
	size_t		pixels_count;

	(void)ac;
	rt->sys.geometry = arg_getgeo(*av);
	if ((!rt->sys.geometry.x) || (!rt->sys.geometry.y))
	{
		ft_putstr_fd("invalid geometry\n", 2);
		return (PARSE_ARG_ERROR);
	}
	pixels_count = (size_t)rt->sys.geometry.x * (size_t)rt->sys.geometry.y *
		sizeof(int);
	if (pixels_count > 2147383647)
	{
		ft_putstr_fd("error: size is too big: refusing job\n", 2);
		return (PARSE_ARG_ERROR);
	}
	ft_printf("geometry set: x: %d y: %d\n", rt->sys.geometry.x,
		rt->sys.geometry.y);
	return (1);
}
