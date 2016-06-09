/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putbounds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 06:24:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/09 05:34:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

void	rt_putbounds(t_obj *obj, unsigned int p)
{
	char				*x[6];

	x[0] = ft_dtoa((double)obj->bounds.xmin, p);
	x[1] = ft_dtoa((double)obj->bounds.xmax, p);
	x[2] = ft_dtoa((double)obj->bounds.ymin, p);
	x[3] = ft_dtoa((double)obj->bounds.ymax, p);
	x[4] = ft_dtoa((double)obj->bounds.zmin, p);
	x[5] = ft_dtoa((double)obj->bounds.zmax, p);
	ft_printf("[%s:%s] [%s:%s] [%s:%s]\n", x[0], x[1], x[2], x[3], x[4], x[5]);
	ft_free_tab(x, 6);
}
