/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 21:19:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 20:31:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"

static void				rt_event_resize_menu(t_rt *rt)
{
	menu_configure_thumbs_size(rt);
	menu_background_update(rt);
	menu_update_positions(rt);
}

int						rt_event_resize(SDL_Event *event, t_rt *rt)
{
	rt->sys.geometry = (t_v2i){event->window.data1, event->window.data2};
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
		return (2);
	if (rt->keyboard & MENU)
		rt_event_resize_menu(rt);
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}
