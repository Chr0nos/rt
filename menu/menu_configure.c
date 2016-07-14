/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_configure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:38:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 13:38:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "menu.h"
#include "keyboard.h"
#include "parser.h"

void			menu_configure_thumbs_size(t_rt *rt)
{
	int				d;
	const t_point	*geo = &rt->sys.geometry;

	d = rt->menu.thumb.x + MENU_BORDER_X;
	rt->menu.items.x = (d) ? (geo->x + MENU_BORDER_X - MENU_PADDING_X) / d : 0;
	d = rt->menu.thumb.y + MENU_BORDER_Y;
	rt->menu.items.y = (d) ? (geo->y + MENU_BORDER_Y - MENU_PADDING_Y) / d : 0;
}

static void		menu_confiture_id(t_rt *dest, const t_rt *src, const char *file)
{
	const t_point	subgeo = src->menu.thumb;

	ft_memcpy(dest, src, sizeof(t_rt));
	dest->keyboard &= ~MENU;
	dest->sys.geometry = subgeo;
	if ((dest->root = rt_parser(file, dest)))
	{
		if ((dest->sys.screen = draw_make_surface(subgeo)))
			draw_reset_surface(dest->sys.screen, 0x000000);
	}
	else
		dest->sys.screen = NULL;
}

size_t			menu_configure_rts(t_rt *rt, t_rt *rts, t_list *files)
{
	size_t			p;

	rt->menu.positions = (SDL_Rect*)&rt->rts[rt->rts_size];
	menu_configure_thumbs_size(rt);
	menu_update_positions(rt);
	menu_background_init(rt);
	p = 0;
	while (files)
	{
		menu_confiture_id(&rts[p++], rt, (const char *)files->content);
		files = files->next;
	}
	return (p);
}
