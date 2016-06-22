/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:26:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/22 23:57:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"

void	menu_update_positions(t_rt *rt)
{
	SDL_Rect	rect;
	size_t		p;

	rect = (SDL_Rect){rt->menu.thumb.x, rt->menu.thumb.y,
		MENU_PADDING_X, MENU_PADDING_Y};
	p = 0;
	while (p < rt->rts_size)
	{
		if (((p + 1) % (size_t)rt->menu.items.x == 0) && (p))
		{
			rect.x = MENU_PADDING_X;
			rect.y += MENU_BORDER_Y + rt->rts[p].sys.geometry.y;
		}
		else
			rect.x += MENU_BORDER_X + rt->rts[p].sys.geometry.x;
		rt->menu.positions[p] = rect;
		p++;
	}
}
