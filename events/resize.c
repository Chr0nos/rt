/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 21:19:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/22 16:11:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"

int		rt_event_resize(SDL_Event *event, t_rt *rt)
{
	rt->sys.geometry = draw_make_px(event->window.data1,
		event->window.data2);
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
		return (2);
	rt->menu.items.x = rt->sys.geometry.x / (rt->menu.thumb.x + 10);
	rt->menu.items.y = rt->sys.geometry.y / (rt->menu.thumb.y + 10);
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}
