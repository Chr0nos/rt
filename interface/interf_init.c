/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:33:02 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 20:39:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "draw.h"
#include "rt.h"
#include <stdlib.h>

static SDL_Color	interface_color(unsigned int color)
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
		if (!me->cfg[n].title)
			return (-2);
	}
	return (0);
}

static int			interface_font_init(t_interf *me)
{
	int					n;
	t_interface_font	*font;

	me->fonts[0] = (t_interface_font){"interface/font/monkey.ttf", 25,
		0xffffff, NULL};
	me->fonts[1] = (t_interface_font){"interface/font/pointfree.ttf", 19,
		0xe4ffc0, NULL};
	n = INTERF_FONTS;
	while (n--)
	{
		font = &me->fonts[n];
		if (!(font->font = TTF_OpenFont(font->path, font->size)))
			return (-1);
	}
	return (interface_font_prerender(me, INTERF_ITEMS));
}

void				interface_clean(t_interf *interf)
{
	int				n;
	t_interface_cfg	*cfg;

	n = INTERF_FONTS;
	while (n--)
	{
		cfg = &interf->cfg[n];
		if (cfg->title)
			SDL_FreeSurface(cfg->title);
		if (cfg->value)
			free(cfg->value);
	}
	n = INTERF_FONTS;
	while (n--)
	{
		if (interf->fonts[n].font)
			TTF_CloseFont(interf->fonts[n].font);
	}
	if (interf->screen)
		SDL_FreeSurface(interf->screen);
	TTF_Quit();
	interf->flags &= ~INTER_INITIALIZED;
}

int					interface_init(t_rt *rt)
{
	if (rt->interf.flags & INTER_INITIALIZED)
		return (0);
	ft_memcpy(&rt->interf.cfg, &g_interface,
		sizeof(t_interface_cfg) * INTERF_ITEMS);
	if (TTF_Init() < 0)
		return (-1);
	if (!(rt->interf.screen = draw_make_surface(INTERF_GEO)))
	{
		TTF_Quit();
		ft_putstr_fd("error: failed to init menu surface\n", 2);
		return (-2);
	}
	if (interface_font_init(&rt->interf) < 0)
	{
		ft_freesplit((char **)(unsigned long)rt->interf.fonts);
		ft_putstr_fd("error: failed to unit all fonts\n", 2);
		TTF_Quit();
		return (-3);
	}
	ft_putstr("#Menu init ok\n");
	rt->interf.flags |= INTER_INITIALIZED;
	return (0);
}
