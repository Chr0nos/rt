/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:54:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 17:15:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "menu.h"
#include "parser.h"
#include "keyboard.h"
#define VIGN_X 4
#define VIGN_Y 3
#define VIGN_PAD 30

static int		menu_configure_rts(t_rt *rt, t_rt *rts, t_list *files)
{
	size_t			p;
	const t_point	*geometry = &rt->sys.geometry;
	const t_point	subgeo = (t_point){
		geometry->x / VIGN_X - (VIGN_PAD * VIGN_X),
		geometry->y / VIGN_Y - (VIGN_PAD * VIGN_Y)
	};

	p = 0;
	while (files)
	{
		ft_memcpy(&rts[p], rt, sizeof(t_rt));
		rts[p].sys.geometry = subgeo;
		rts[p].root = yolo_parse((const char*)files->content, &rts[p].settings);
		if (rts[p].root)
		{
			rts[p].sys.screen = SDL_CreateRGBSurface(0, subgeo.x, subgeo.y,
				24, 0xff0000, 0x00ff00, 0x0000ff, 0xff000000);
			draw_reset_surface(rts[p].sys.screen, 0x30f0b0);
			p++;
		}
		files = files->next;
	}
	return (0);
}

static void		menu_clean(size_t size, t_rt *rts)
{
	while (size--)
	{
		rt_node_free(rts[size].root);
		SDL_FreeSurface(rts[size].sys.screen);
	}
	free(rts);
}

int				menu_init(t_rt *rt)
{
	t_list		*files;
	t_rt		*rts;
	int			ret;

	if (!(files = ls_dir("./scenes/", "*.yolo")))
		return (-2);
	rt->rts_size = ft_lstsize(files);
	if ((rts = malloc(sizeof(t_rt) * rt->rts_size)) != NULL)
	{
		ret = menu_configure_rts(rt, rts, files);
		//code utile ici
		//rt_create_window(rt);
		rt->keyboard |= MENU;
		rt_start(rt);
		menu_clean(rt->rts_size, rts);
	}
	else
		ret = -1;
	ft_lstdel(&files, &ft_lstpulverisator);
	return (ret);
}
