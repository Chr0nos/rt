/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 23:17:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/06 15:24:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "libft.h"
#include "keyboard.h"

int				movemyass(t_rt *rt)
{
	const int		k = rt->keyboard;
	const double	offset = 0.5;

	if (k & ZOOMIN)
		((t_obj*)rt->root->content)->trans.w.z += offset;
	if (k & ZOOMOUT)
		((t_obj*)rt->root->content)->trans.w.z -= offset;
	if (k & RIGHT)
		((t_obj*)rt->root->content)->trans.w.x -= offset;
	if (k & LEFT)
		((t_obj*)rt->root->content)->trans.w.x += offset;
	if (k & UP)
		((t_obj*)rt->root->content)->trans.w.y += offset;
	if (k & DOWN)
		((t_obj*)rt->root->content)->trans.w.y -= offset;
	if (k & QUIT)
		return (QUIT);
	if (k & (ROTATE_LEFT | ROTATE_RIGHT | ROTATE_DOWN | ROTATE_UP))
		camera_rotate(rt, 0.1, k);
	return (k & (ZOOMIN | ZOOMOUT | RIGHT | LEFT | UP | DOWN | ROTATE_LEFT |
				ROTATE_RIGHT | ROTATE_UP | ROTATE_DOWN | FORCE_DISPLAY));
}

static int		getkeybit(const int keycode)
{
	const t_kbcmp	cmp[] = {
		{SDLK_e, ZOOMIN},
		{SDLK_q, ZOOMOUT},
		{SDLK_ESCAPE, QUIT},
		{SDLK_w, UP},
		{SDLK_s, DOWN},
		{SDLK_a, RIGHT},
		{SDLK_d, LEFT},
		{SDLK_UP, ROTATE_UP},
		{SDLK_DOWN, ROTATE_DOWN},
		{SDLK_LEFT, ROTATE_LEFT},
		{SDLK_RIGHT, ROTATE_RIGHT},
		{SDLK_p, FORCE_DISPLAY}
	};
	unsigned int	p;

	p = sizeof(cmp);
	while (p--)
		if (cmp[p].key == keycode)
			return (cmp[p].bit);
	return (-1);
}

int				keydown(int keycode, t_rt *rt)
{
	const int		keybit = getkeybit(keycode);

	if ((keybit < 0) || (rt->keyboard & QUIT))
		return (0);
	rt->keyboard |= keybit;
	return (0);
}

int				keyrlz(int keycode, t_rt *rt)
{
	const int		keybit = getkeybit(keycode);

	if (keybit < 0)
		return (0);
	rt->keyboard ^= keybit;
	return (0);
}

int				mouseclick(SDL_Event *event, t_rt *rt)
{
	if (event->motion.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
			rt->keyboard |= ZOOMIN;
		else if (event->button.button == SDL_BUTTON_RIGHT)
			rt->keyboard |= ZOOMOUT;
	}
	else
	{
		if ((event->button.button == SDL_BUTTON_LEFT) &&
			(rt->keyboard & ZOOMIN))
			rt->keyboard ^= ZOOMIN;
		else if ((event->button.button == SDL_BUTTON_RIGHT) &&
			(rt->keyboard & ZOOMOUT))
			rt->keyboard ^= ZOOMOUT;
	}
	return (0);
}

int				sdl_event(SDL_Event *event, t_rt *rt)
{
	if (event->type == SDL_QUIT)
		return (1);
	else if ((event->type == SDL_WINDOWEVENT) &&
		(event->window.event == SDL_WINDOWEVENT_RESIZED))
	{
		rt->sys.geometry = draw_make_px(event->window.data1,
			event->window.data2);
		if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
			return (2);
	}
	else if (event->type == SDL_KEYDOWN)
		return (keydown(event->key.keysym.sym, rt));
	else if (event->type == SDL_KEYUP)
		return (keyrlz(event->key.keysym.sym, rt));
	else if ((event->type == SDL_MOUSEBUTTONDOWN) ||
		(event->type == SDL_MOUSEBUTTONUP))
		return (mouseclick(event, rt));
	return (0);
}
