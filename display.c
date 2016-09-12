/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 23:21:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/12 14:41:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"
#include "interface.h"

/*
** this function duplicate the current render screen into rt->render_screen
*/

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
	SDL_UpdateWindowSurface(rt->sys.win);
	return (0);
}

static int		display_real(t_rt *rt, const int ret)
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
	{
		interface_display(rt);
		sdl_flush(rt);
	}
	if (ret & FORCE_DISPLAY)
		rt->keyboard ^= FORCE_DISPLAY;
	return (0);
}

static int		refresh_interface(t_rt *rt)
{
	if (!rt->render_screen)
	{
		return (display_real(rt, 0));
	}
	if (rt->settings.cfgbits & RT_CFGB_REFRESHINTER)
	{
		draw_blitsurface(rt->sys.screen, rt->render_screen, (t_v2i){0, 0});
		interface_display(rt);
		sdl_flush(rt);
		rt->settings.cfgbits &= ~RT_CFGB_REFRESHINTER;
		rt->keyboard &= ~FORCE_DISPLAY;
	}
	return (0);
}

int				display(t_rt *rt)
{
	int		ret;

	if (rt->settings.cfgbits & RT_CFGB_INTERFEDIT)
		return (refresh_interface(rt));
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
