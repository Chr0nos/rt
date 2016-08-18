/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:33:02 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/17 10:40:34 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static void init_ttf(void)
{
	if (TTF_Init() == -1)
	{
		ft_printf("Erreur initialisation TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	else
		ft_putstr("TTF_Init : okay.\n");
}

static void init_str_data(char *interface[NB_CHAMPS][LARGER_SIZE])
{
	*interface[0] = ft_strdup("Id ................... :");
	*interface[1] = ft_strdup("Name ........... :");
	*interface[2] = ft_strdup("Type .............. :");
	*interface[3] = ft_strdup("pos.X ............. :");
	*interface[4] = ft_strdup("pos.Y .............. :");
	*interface[5] = ft_strdup("pos.Z ............. :");
	*interface[6] = ft_strdup("dir.X ............... :");
	*interface[7] = ft_strdup("dir.Y ................ :");
	*interface[8] = ft_strdup("dir.Z ............... :");
	*interface[9] = ft_strdup("color.R ............ :");
	*interface[10] = ft_strdup("color.G ........... :");
	*interface[11] = ft_strdup("color.B ........... :");
	*interface[12] = ft_strdup("transparence :");
	*interface[13] = ft_strdup("reflection (%) :");
	*interface[14] = ft_strdup("refraction (%) :");
	*interface[15] = ft_strdup("size ................ :");
}

static void init_font(t_interf *interf)
{
	define_color(&interf->color_classic, 255, 255, 255);
	define_color(&interf->color_selected, 210, 255, 50);
	interf->font_size = 26;
	interf->police_classic = define_police(interf->police_classic,
		"interface/font/angelina.ttf", interf->font_size, 0);
	interf->police_selected = define_police(interf->police_selected,
		"interface/font/angelina.ttf", interf->font_size, 1);
	interf->pos.x = 10;
	interf->pos.y = 10;
	interf->id_selected = 3; //tmp
}

void init_surface_data(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color)
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS)
	{
		surface[i] = define_texte(police, *champs[i], color);
	}
}

void init_interface(t_rt *rt)
{
	init_ttf();
	init_str_data(rt->interf->champs_txt);
	init_font(rt->interf);
	init_surface_data(rt->interf->champs_txt, rt->interf->surface_txt,
		rt->interf->police_classic, &rt->interf->color_classic);
	free_champs(rt->interf->champs_txt);
}
