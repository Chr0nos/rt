/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 17:02:01 by snicolet         ###   ########.fr       */
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
	SDL_Surface		*screen;
	t_interface_cfg	*cfg;

	if (!rt->interf.flags & INTER_INITIALIZED)
		return ;
	screen = rt->interf.screen;
	if (!screen)
		return ;
	p = INTERF_ITEMS;
	while (p--)
	{
		cfg = &g_interface[p];
		if (!cfg->title)
			continue ;
		draw_blitsurface_blend(screen, cfg->title, cfg->offset, &blend_menu);
	}
}
