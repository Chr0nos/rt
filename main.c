/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:19:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 20:52:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "libft.h"
#include "keyboard.h"
#include "parser.h"
#include "menu.h"
#include "sda.h"
#include "arguments.h"
#include "interface.h"

static int		sdl_loop(SDL_Event *event, t_rt *rt)
{
	while (SDL_PollEvent(event))
	{
		if (sdl_event(event, rt))
		{
			ft_putendl("#exit requested...");
			return (1);
		}
	}
	return (0);
}

int				rt_create_window(t_rt *rt)
{
	if (draw_init(&rt->sys, rt->sys.geometry, "RT") < 0)
		return (1);
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
	{
		ft_putendl("error: failed to get sdl surface from screen");
		return (1);
	}
	draw_reset_surface(rt->sys.screen, COLOR_BLACK);
	if (rt->settings.cfgbits & RT_CFGB_FULLSCREEN)
		togglefs(rt);
	return (0);
}

int				rt_start(t_rt *rt)
{
	SDL_UpdateWindowSurface(rt->sys.win);
	while ((!sdl_loop(&rt->sys.events, rt)) && (!display(rt)))
		SDL_Delay(1);
	if (rt->keyboard & MENU)
		menu_clean(rt, -1);
	return (0);
}

int				rt_normal(t_rt *rt, const char *path)
{
	if (!path || ls_isdir(path) == 1)
		menu_init(rt, path);
	else
	{
		if (!(rt->root = rt_parser(path, rt)))
		{
			ft_putendl_fd("error.", 2);
			return (1);
		}
		if (rt_checkcamera(rt))
		{
			if (!rt_create_window(rt))
				rt_start(rt);
		}
		else
			ft_putstr("#no camera\n");
	}
	ft_putendl("#normal end");
	return (0);
}

int				main(int ac, char **av)
{
	t_rt	rt;

	rt_configure(&rt);
	if (ac > 1)
		return (rt_quit(&rt, arg_parse(&rt, ac - 1, av + 1)));
	return (rt_quit(&rt, rt_normal(&rt, NULL)));
}
