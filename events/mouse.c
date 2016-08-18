/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:40:57 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/18 15:50:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"
#include "libft.h"
#include "objects.h"

static void		menu_update_params(t_rt *rt)
{
	rt->rts_size = 0;
	rt->rts = NULL;
	rt->keyboard &= FULLSCREEN;
	rt->keyboard |= FORCE_DISPLAY;
	rt->settings.cfgbits &= RT_CFGB_INMENU;
	//textures_cleanup(rt->root, rt->textures);
}

static int		menu_click(SDL_Event *event, t_rt *rt)
{
	int		id;
	t_rt	tmp_rt;

	if (event->motion.type == SDL_MOUSEBUTTONDOWN)
	{
		id = menu_position_id(rt, event->motion.x, event->motion.y);
		ft_printf("id: %d\n", id);
		if (id >= 0)
		{
			if ((!rt_checkcamera(&rt->rts[id])) || (!rt->rts[id].root) ||
				(!rt->rts[id].sys.screen))
				return (0);
			ft_printf("menu: opening id: %d\n", id);
			tmp_rt = rt->rts[id];
			tmp_rt.sys = rt->sys;
			rt->rts[id].root = NULL;
			menu_clean(rt, id);
			*rt = tmp_rt;
			menu_update_params(rt);
		}
	}
	return (0);
}

int				mouseclick(SDL_Event *event, t_rt *rt)
{
	t_v2i	pos;

	SDL_GetMouseState(&pos.x, &pos.y);
	if (rt->keyboard & MENU)
		return (menu_click(event, rt));
	if (event->motion.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			ft_printf("click at: x: %d y: %d\n", pos.x, pos.y);
			rt_debug(rt_obj_atpx(rt, pos), 0);
			ft_putchar('\n');
			//	rt->keyboard |= ZOOMIN;
		}
		else if (event->button.button == SDL_BUTTON_RIGHT)
			rt->keyboard |= ZOOMOUT;
	}
	else
	{
		if ((event->button.button == SDL_BUTTON_LEFT) &&
			(rt->keyboard & ZOOMIN))
			rt->keyboard ^= ZOOMIN;
		else if ((event->button.button == SDL_BUTTON_RIGHT) &&
			(rt->keyboard & ZOOMOUT))
			rt->keyboard ^= ZOOMOUT;
	}
	return (0);
}
