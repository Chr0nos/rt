/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:42:24 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/29 17:01:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"

void	clean_interface(t_rt *rt)
{
//	free_champs(rt->interf->champs_obj);
	ft_freesplit(*rt->interf->champs_obj);
	free_surfaces(rt->interf->surface_txt);
	TTF_CloseFont(rt->interf->police_classic);
	TTF_CloseFont(rt->interf->police_selected);
	TTF_Quit();
	ft_putstr("TTF_quit ...\n");
}

//ft_free_tab((char**)(unsigned long)champs, sizeof(*champs));
//penser a metre un NULL a la fin de champs

void	free_surfaces(SDL_Surface *surface[NB_CHAMPS])
{
	int		i;

	i = -1;
	while (++i != I_END)
		free(surface[i]);
}
