/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 20:11:59 by qloubier          #+#    #+#             */
/*   Updated: 2016/09/01 18:04:02 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"

void		rt_init_rt_rendermode(t_rt *rt, void (*cbf)(t_rt *))
{
	rt->rayfunc = &rt_render_ray;
	rt->tree = rt_render_tree(rt->root);
	if (rt->tree.memlen == 0)
	{
		ft_putendl_fd("error: failed to malloc render tree", 2);
		return ;
	}
	cbf(rt);
	rt->tree.memlen = 0;
	free(rt->tree.bounded);
}
