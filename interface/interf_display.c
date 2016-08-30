/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/30 21:09:40 by dboudy           ###   ########.fr       */
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

/*
** this function is here to clamp the "pos" rect to the window size and prevent
** any crash du to screen size < menu size
*/
/*
static void			clamp_rect(SDL_Rect *pos, SDL_Surface *screen)
{
	if (screen->w < pos->w)
		pos->w = screen->w;
	if (screen->h < pos->h)
		pos->h = screen->h;
}

*/
static void			print_scale(SDL_Surface **tab_surface, SDL_Surface *screen, SDL_Rect *pos)
{
	int			i;

	i = -1;
	while (tab_surface[++i])
	{
		draw_blitsurface_blend(screen, tab_surface[i],
				(t_v2i){pos->x, pos->y}, &blend_menu);
		pos->x += 45;
	}
}

static void			print_surface(SDL_Surface *tab_surface[NB_CHAMPS],
		SDL_Surface *screen, SDL_Rect *pos)
{
	int	i;

	//clamp_rect(pos, screen);
	i = -1;
	while (++i != I_END)
	{
		if (tab_surface[i] && i != I_VIDE2 && i != I_VIDE3 && i != I_VIDE4
			&& i != I_VIDE5 && i != I_VIDE6 && i != I_VIDE7 && i != I_VIDE8)
			draw_blitsurface_blend(screen, tab_surface[i],
					(t_v2i){pos->x, pos->y}, &blend_menu);
		pos->y += 28;
	}
}

void				interface_display(t_rt *rt)
{
	define_position(&rt->interf->pos, 5, 8);
	print_scale(rt->interf->surface_scale, rt->sys.screen, &rt->interf->pos);
	define_position(&rt->interf->pos, 5, 64);
	print_surface(rt->interf->surface_txt, rt->sys.screen, &rt->interf->pos);
	fill_surfaces(rt->interf->champs_obj, rt->interf->surface_obj,
			rt->interf->police_selected, &rt->interf->color_selected);
	define_position(&rt->interf->pos, 150, 64);
	print_surface(rt->interf->surface_obj, rt->sys.screen, &rt->interf->pos);
	free_surfaces(rt->interf->surface_obj);
}
