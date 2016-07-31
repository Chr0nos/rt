/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 20:46:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/31 14:36:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "draw.h"
#include "libft.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

unsigned int		texture_color_convert(unsigned int color)
{
	const unsigned int		alpha = 0xFF - ((color & 0xff000000) >> 24);

	return (((color & 0xff0000) >> 16) |
		((color & 0x0000ff) << 16) |
		(color & 0x00ff00) | (alpha << (24)));
}

void				texture_convertformat(t_texture *tex)
{
	size_t			size;
	unsigned int	*pixels;

	pixels = tex->surface->pixels;
	size = (size_t)(tex->surface->w * tex->surface->h);
	while (size--)
		pixels[size] = texture_color_convert(pixels[size]);
}

t_texture			*texture_search(t_texture *tex,
	const char *filepath)
{
	if (!ft_strncmp(filepath, "perlin:", 7))
		return (NULL);
	while (tex)
	{
		if (!ft_strcmp(tex->filepath, filepath))
			return (tex);
		tex = tex->next;
	}
	return (NULL);
}
