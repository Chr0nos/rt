/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 19:38:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "libft.h"

void			menu_display(t_rt *rt)
{
	const size_t	size = rt->rts_size;
	t_point			px;
	size_t			p;

	(void)size;
	p = 0;
	draw_reset_surface(rt->sys.screen, 0xe97313);

	px = (t_point){10, 10};
	while (p < 6)
	{
		rt_rays(&rt->rts[p]);
		draw_blitsurface(rt->sys.screen, rt->rts[p].sys.screen, px);
		if (((p + 1) % 3 == 0) && (p))
		{
			px.y += 12 + rt->rts[p].sys.geometry.y;
			px.x = 10;
		}
		else
			px.x += 12 + rt->rts[p].sys.geometry.x;
		p++;
	}
}
