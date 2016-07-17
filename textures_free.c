/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 21:48:23 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 14:14:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "SDL2/SDL.h"
#include <stdlib.h>

void	textures_free(t_texture *t)
{
	if (!t)
		return ;
	if (t->next)
		textures_free(t->next);
	SDL_FreeSurface(t->surface);
	free(t->filepath);
	free(t);
}
