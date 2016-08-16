/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 23:21:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/16 10:32:59 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"

void			display_help_arg(void)
{
	ft_putstr(
		"\033[01;032m\n\
		..______________________________________________________________..\n\
		||                                                              ||\n\
		||\033[01;035m                    WELCOME IN OUR RT MENU\
		\033[01;032m        ||\n\
		\\\\______________________________________________________________//\n\
		|                                                                |\n\
		|\
		\033[04;036mNext time, add map and try option :\
		\033[;032m |\n\
		|  -e  : output scene to sda format.                             |\n\
		|  -b  : export scene to image bmp & choose a destination path   |\n\
		|        -> ./rt -e scenes/test.sda ~Desktop/my_image.bmp        |\n\
		|  -s  : define your map size.                                   |\n\
		|        -> ./rt -s 800x800 scenes/test.sda                      |\n\
		|  -fs : full screen mode.                                       |\n\
		|  -x  : disable refresh mode.                                   |\n\
		|________________________________________________________________|\n\
		|____________________________  ENJOY ____________________________|\
		\n\n\033[;m");
}

int				sdl_flush(t_rt *rt)
{
	//draw_blitsurface_dbg_alpha(rt->sys.screen, rt->textures->surface, (t_point){0,0});
	//draw_perlin_aa(rt->sys.screen);
	SDL_LockSurface(rt->sys.screen);
	SDL_UpdateWindowSurface(rt->sys.win);
	SDL_UnlockSurface(rt->sys.screen);
	return (0);
}

int				display(t_rt *rt)
{
	int		ret;

	if ((ret = movemyass(rt)) & QUIT)
	{
		ft_putendl("quit requested");
		return (1);
	}
	if ((!(ret & FORCE_DISPLAY)) && (ret == 0) && (!(rt->keyboard & MENU)))
		return (0);
	if (rt->keyboard & MENU)
	{
		if (!(rt->keyboard & (MOVE | FORCE_DISPLAY)))
			return (0);
		menu_display(rt);
	}
	else
	{
		rt_render(rt);
		if (ret & FORCE_DISPLAY)
			rt->keyboard ^= FORCE_DISPLAY;
	}
	return (sdl_flush(rt));
}
