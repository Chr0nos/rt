/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 17:55:18 by snicolet         ###   ########.fr       */
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

	if (b == 0xff000000)
		return (a);
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
	{
		ft_putendl("#Menu: warning: interface not initialized i will hide\n");
		return ;
	}
	screen = rt->interf.screen;
	if (!screen)
		return ;
	p = INTERF_ITEMS;
	draw_reset_surface(screen, 0xff000000);
	while (p--)
	{
		cfg = &rt->interf.cfg[p];
		if (!cfg->title)
			continue ;
		draw_blitsurface(screen, cfg->title, cfg->offset);
	}
	draw_blitsurface_blend(rt->sys.screen, screen, INTERF_OFFSET,
		&blend_menu);
}
