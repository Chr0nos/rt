/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_configure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:38:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 10:45:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "menu.h"
#include "keyboard.h"
#include "parser.h"

void	menu_configure_thumbs_size(t_rt *rt)
{
	int				d;
	const t_point	*geo = &rt->sys.geometry;

	d = rt->menu.thumb.x + MENU_BORDER_X;
	rt->menu.items.x = (d) ? (geo->x + MENU_BORDER_X - MENU_PADDING_X) / d : 0;
	d = rt->menu.thumb.y + MENU_BORDER_Y;
	rt->menu.items.y = (d) ? (geo->y + MENU_BORDER_Y - MENU_PADDING_Y) / d : 0;
}

size_t	menu_configure_rts(t_rt *rt, t_rt *rts, t_list *files)
{
	size_t			p;
	const t_point	subgeo = rt->menu.thumb;

	rt->menu.positions = (SDL_Rect*)&rt->rts[rt->rts_size];
	menu_configure_thumbs_size(rt);
	menu_update_positions(rt);
	menu_background_init(rt);
	p = 0;
	while (files)
	{
		ft_memcpy(&rts[p], rt, sizeof(t_rt));
		rts[p].keyboard &= ~MENU;
		rts[p].sys.geometry = subgeo;
		if ((rts[p].root = rt_parser((const char *)files->content, &rts[p])))
		{
			if ((rts[p].sys.screen = draw_make_surface(subgeo)))
				draw_reset_surface(rts[p].sys.screen, 0x000000);
			p++;
		}
		else
			rts[p].sys.screen = NULL;
		files = files->next;
	}
	return (p);
}
