/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_fill_surface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 16:25:23 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/30 21:13:35 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void		fill_surfaces(char *champs[NB_CHAMPS][LARGER_SIZE],
		SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color)
{
	int	i;

	i = -1;
	while (++i != I_END)
	{
		if (i != I_VIDE2 && i != I_VIDE3 && i != I_VIDE4 && i != I_VIDE5
			&& i != I_VIDE6 && i != I_VIDE7 && i != I_VIDE8)
			surface[i] = define_texte(police, *champs[i], color);
	}
	surface[I_END] = NULL;
}

void		fill_surface_scale(t_interf *in, int i_scale)
{
	int	i;

	i = -1;
	while (in->champs_scale[++i])
	{
		if (i == i_scale)
			in->surface_scale[i] = define_texte(in->police_classic,
				in->champs_scale[i], &(SDL_Color){0, 255, 115, 25});
		else
			in->surface_scale[i] = define_texte(in->police_classic,
				in->champs_scale[i], &in->color_selected);
	}
	in->surface_scale[i] = NULL;
}
