/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:42:24 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/17 10:42:27 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"


/*
 ** Le moment venu penser a :
 ** add TTF_CLoseFont(police);
 ** add TTF_Quit;
*/

void free_champs(char *champs[NB_CHAMPS][LARGER_SIZE])
{
	int		i;

	i = -1;
	while (++i < NB_CHAMPS)
		free (*(champs[i]));
}

void free_surfaces(SDL_Surface *surface[NB_CHAMPS])
{
	int		i;

	i = -1;
	while (++i < NB_CHAMPS)
		free (surface[i]);
}
