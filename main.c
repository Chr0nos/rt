/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:19:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/29 06:25:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "libft.h"

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
	SDL_Event	event;

	if (draw_init(&rt->sys, draw_make_px(800, 600), "RTv1") < 0)
		return (1);
	if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
		ft_putendl("error: failed to get sdl surface from screen");
	else
	{
		draw_reset_surface(rt->sys.screen, COLOR_BLACK);
		SDL_UpdateWindowSurface(rt->sys.win);
		while (!sdl_loop(&event, rt))
			SDL_Delay(1);
	}
	SDL_DestroyWindow(rt->sys.win);
	SDL_Quit();
	return (0);
}

int				main(int ac, char **av)
{
	t_rt	rt;

	if (ac >= 2)
	{
		rt.root = parse_yolo(av[1]);
		rt_debug(rt.root, 0);
		if (rt.root->content)
		{
			rt_bounds_update(rt.root);
			ft_putstr("\nActive camera: ");
			rt_debug((t_obj*)rt.root->content, 0);
			rt_node_foreach(rt.root, PREFIX, &rt_putbounds, (void*)3);
			(void)rt;
			(void)rt_start;
			//rt_start(&rt);
		}
		else
			ft_putstr("no camera\n");
		rt_obj_free(rt.root, 0);
	}
	return (0);
}
