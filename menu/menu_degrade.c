/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_degrade.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 18:16:13 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/26 18:16:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "libft.h"

void		menu_degrade(SDL_Surface *surface,
	const unsigned int scolor, const unsigned int ecolor)
{
	int				line;
	int				col;
	float			pc;
	unsigned int	*pixels;

	col = surface->w;
	while (col--)
	{
		pc = (float)col / (float)surface->w;
		((unsigned int *)surface->pixels)[col] = draw_color_lerp(scolor, ecolor,
			pc);
	}
	line = surface->h;
	while (line-- > 1)
	{
		pixels = &((unsigned int *)surface->pixels)[line * surface->w];
		ft_memcpy(pixels, surface->pixels,
			(size_t)surface->w * sizeof(unsigned int));
	}
}
