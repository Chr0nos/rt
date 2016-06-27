/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_configure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:38:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/27 13:43:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "menu.h"
#include "keyboard.h"
#include "parser.h"

int		menu_configure_rts(t_rt *rt, t_rt *rts, t_list *files)
{
	size_t			p;
	const t_point	subgeo = rt->menu.thumb;

	rt->menu.positions = (SDL_Rect*)&rt->rts[rt->rts_size];
	menu_update_positions(rt);
	menu_background_init(rt);
	p = 0;
	while (files)
	{
		ft_memcpy(&rts[p], rt, sizeof(t_rt));
		rts[p].keyboard &= ~MENU;
		rts[p].sys.geometry = subgeo;
		rts[p].root = yolo_parse((const char*)files->content, &rts[p].settings);
		if (rts[p].root)
		{
			if ((rts[p].sys.screen = draw_make_surface(subgeo)))
				draw_reset_surface(rts[p].sys.screen, 0x000000);
			p++;
		}
		else
			rts[p].sys.screen = NULL;
		files = files->next;
	}
	return (0);
}
