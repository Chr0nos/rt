/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_positions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 19:26:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/27 12:50:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"

void	menu_update_positions(t_rt *rt)
{
	SDL_Rect	rect;
	size_t		p;

	if ((!rt->menu.items.x) || (!rt->menu.items.y))
		return ;
	rect = (SDL_Rect){MENU_PADDING_X, MENU_PADDING_Y,
		rt->menu.thumb.x, rt->menu.thumb.y};
	p = 0;
	while (p < rt->rts_size)
	{
		rt->menu.positions[p] = rect;
		if (((p + 1) % (size_t)rt->menu.items.x == 0) && (p))
		{
			rect.x = MENU_PADDING_X;
			rect.y += MENU_BORDER_Y + rt->menu.thumb.y;
		}
		else
			rect.x += MENU_BORDER_X + rt->menu.thumb.x;
		p++;
	}
}

int		menu_position_id(t_rt *rt, int x, int y)
{
	const int	last_id = rt->menu.items.y * rt->menu.items.x;
	int			id;
	SDL_Rect	*rect;

	id = ((int)rt->rts_size > last_id) ? last_id : (int)rt->rts_size;
	while (id--)
	{
		rect = &rt->menu.positions[id];
		if ((x >= rect->x) && (x < (rect->x + rect->w)) &&
			(y >= rect->y) && (y < (rect->y + rect->h)))
			return (id);
	}
	return (-1);
}
