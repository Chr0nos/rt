/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:19:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/27 18:31:24 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "libft.h"

int				keydown(int keycode, t_rt *rt)
{
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

static int		sdl_loop(SDL_Event *event, t_rt *rt)
{
	while (SDL_PollEvent(event))
	{
		if (sdl_event(event, rt))
		{
			ft_putendl("exit requested...");
			return (1);
		}
	}
	return (0);
}

static int		rt_start(void)
{
	t_rt		rt;
	SDL_Event	event;

	if (draw_init(&rt.sys, draw_make_px(800, 600), "RTv1") < 0)
		return (1);
	if (!(rt.sys.screen = SDL_GetWindowSurface(rt.sys.win)))
		ft_putendl("error: failed to get sdl surface from screen");
	else
	{
		draw_reset_surface(rt.sys.screen, COLOR_WHITE);
		SDL_UpdateWindowSurface(rt.sys.win);
		while (!sdl_loop(&event, &rt))
			SDL_Delay(1);
	}
	SDL_DestroyWindow(rt.sys.win);
	SDL_Quit();
	return (0);
}

int		main(int ac, char **av)
{
	t_obj	*root;

	if (ac >= 2)
	{
		root = parse_yolo(av[1]);
		rt_obj_free(root, 0);
	}
	(void)rt_start;
	return (0);
}
