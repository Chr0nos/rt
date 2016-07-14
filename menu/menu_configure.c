/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_configure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:38:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 14:52:39 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "menu.h"
#include "keyboard.h"
#include "parser.h"
#include <pthread.h>

void			menu_configure_thumbs_size(t_rt *rt)
{
	int				d;
	const t_point	*geo = &rt->sys.geometry;

	d = rt->menu.thumb.x + MENU_BORDER_X;
	rt->menu.items.x = (d) ? (geo->x + MENU_BORDER_X - MENU_PADDING_X) / d : 0;
	d = rt->menu.thumb.y + MENU_BORDER_Y;
	rt->menu.items.y = (d) ? (geo->y + MENU_BORDER_Y - MENU_PADDING_Y) / d : 0;
}

static void		*menu_confiture_id(void *userdata)
{
	t_point			subgeo;
	t_menu_id		*id;

	id = userdata;
	subgeo = ((const t_rt*)id->src)->menu.thumb;
	ft_memcpy(id->dest, (const t_rt*)id->src, sizeof(t_rt));
	((t_rt *)id->dest)->keyboard &= ~MENU;
	((t_rt *)id->dest)->sys.geometry = subgeo;
	if ((((t_rt *)id->dest)->root = rt_parser(id->file, (t_rt *)(id->dest))))
	{
		if ((((t_rt *)id->dest)->sys.screen = draw_make_surface(subgeo)))
			draw_reset_surface(((t_rt *)id->dest)->sys.screen, 0x000000);
	}
	else
		((t_rt *)id->dest)->sys.screen = NULL;
	return (userdata);
}

size_t			menu_configure_rts(t_rt *rt, t_rt *rts, t_list *files)
{
	size_t			p;
	t_menu_id		*id;

	rt->menu.positions = (SDL_Rect*)&rt->rts[rt->rts_size];
	rt->menu.id = malloc(sizeof(t_menu_id) * rt->rts_size);
	menu_configure_thumbs_size(rt);
	menu_update_positions(rt);
	menu_background_init(rt);
	p = 0;
	while (files)
	{
		id = &rt->menu.id[p];
		id->id = 0;
		id->dest = &rts[p];
		id->src = rt;
		id->file = (const char *)files->content;
		menu_confiture_id(&rt->menu.id[p]);
		files = files->next;
		p++;
	}
	return (p);
}
