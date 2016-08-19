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


/*
 ** Le moment venu penser a :
 ** add TTF_CLoseFont(police);
 ** add TTF_Quit;
*/

//ft_free_tab((void**)(unsigned long)champs)
//penser a metre un NULL a la fin de champs

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
