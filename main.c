/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:19:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/21 13:34:09 by snicolet         ###   ########.fr       */
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
#include <unistd.h>

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

int				rt_create_window(t_rt *rt)
{
	if (draw_init(&rt->sys, rt->sys.geometry, "Rt") < 0)
		return (1);
	if (draw_init_openglcontext(&rt->sys))
		return (1);
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
	{
		ft_putendl("error: failed to get sdl surface from screen");
		draw_quit(&rt->sys);
		return (1);
	}
	draw_reset_surface(rt->sys.screen, COLOR_BLACK);
	return (0);
}

int				rt_start(t_rt *rt)
{
	SDL_UpdateWindowSurface(rt->sys.win);
	while ((!sdl_loop(&rt->sys.events, rt)) && (!display(rt)))
		SDL_Delay(1);
	if (rt->keyboard & MENU)
		menu_clean(rt->rts);
	draw_quit(&rt->sys);
	return (0);
}

int			rt_normal(t_rt *rt, int ac, char **av)
{
	if ((ac == 0) || (ls_isdir(av[0]) == 1))
		menu_init(rt, av[0]);
	else
	{
		if (!(rt->root = rt_parser(av[0], rt)))
		{
			ft_putendl_fd("error.", 2);
			return (1);
		}
		if (rt_checkcamera(rt))
		{
			rt_node_foreach(rt->root, INFIX, rt_node_display, NULL);
			ft_putchar('\n');
			if (!rt_create_window(rt))
				rt_start(rt);
		}
		else
			ft_putstr("no camera\n");
		rt_node_free(rt->root);
		textures_free(rt->textures);
	}
	ft_putendl("normal end");
	return (0);
}

int				rt_export(t_rt *rt, int ac, char **av)
{
	int			fd;
	const char	*filepath = av[0];
	const char	*dest = av[1];

	(void)ac;
	rt->settings.fake_texture_load = 1;
	if (!(rt->root = rt_parser(filepath, rt)))
	{
		ft_putendl_fd("error.", 2);
		return (PARSE_ARG_ERROR);
	}
	fd = (dest) ? sda_export_file(dest) : 1;
	if (fd < 0)
		return (PARSE_ARG_ERROR);
	sda_export(rt, fd);
	if (fd != 1)
		close(fd);
	rt_node_free(rt->root);
	textures_free(rt->textures);
	return (PARSE_ARG_STOPALL);
}

int				rt_export_bmp(t_rt *rt, int ac, char **av)
{
	const char	*filepath = av[0];
	const char	*dest = av[1];

	(void)ac;
	if ((rt->root = rt_parser(filepath, rt)))
	{
		SDL_Init(0);
		rt->sys.screen = draw_make_surface(rt->sys.geometry);
		rt_rays(rt);
		sda_export_bitmap_file(dest, rt->sys.screen);
		rt_node_free(rt->root);
		textures_free(rt->textures);
		SDL_FreeSurface(rt->sys.screen);
		SDL_Quit();
		return (PARSE_ARG_STOP);
	}
	return (PARSE_ARG_ERROR);
}

int				main(int ac, char **av)
{
	t_rt	rt;

	rt_configure(&rt);
	if (ac > 1)
		return (arg_parse(&rt, ac - 1, av + 1));
	return (rt_normal(&rt, ac -1 , av + 1));
}
