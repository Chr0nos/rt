/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:42:24 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/30 19:35:45 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"

void	clean_interface(t_rt *rt)
{
	ft_freesplit(*rt->interf->champs_obj);
	ft_freesplit(rt->interf->champs_scale);
	free_surfaces(rt->interf->surface_txt);
	free_surfaces(rt->interf->surface_scale);
	TTF_CloseFont(rt->interf->police_classic);
	TTF_CloseFont(rt->interf->police_selected);
	TTF_Quit();
	ft_putstr("TTF_quit ...\n");
}

void	free_surfaces(SDL_Surface *surface[NB_CHAMPS])
{
	int		i;

	i = -1;
	while (surface[++i])
		SDL_FreeSurface(surface[i]);
}
