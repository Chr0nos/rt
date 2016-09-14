/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 19:46:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 16:34:18 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "arguments.h"
#include "libft.h"
#include "menu.h"
#include "sda.h"
#include "interface.h"

int				togglefs(t_rt *rt)
{
	SDL_SetWindowFullscreen(rt->sys.win,
		(unsigned int)((rt->keyboard & FULLSCREEN) ? \
		~SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_FULLSCREEN_DESKTOP));
	rt_event_resize_force(draw_getgeometry(rt->sys.win), rt);
	rt->keyboard ^= FULLSCREEN;
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
	{
		ft_printf("sdl error: %s\n", SDL_GetError());
	}
	draw_reset_surface(rt->sys.screen, COLOR_BLACK);
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}

static int		togglefilters(t_rt *rt, int keycode)
{
	const int	bit = 1 << (keycode - SDLK_1 + 17);
	const char	stop = (rt->keyboard & bit) ? 1 : 0;

	rt->keyboard &= ~FILTER;
	rt->keyboard |= FORCE_DISPLAY;
	if (!stop)
		rt->keyboard |= bit;
	menu_kb_copy(rt);
	return (0);
}

static int		togglefinterf(t_rt *rt)
{
	if (!(rt->interf.flags & INTER_ENABLED) &&
		(rt->sys.geometry.x > INTERF_GEO.x) &&
		(rt->sys.geometry.y >= INTERF_GEO.y))
	{
		rt->interf.flags |= INTER_ENABLED;
		interface_init(rt);
		interface_display(rt);
		sdl_flush(rt);
	}
	else if (rt->interf.flags & INTER_ENABLED)
	{
		rt->interf.flags ^= INTER_ENABLED;
		if (rt->render_screen)
		{
			draw_blitsurface(rt->sys.screen, rt->render_screen, (t_v2i){0, 0});
			sdl_flush(rt);
		}
		else
			rt->keyboard |= FORCE_DISPLAY;
	}
	return (0);
}

int				toggle_key(int keycode, t_rt *rt)
{
	if (keycode == SDLK_o && (!(rt->keyboard & MENU)))
		geo_putm4(((t_obj*)rt->root->content)->trans, 6);
	else if (keycode == SDLK_r)
		return (camera_reset(rt));
	else if (keycode == SDLK_y)
		camera_save(rt);
	IFRET__(keycode == SDLK_f, togglefs(rt));
	if (keycode == SDLK_i && (!(rt->keyboard & MENU)))
		return (togglefinterf(rt));
	else if ((keycode >= SDLK_1) && (keycode <= SDLK_7))
		return (togglefilters(rt, keycode));
	else if ((keycode == SDLK_x) && (!(rt->keyboard & MENU)))
		sda_export(rt, 1);
	else if (keycode == SDLK_b)
		sda_export_bitmap_file("save.bmp", rt->sys.screen);
	else if (keycode == SDLK_t)
		textures_used_display(rt->root);
	else if (keycode == SDLK_l)
		rt_debug(rt->root, 0);
	else if (keycode == SDLK_m && (!(rt->keyboard & MENU)))
		return (camera_switch(rt));
	else if (keycode == SDLK_h)
		arg_display_help(rt, 0, NULL);
	return (0);
}
