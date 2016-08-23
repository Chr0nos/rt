/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/21 18:48:21 by snicolet         ###   ########.fr       */
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
	return (draw_color_lerp(b, a, pc));
}

/*
** this function is here to clamp the "pos" rect to the window size and prevent
** any crash du to screen size < menu size
*/

static void	clamp_rect(SDL_Rect *pos, SDL_Surface *screen)
{
	(void)pos;
	(void)screen;
}

static void print_surface(SDL_Surface *tab_surface[NB_CHAMPS],
	SDL_Surface *screen, SDL_Rect *pos, int font_size)
{
	int	i;

	clamp_rect(pos, screen);
	i = -1;
	while (++i < NB_CHAMPS - 1)
	{
		if (tab_surface[i] && i != I_VIDE1 && i != I_VIDE2 && i != I_VIDE3
			&& i != I_VIDE4 && i != I_VIDE5 && i != I_VIDE6 && i != I_VIDE7
			&& i != I_VIDE8)
			draw_blitsurface_blend(screen, tab_surface[i],
				(t_v2i){pos->x, pos->y}, &blend_menu);
		pos->y += font_size;
		//else
		//	pos->y += font_size + 3;
	}
}

void interface_display(t_rt *rt)
{
	/*
	** affichage partie blanche :
	*/
	define_position(&rt->interf->pos, 10, 2);
	print_surface(rt->interf->surface_txt, rt->sys.screen,
		&rt->interf->pos, rt->interf->font_size);
	/*
	** affichage partie jaune :
	*/
	fill_surfaces(rt->interf->champs_obj, rt->interf->surface_obj,
		rt->interf->police_classic, &rt->interf->color_selected);
	define_position(&rt->interf->pos, 130, 2);
	print_surface(rt->interf->surface_obj, rt->sys.screen,
		&rt->interf->pos, rt->interf->font_size);
	free_surfaces(rt->interf->surface_obj);
}
