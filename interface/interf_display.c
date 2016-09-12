/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/12 14:42:17 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "shaders.h"
#include <SDL2/SDL.h>

/*
** "a" is the "original pixel"
** "b" is the copied pixels (the one you are trying to copy)
** in case of the menu color: the sdl_ttf just has invert alpha
*/

unsigned int		blend_menu(unsigned int a, unsigned b)
{
	const unsigned int	alpha = 0xff - ((b & 0xff000000) >> 24);
	const float			pc = (float)alpha / (float)0xff;

	if (b == 0xff000000)
		return (a);
	b = (b & 0xffffff) | (alpha << 24);
	if ((R(b) > 220) && (G(b) > 220) && (B(b) > 220) &&
			(R(a) > 220) && (G(a) > 220) && (B(a) > 220))
	{
		b = blend_darken(b, 0x606060);
		return (draw_color_lerp(b, a, pc - 0.3f));
	}
	return (draw_color_lerp(b, a, pc));
}

static inline int	interface_fit(t_v2i geo)
{
	if ((geo.x < INTERF_GEO.x + INTERF_OFFSET.x) ||
		(geo.y < INTERF_GEO.y + INTERF_OFFSET.y))
	{
		ft_putendl("#warning: not enoth space in the window for interface\n");
		return (0);
	}
	return (1);
}

static void			interface_display_value(SDL_Surface *screen,
	t_interface_cfg *cfg, t_obj *obj, t_rt *rt)
{
	char					*value;
	SDL_Surface				*value_surface;
	t_v2i					offset;
	t_interface_font		*fonts;
	int						value_offset;

	if ((!obj) || (!(obj->type & (unsigned int)cfg->mask)) || (!cfg->get_value))
		return ;
	if (cfg->flags & INTER_SELECTED)
		value = ft_strdup(rt->interf.line);
	else if (!(value = cfg->get_value(obj, NULL)))
		return ;
	value_offset = (int)ft_strlen(value) - 20;
	fonts = rt->interf.fonts;
	if ((value_surface = TTF_RenderText_Blended(fonts[1].font,
		&value[(value_offset < 0) ? 0 : value_offset],
		interface_color(fonts[1].color))) != NULL)
	{
		offset = (t_v2i){cfg->offset.x + INTERF_VALOFFSET + INTERF_OFFSETX,
			cfg->offset.y};
		draw_blitsurface(screen, value_surface, offset);
		SDL_FreeSurface(value_surface);
	}
	free(value);
}

void				interface_display(t_rt *rt)
{
	int					p;
	SDL_Surface			*screen;
	t_interface_cfg		*cfg;

	screen = rt->interf.screen;
	if ((!interface_fit(rt->sys.geometry)) || (!screen) || (!rt->sys.screen))
		;
	else if (!rt->interf.flags & INTER_INITIALIZED)
		ft_putendl("#Menu: warning: interface not initialized i will hide\n");
	else
	{
		p = INTERF_ITEMS;
		draw_reset_surface(screen, 0xff000000);
		while (p--)
		{
			cfg = &rt->interf.cfg[p];
			if (!cfg->title)
				continue ;
			draw_blitsurface(screen, (cfg->flags & INTER_SELECTED) ?
				cfg->title_selected : cfg->title, cfg->offset);
			interface_display_value(screen, cfg, rt->interf.obj_selected, rt);
		}
		draw_blitsurface_blend(rt->sys.screen, screen, INTERF_OFFSET,
			&blend_menu);
	}
}
