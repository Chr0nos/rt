/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 23:21:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 18:11:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"

int				display(t_rt *rt)
{
	int		ret;

	if ((ret = movemyass(rt)) & QUIT)
	{
		ft_putendl("quit requested");
		return (1);
	}
	if ((ret & (FORCE_DISPLAY | MENU)) || (ret != 0))
	{
		if (ret & FORCE_DISPLAY)
			rt->keyboard ^= FORCE_DISPLAY;
		if (rt->keyboard & MENU)
			menu_display(rt);
		else
			rt_rays(rt);
		SDL_LockSurface(rt->sys.screen);
		SDL_UpdateWindowSurface(rt->sys.win);
		SDL_UnlockSurface(rt->sys.screen);
	}
	return (0);
}
