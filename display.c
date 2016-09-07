/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 23:21:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/07 21:54:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"
#include "interface.h"

static int		rt_display_dumprender(t_rt *rt)
{
	if (rt->settings.cfgbits & RT_CFGB_INMENU)
		return (0);
	if (!rt->render_screen)
		rt->render_screen = draw_make_surface(rt->sys.geometry);
	else if ((rt->render_screen->w != rt->sys.geometry.x) ||
		(rt->render_screen->h != rt->sys.geometry.y))
	{
		SDL_FreeSurface(rt->render_screen);
		rt->render_screen = draw_make_surface(rt->sys.geometry);
	}
	if (!rt->render_screen)
		return (-1);
	draw_blitsurface(rt->render_screen, rt->sys.screen, (t_v2i){0, 0});
	return (1);
}

int				sdl_flush(const t_rt *rt)
{
	SDL_LockSurface(rt->sys.screen);
	SDL_UpdateWindowSurface(rt->sys.win);
	SDL_UnlockSurface(rt->sys.screen);
	return (0);
}

static void		display_real(t_rt *rt, const int ret)
{
	if ((!(rt->settings.cfgbits & RT_CFGB_REFRESHINTER)) ||
		(!rt->render_screen))
	{
		rt_render(rt);
		rt_display_dumprender(rt);
	}
	else
		draw_blitsurface(rt->sys.screen, rt->render_screen, (t_v2i){0, 0});
	if (rt->interf.flags & INTER_ENABLED)
		interface_display(rt);
	if (ret & FORCE_DISPLAY)
		rt->keyboard ^= FORCE_DISPLAY;
}

int				display(t_rt *rt)
{
	int		ret;

	if (rt->settings.cfgbits & RT_CFGB_INTERFEDIT)
	{
		if (rt->settings.cfgbits & RT_CFGB_REFRESHINTER)
		{
			draw_blitsurface(rt->sys.screen, rt->render_screen, (t_v2i){0, 0});
			interface_display(rt);
			sdl_flush(rt);
			rt->settings.cfgbits ^= RT_CFGB_REFRESHINTER;
		}
		return (0);
	}
	if ((ret = movemyass(rt)) & QUIT)
	{
		ft_putendl("quit requested");
		return (1);
	}
	else if ((!(ret & FORCE_DISPLAY)) && (ret == 0) &&
		(!(rt->keyboard & MENU)) &&
		(!(rt->settings.cfgbits & RT_CFGB_REFRESHINTER)))
		return (0);
	if (rt->keyboard & MENU)
	{
		if (!(rt->keyboard & (MOVE | FORCE_DISPLAY)))
			return (0);
		menu_display(rt);
	}
	else
		display_real(rt, ret);
	return (sdl_flush(rt));
}
