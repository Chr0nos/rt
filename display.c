/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 23:21:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 21:16:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"

static int		sdl_flush(t_rt *rt)
{
	SDL_LockSurface(rt->sys.screen);
	SDL_UpdateWindowSurface(rt->sys.win);
	SDL_UnlockSurface(rt->sys.screen);
	return (0);
}

int				display(t_rt *rt)
{
	int		ret;

	if ((ret = movemyass(rt)) & QUIT)
	{
		ft_putendl("quit requested");
		return (1);
	}
	if ((!(ret & FORCE_DISPLAY)) && (ret == 0) && (!(rt->keyboard & MENU)))
		return (0);
	if (rt->keyboard & MENU)
	{
		if (!(rt->keyboard & (MOVE | FORCE_DISPLAY)))
			return (0);
		menu_display(rt);
	}
	else
	{
		rt_rays(rt);
		if (ret & FORCE_DISPLAY)
			rt->keyboard ^= FORCE_DISPLAY;
	}
	return (sdl_flush(rt));
}
