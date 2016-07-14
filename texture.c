/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 20:46:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 19:45:56 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "draw.h"
#include "libft.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

unsigned int		texture_color_convert(unsigned int color)
{
	return (((color & 0xff0000) >> 16) |
		((color & 0x000000ff) << 16) |
		(color & 0xff00ff00));
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
	while (tex)
	{
		if (!ft_strcmp(tex->filepath, filepath))
			return (tex);
		tex = tex->next;
	}
	return (NULL);
}

static t_texture	*texture_create_set(t_texture *tex, char *filepath,
	SDL_Surface *std_surface, t_texture **lst)
{
	tex->filepath = filepath;
	tex->surface = std_surface;
	tex->next = *lst;
	texture_convertformat(tex);
	*lst = tex;
	return (tex);
}

t_texture			*texture_create(t_texture **lst, char *filepath)
{
	t_texture		*tex;
	SDL_Surface		*surface;
	SDL_Surface		*std_surface;

	if (!(surface = IMG_Load(filepath)))
	{
		ft_putendl_fd("holly shit", 2);
		ft_putendl_fd(IMG_GetError(), 2);
		return (NULL);
	}
	if (!(std_surface = draw_make_surface((t_point){surface->w, surface->h})))
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	draw_pixelsconvert(std_surface->pixels, surface->pixels,
		surface->format->BytesPerPixel,
		(size_t)(surface->pitch * surface->h) / surface->format->BytesPerPixel);
	SDL_FreeSurface(surface);
	if (!(tex = malloc(sizeof(t_texture))))
	{
		SDL_FreeSurface(std_surface);
		return (NULL);
	}
	return (texture_create_set(tex, filepath, std_surface, lst));
}
