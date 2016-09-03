/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 15:24:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "shaders.h"

/*
** "a" is the "original pixel"
** "b" is the copied pixels (the one you are trying to copy)
** in case of the menu color: the sdl_ttf just has invert alpha
*/

static unsigned int	blend_menu(unsigned int a, unsigned b)
{
	const unsigned int	alpha = 0xff - ((b & 0xff000000) >> 24);
	const float			pc = (float)alpha / (float)0xff;

	b = (b & 0xffffff) | (alpha << 24);
	if ((R(b) > 240) && (G(b) > 240) && (B(b) > 240) &&
			(R(a) > 240) && (G(a) > 240) && (B(a) > 240))
	{
		b = blend_darken(b, 0x606060);
		return (draw_color_lerp(b, a, pc - 0.3f));
	}
	return (draw_color_lerp(b, a, pc));
}

void				interface_display(t_rt *rt)
{
	int				p;
	char			*text;
	SDL_Surface		*screen;
	SDL_Surface		*value_img;

	screen = rt->interf->screen;
	p = INTERF_ITEMS;
	while (p--)
	{
		value_img = NULL;
		draw_blitsurface_blend(screen,
			g_interface[p].title,
			g_interface[p].offset,
			&blend_menu);
	}
}
