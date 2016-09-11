/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_font.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 01:47:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 01:59:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"

SDL_Color			interface_color(unsigned int color)
{
	return ((SDL_Color){
		(color & 0x00ff0000) >> 16,
		(color & 0x0000ff00) >> 8,
		(color & 0x000000ff),
		(color & 0xff000000) >> 24
	});
}

static int			interface_font_prerender(t_interf *me, int n)
{
	while (n--)
	{
		me->cfg[n].title = TTF_RenderText_Blended(me->fonts[0].font,
			me->cfg[n].name, interface_color(me->fonts[0].color));
		me->cfg[n].title_selected = TTF_RenderText_Blended(me->fonts[2].font,
			me->cfg[n].name, interface_color(me->fonts[2].color));
		if (!me->cfg[n].title)
			return (-2);
		if (!me->cfg[n].title_selected)
			return (-3);
	}
	return (0);
}

int					interface_font_init(t_interf *me)
{
	int					n;
	t_interface_font	*font;

	me->fonts[0] = (t_interface_font){"interface/font/monkey.ttf", 25,
		0xffffff, NULL};
	me->fonts[1] = (t_interface_font){"interface/font/pointfree.ttf", 19,
		0xa4ffc0, NULL};
	me->fonts[2] = (t_interface_font){"interface/font/monkey.ttf", 25,
		0x8080ff, NULL};
	n = INTERF_FONTS;
	while (n--)
	{
		font = &me->fonts[n];
		if (!(font->font = TTF_OpenFont(font->path, font->size)))
			return (-1);
	}
	return (interface_font_prerender(me, INTERF_ITEMS));
}
