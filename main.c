/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:19:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/20 12:07:38 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "dirent.h"
#include "libft.h"
#include "keyboard.h"
#include "parser.h"

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

static int		rt_start(t_rt *rt)
{
	if (draw_init(&rt->sys, draw_make_px(1024, 768), "RTv1") < 0)
		return (1);
	if (draw_init_openglcontext(&rt->sys))
		return (1);
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
		ft_putendl("error: failed to get sdl surface from screen");
	else
	{
		draw_reset_surface(rt->sys.screen, COLOR_BLACK);
		SDL_UpdateWindowSurface(rt->sys.win);
		while ((!sdl_loop(&rt->sys.events, rt)) && (!display(rt)))
			SDL_Delay(1);
	}
	draw_quit(&rt->sys);
	return (0);
}

static int	read_file(char	**av)
{
	DIR* rep = NULL;
	struct dirent* fichier_lu = NULL;
	int	i;

	i = -1;
	if ((rep = opendir("./scenes/")) == NULL)
	{
		ft_putendl_fd("opendir faile\n", 2);
		exit(-1);
	}
	while ((fichier_lu = readdir(rep)) != NULL && i < 11)
	{
		if (fichier_lu->d_name[0] != '.')
			av[++i] = ft_strdup(fichier_lu->d_name);
		ft_printf("av[%d] = %s.\n", i, av[i]); // debug a sup a la fin.
	}
	if (closedir(rep) == -1)
		exit(-1);
	return (i);
}

int				main(int ac, char **av)
{
	t_rt	rt;
	int		new_ac;
	char	**new_av;

	if (ac == 1)
	{
		new_av = (char**)ft_memalloc(sizeof(char**));
		new_ac = read_file(new_av);
	}
	else if (ac >= 2)
	{
		rt.mouse = 0;
		rt.keyboard = FORCE_DISPLAY;
		rt.settings = (t_rtcfg){0.0, RTMODE};
		if (!(rt.root = yolo_parse(av[1], &(rt.settings))))
		{
			ft_putendl_fd("error.", 2);
			return (1);
		}
		if (rt.root->content)
		{
			rt_node_foreach(rt.root, INFIX, rt_node_display, NULL);
			ft_putchar('\n');
			rt_start(&rt);
		}
		else
			ft_putstr("no camera\n");
		rt_node_free(rt.root);
	}
	return (0);
}
