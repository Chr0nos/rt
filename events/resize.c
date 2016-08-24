/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 21:19:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 20:11:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"

/*
** DONT TOUCH:
** it's magic, i mean, the kind of dark magic summoned by dark math wizard
** just go to an other file and pretent you never see this.
*/

static void		rt_event_resize_menu(t_rt *rt)
{
	menu_configure_thumbs_size(rt);
	menu_background_update(rt);
	menu_update_positions(rt);
}

static void		change_mode_interf(t_rt *rt)
{
	if (rt->interf->mode_activated &&
		(rt->sys.geometry.x < 260 || rt->sys.geometry.y < 770))
	{
		rt->interf->mode_activated = 0;
		clean_interface(rt);
	}
}

int				rt_event_resize(SDL_Event *event, t_rt *rt)
{
	rt->sys.geometry = draw_make_px(event->window.data1,
		event->window.data2);
	change_mode_interf(rt);
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
		return (2);
	if (rt->keyboard & MENU)
		rt_event_resize_menu(rt);
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}
