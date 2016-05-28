/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 23:17:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/28 21:24:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "libft.h"

static void		rt_rays(t_rt *rt)
{
	t_obj		*cam;
	t_ray		ray;
	t_point		px;
	t_matrix	m;

	m = draw_make_matrix_iso(0, 0, rt->sys.geometry.x, rt->sys.geometry.y);
	cam = (t_obj*)rt->root->content;
	ray.start = (t_v3f){0.5, 0.5, 0.5};
	px = draw_raster_px(ray.start, &m);
	ft_printf("x: %d y: %d\n", px.x, px.y);
}

int				keydown(int keycode, t_rt *rt)
{
	if (keycode == SDLK_ESCAPE)
		return (1);
	if (keycode == SDLK_d)
		rt_rays(rt);
	(void)keycode;
	(void)rt;
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
