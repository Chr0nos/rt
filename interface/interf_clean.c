/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:42:24 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/19 01:45:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void clean_interface(t_rt *rt)
{
	free_champs(rt->interf->champs_obj);
	free_surfaces(rt->interf->surface_txt);
	TTF_CloseFont(rt->interf->police_classic);
	TTF_CloseFont(rt->interf->police_selected);
	TTF_Quit();
	ft_putstr("TTF_quit ...\n");
}

//ft_free_tab((void**)(unsigned long)champs)
//penser a metre un NULL a la fin de champs

void free_old_data_obj(t_obj *obj)
{
	if (obj->name)
		free(obj->name);
	if (((t_cube*)obj->content)->texture)
		free(((t_cube*)obj->content)->texture);
}

void free_champs(char *champs[NB_CHAMPS][LARGER_SIZE])
{
	int		i;

	i = -1;
	while (*champs[i])
		free (*champs[i]);
}

void free_surfaces(SDL_Surface *surface[NB_CHAMPS])
{
	int		i;

	i = -1;
	while (surface[i])
		free (surface[i]);
}
