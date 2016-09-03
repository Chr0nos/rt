/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:33:02 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 15:18:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "draw.h"

static int		interface_font_init(t_interf *me)
{
	int					n;
	t_interface_font	*font;

	me->fonts[0] = (t_interface_font){"interface/font/monkey.ttf", 3,
		0xffffff, NULL};
	me->fonts[1] = (t_interface_font){"interface/font/pointfree.ttf", 3,
		0xe4ffc0, NULL};
	n = INTERF_FONTS;
	while (n--)
	{
		font = &me->fonts[n];
		font->font = TTF_OpenFont(font->path, font->size);
	}
	n = INTERF_ITEMS;
	while (n--)
		g_interface[p].title = TTF_RenderText_Blended(me->fonts[0].font,
			g_interface[p].name, (SDL_Color)me->fonts[0].color);
	return (0);
}

int				interface_init(t_rt *rt)
{
	if (!TTF_Init() < 0)
		return ;
	if (!(me->screen = draw_make_surface((t_v2i){768, 300})))
	{
		TTF_Quit();
		return (-1);
	}
	interface_font_init(rt->interface);
	return (0);
}
