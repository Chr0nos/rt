/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/19 02:43:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "shaders.h"

static void print_debug_champs(char *interface[NB_CHAMPS][LARGER_SIZE]) //tmp debug
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS)
	{
		if (*interface[i])
		{
			ft_putstr(*interface[i]);
			ft_putchar('\n');
		}
		else
			ft_putstr("warning: null intem in champs\n");
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

static void print_surface(SDL_Surface *interface[NB_CHAMPS],
	SDL_Surface *screen, SDL_Rect *pos, int font_size)
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS)
	{
		if (!(i % 3))
			pos->y += font_size + 3;
		pos->y += font_size + 3;
		//fonction interdite :)
		//SDL_BlitSurface(interface[i], NULL, screen, pos);
		(void)blend_menu;
		draw_blitsurface_blend(screen, interface[i], (t_v2i){pos->x, pos->y}, &blend_menu);
	}
}

void draw_interface(t_rt *rt)
{
	//print_debug_champs(rt->interf->champs_txt); //tmp debug
	ft_putstr("coucou1\n");
	rt->interf->pos.x = 10;
	rt->interf->pos.y = 10;
	print_surface(rt->interf->surface_txt, rt->sys.screen,
		&rt->interf->pos, rt->interf->font_size);
	ft_putstr("coucou2\n");
	define_selected_obj(rt_obj_byid(rt->root, rt->interf->id_selected), rt->interf->champs_obj); //systeme de selection d'objet a implementer == event.
	ft_putstr("coucou3\n");
	print_debug_champs(rt->interf->champs_obj); //tmp debug
	init_surface_data(rt->interf->champs_obj, rt->interf->surface_obj,
		rt->interf->police_selected, &rt->interf->color_selected);
	ft_putstr("coucou4\n");
	rt->interf->pos.x = 130;
	rt->interf->pos.y = 10;
	ft_putstr("coucou5\n");
	print_surface(rt->interf->surface_obj, rt->sys.screen,
		&rt->interf->pos, rt->interf->font_size);
	free_champs(rt->interf->champs_obj);
	free_surfaces(rt->interf->surface_obj);
}
