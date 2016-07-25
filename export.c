/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 19:01:04 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/22 21:01:24 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "parser.h"
#include "libft.h"
#include "sda.h"
#include <unistd.h>

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
	return (PARSE_ARG_STOPALL);
}

int				rt_export_bmp(t_rt *rt, int ac, char **av)
{
	const char	*filepath = av[0];
	const char	*dest = av[1];

	(void)ac;
	ft_putendl("export bmp requested");
	if (((rt->root = rt_parser(filepath, rt))) && (rt_checkcamera(rt)))
	{
		if (SDL_Init(0) < 0)
		{
			ft_putendl_fd("error: failed to init sdl", 2);
			return (PARSE_ARG_ERROR);
		}
		rt->sys.screen = draw_make_surface(rt->sys.geometry);
		draw_reset_surface(rt->sys.screen, COLOR_WHITE);
		rt->settings.cfgbits |= RT_CFGB_FREESCREEN;
		ft_putstr("rendering scene\n");
		rt_render(rt);
		ft_putstr("render done\n");
		sda_export_bitmap_file(dest, rt->sys.screen);
		return (PARSE_ARG_STOPALL);
	}
	else
		ft_putstr_fd("error: failed to parse file.\n", 2);
	return (PARSE_ARG_ERROR);
}
