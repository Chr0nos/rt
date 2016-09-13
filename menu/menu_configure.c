/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_configure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:38:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/13 15:55:29 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "menu.h"
#include "keyboard.h"
#include "parser.h"

void			menu_configure_thumbs_size(t_rt *rt)
{
	int				d;
	const t_v2i		*geo = &rt->sys.geometry;

	d = rt->menu.thumb.x + MENU_BORDER_X;
	rt->menu.items.x = (d) ? (geo->x + MENU_BORDER_X - MENU_PADDING_X) / d : 0;
	d = rt->menu.thumb.y + MENU_BORDER_Y;
	rt->menu.items.y = (d) ? (geo->y + MENU_BORDER_Y - MENU_PADDING_Y) / d : 0;
	menu_update_positions(rt);
	menu_background_init(rt);
}

static void		menu_confiture_id_interf(t_rt *rt_dest, t_rt *rt)
{
	rt_dest->render_screen = NULL;
	rt_dest->textures = rt->textures;
	rt_configure_interface(&rt_dest->interf);
}

static void		*menu_confiture_id(void *userdata)
{
	t_v2i			subgeo;
	t_menu_id		*id;
	t_rt			*d;

	id = userdata;
	d = id->dest;
	subgeo = ((const t_rt*)id->src)->menu.thumb;
	ft_memcpy(d, (const t_rt *)id->src, sizeof(t_rt));
	d->keyboard &= ~MENU;
	d->sys.geometry = subgeo;
	d->settings.cfgbits = RT_CFGB_INMENU | RT_CFGB_NOREFRESHX;
	if ((d->root = rt_parser(id->file, d)))
	{
		d->sys.screen = draw_make_surface(subgeo);
		if (d->sys.screen)
			draw_reset_surface(d->sys.screen, 0x000000);
		else
		{
			rt_node_free(d->root);
			d->root = NULL;
		}
	}
	else
		d->sys.screen = NULL;
	return (d->sys.screen);
}

static void		menu_configure_rts_setup(t_menu_id **id, t_rt *rt,
	t_list *files, int p)
{
	t_rt	*rt_dest;

	rt_dest = &rt->rts[p];
	*id = &rt->menu.id[p];
	(*id)->id = 0;
	(*id)->dest = &rt->rts[p];
	(*id)->src = rt;
	(*id)->file = (const char *)files->content;
}

size_t			menu_configure_rts(t_rt *rt, t_list *files)
{
	int				p;
	t_menu_id		*id;

	rt->menu.positions = (SDL_Rect*)&rt->rts[rt->rts_size];
	if (!(rt->menu.id = malloc(sizeof(t_menu_id) * rt->rts_size)))
		return (0);
	menu_configure_thumbs_size(rt);
	p = 0;
	while ((files))
	{
		menu_configure_rts_setup(&id, rt, files, p);
		if (menu_confiture_id(id) == NULL)
		{
			ft_putstr_fd("menu has failed on: ", 2);
			ft_putendl_fd(id->file, 2);
			id->enabled = 0;
		}
		else
			id->enabled = 1;
		menu_confiture_id_interf(id->dest, rt);
		files = files->next;
		p++;
	}
	textures_display(*rt->textures);
	return ((size_t)p);
}
