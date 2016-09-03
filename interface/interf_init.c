/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:33:02 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/03 17:20:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "draw.h"
#include "rt.h"
#include <stdlib.h>

static SDL_Color	interface_color(unsigned int color)
{
	return ((SDL_Color){
		(color & 0xff000000) >> 24,
		(color & 0x00ff0000) >> 16,
		(color & 0x0000ff00) >> 8,
		(color & 0x000000ff)
	});
}

static int			interface_font_prerender(const t_interf *me, int n)
{
	t_interface_cfg		*cfg;

	while (n--)
	{
		cfg = &g_interface[n];
		cfg->title = TTF_RenderText_Blended(me->fonts[0].font,
			cfg->name, interface_color(me->fonts[0].color));
		if (!cfg->title)
			return (-2);
	}
	return (0);
}

static int			interface_font_init(t_interf *me)
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
		if (!(font->font = TTF_OpenFont(font->path, font->size)))
			return (-1);
		TTF_SetFontStyle(font->font, TTF_STYLE_UNDERLINE);
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
		cfg = &g_interface[n];
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
	if (TTF_Init() < 0)
		return (-1);
	if (!(rt->interf.screen = draw_make_surface((t_v2i){300, 768})))
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
