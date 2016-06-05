/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 23:21:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/05 21:47:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"

int				display(t_rt *rt)
{
	int		ret;

	if ((ret = movemyass(rt)) & QUIT)
		return (1);
	if ((ret & FORCE_DISPLAY) || (ret != 0))
	{
		if (ret & FORCE_DISPLAY)
			rt->keyboard ^= FORCE_DISPLAY;
		rt_rays(rt);
		SDL_LockSurface(rt->sys.screen);
		SDL_UpdateWindowSurface(rt->sys.win);
		SDL_UnlockSurface(rt->sys.screen);
	}
	return (0);
}
