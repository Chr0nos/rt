/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 20:46:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 05:58:58 by edelangh         ###   ########.fr       */
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
	char	*real_path;

	if (!ft_strncmp(filepath, "perlin:", 7))
		return (NULL);
	real_path = texture_cleanpath(ft_strdup(filepath));
	while (tex)
	{
		if (!ft_strcmp(tex->filepath, real_path))
		{
			ft_printf("#skipping load of %s\n", real_path);
			free(real_path);
			return (tex);
		}
		tex = tex->next;
	}
	free(real_path);
	return (NULL);
}
