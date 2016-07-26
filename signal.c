/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 22:49:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/27 01:14:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#ifndef SIGUSR1
# define SIGUSR1 30
#endif

void		rt_signal_singletone(t_v2i *geometry, t_v2i *px, char delete)
{
	static t_v2i	*pts[2];
	char			pc;

	if (delete)
	{
		pts[0] = NULL;
		pts[1] = NULL;
		return ;
	}
	else if ((geometry) && (px))
	{
		pts[0] = geometry;
		pts[1] = px;
	}
	else if ((!pts[0]) || (!pts[1]))
		return ;
	pc = rt_rays_pc(*pts[0], *pts[1]);
	//ft_printf("status: %d%%\n", (int)pc);
}

void		rt_signal(int num)
{
	if (num == SIGUSR1)
		rt_signal_singletone(NULL, NULL, 0);
}
