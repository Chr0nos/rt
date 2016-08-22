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

static void print_debug_champs(char *interface[NB_CHAMPS][LARGER_SIZE]) //tmp debug
{
	int	i;

	i = -1;
	while (*interface[++i])
	{
		if (*interface[i])
		{
			ft_putstr(*interface[i]);
			ft_putchar('\n');
		}
		else
			ft_putstr("warning: null item in champs\n");
	}
	ft_putstr("\n");
}


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
	while (tab_surface[i])
	{
		pos->y += font_size + 3;
		if (tab_surface[i])
			draw_blitsurface_blend(screen, tab_surface[i],
				(t_v2i){pos->x, pos->y}, &blend_menu);
	}
}

static void init_champs_obj(char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	int	i;

	i = 0;
	*champs_obj[i] = ft_strdup("no object selected");
	while (*champs_obj[i])
		*champs_obj[i] = ft_strdup("");
}

void interface_display(t_rt *rt)
{
	/*
	** affichage partie blanche :
	*/
	define_position(&rt->interf->pos, 10, 50);
	print_surface(rt->interf->surface_txt, rt->sys.screen,
		&rt->interf->pos, rt->interf->font_size);
	/*
	** affichage partie jaune :
	*/
	if (rt->interf->obj_selected->cfgbits & VISIBLE ||
			rt->interf->obj_selected->cfgbits & LIGHTTYPE)
		fill_champs_obj(rt->interf->obj_selected, rt->interf->champs_obj);
	else
		init_champs_obj(rt->interf->champs_obj);
	print_debug_champs(rt->interf->champs_obj); //tmp debug
	fill_surfaces(rt->interf->champs_obj, rt->interf->surface_obj,
		rt->interf->police_selected, &rt->interf->color_selected);
	define_position(&rt->interf->pos, 130, 50);
	print_surface(rt->interf->surface_obj, rt->sys.screen,
		&rt->interf->pos, rt->interf->font_size);
	free_surfaces(rt->interf->surface_obj);
}
