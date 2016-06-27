/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:54:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/27 13:08:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "menu.h"
#include "parser.h"
#include "keyboard.h"

static int		menu_configure_rts(t_rt *rt, t_rt *rts, t_list *files)
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

void			menu_clean(t_rt *rt)
{
	size_t		size;

ft_putendl("clean");
	size = rt->rts_size;
	while (size--)
	{
		rt_node_free(rt->rts[size].root);
		SDL_FreeSurface(rt->rts[size].sys.screen);
		rt->rts[size].sys.screen = NULL;
	}
	if (rt->menu.background)
	{
		SDL_FreeSurface(rt->menu.background);
		rt->menu.background = NULL;
	}
	free(rt->rts);
	rt->rts_size = 0;
}

int				menu_init(t_rt *rt, const char *path)
{
	t_list		*files;
	int			ret;

	if (!path)
		path = "./scenes/";
	if (!(files = ls_dir(path, "*.yolo")))
	{
		ft_putendl_fd("nothing to do: empty directory", 2);
		return (-2);
	}
	rt->rts_size = ft_lstsize(files);
	if ((rt->rts = malloc(
		(sizeof(t_rt) * rt->rts_size) +
		(sizeof(SDL_Rect) * rt->rts_size))) != NULL)
	{
		rt_create_window(rt);
		ret = menu_configure_rts(rt, rt->rts, files);
		rt->keyboard |= MENU;
		rt_start(rt);
	}
	else
		ret = -1;
	ft_lstdel(&files, &ft_lstpulverisator);
	return (ret);
}
