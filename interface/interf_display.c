/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/17 10:41:19 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static void print_debug_champs(char *interface[NB_CHAMPS][LARGER_SIZE]) //tmp debug
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS)
	{
		ft_putstr(*interface[i]);
		ft_putstr("\n");
	}
	ft_putstr("\n");
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
		SDL_BlitSurface(interface[i], NULL, screen, pos);
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
