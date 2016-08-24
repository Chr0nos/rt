/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:40:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 17:59:34 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "libft.h"
#include "menu.h"
#include "sda.h"

int				togglefs(t_rt *rt)
{
	SDL_SetWindowFullscreen(rt->sys.win,
		(unsigned int)((rt->keyboard & FULLSCREEN) ? \
		~SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_FULLSCREEN_DESKTOP));
	rt->sys.geometry = draw_getgeometry(rt->sys.win);
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

static int		switch_camera(t_rt *rt)
{
	t_obj	*cam;
	t_obj	*newcam;

	cam = rt->root->content;
	if (!(newcam = rt_obj_nexttype(rt->root, cam, CAMERA)))
		newcam = rt_obj_nexttype(rt->root, NULL, CAMERA);
	if ((newcam == cam) || (!newcam))
	{
		ft_putendl("no more camera");
		return (0);
	}
	rt->root->content = newcam;
}

static int		togglefinterf(t_rt *rt)
{
	if (!rt->interf->mode_activated &&
		rt->sys.geometry.x > 260 && rt->sys.geometry.y >= 768)
	{
		rt->interf->mode_activated = 1;
		init_interface(rt);
	}
	else if (rt->interf->mode_activated)
	{
		rt->interf->mode_activated = 0;
		clean_interface(rt);
	}
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}

int				keydown(int keycode, t_rt *rt)
{
	const int		keybit = getkeybit(keycode);

	if (keycode == SDLK_o)
		geo_putm4(((t_obj*)rt->root->content)->trans, 6);
	else if (keycode == SDLK_r)
		return (camera_reset(rt));
	else if (keycode == SDLK_y)
		camera_save(rt);
	else if (keycode == SDLK_f)
		return (togglefs(rt));
	else if (keycode == SDLK_i && (!(rt->keyboard & MENU)))
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
	else if (keycode == SDLK_m)
		return (switch_camera(rt));
	if ((keybit < 0) || (rt->keyboard & QUIT))
		return (0);
	rt->keyboard |= keybit;
	menu_kb_copy(rt);
	return (0);
}

int				keyrlz(int keycode, t_rt *rt)
{
	const int		keybit = getkeybit(keycode);

	if ((keybit < 0) || (!(rt->keyboard & keybit)))
		return (0);
	rt->keyboard ^= keybit;
	menu_kb_copy(rt);
	return (0);
}
