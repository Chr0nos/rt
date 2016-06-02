/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 23:17:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/02 17:44:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "libft.h"

static void		display(t_rt *rt)
{
	rt_rays(rt);
	SDL_UpdateWindowSurface(rt->sys.win);
}

int				keydown(int keycode, t_rt *rt)
{
	const double	offset = 1.0;

	if (keycode == SDLK_ESCAPE)
		return (1);
	else if (keycode == SDLK_d)
		((t_obj*)rt->root->content)->trans.w.x += offset;
	else if (keycode == SDLK_a)
		((t_obj*)rt->root->content)->trans.w.x -= offset;
	else if (keycode == SDLK_w)
		((t_obj*)rt->root->content)->trans.w.y += offset;
	else if (keycode == SDLK_s)
		((t_obj*)rt->root->content)->trans.w.y -= offset;
	else if (keycode == SDLK_e)
		((t_obj*)rt->root->content)->trans.w.z += offset;
	else if (keycode == SDLK_q)
		((t_obj*)rt->root->content)->trans.w.z -= offset;
	display(rt);
	return (0);
}

int				keyrlz(int keycode, t_rt *rt)
{
	(void)keycode;
	(void)rt;
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
	return (0);
}
