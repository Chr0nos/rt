/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/31 14:29:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 08:57:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "draw.h"
#include "libft.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

char					*texture_cleanpath(char *filepath)
{
	int		p;

	p = 0;
	while (!ft_strncmp(&filepath[p], "./", 2))
		p += 2;
	return (ft_memmove(filepath, &filepath[p], ft_strlen(&filepath[p])));
}

static t_texture		*texture_create_set(t_texture *tex, char *filepath,
	SDL_Surface *std_surface, t_texture **lst)
{
	tex->filepath = filepath;
	ft_printf("#loaded texture: %s\n", tex->filepath);
	tex->surface = std_surface;
	tex->next = *lst;
	tex->prev = NULL;
	if (tex->next)
		tex->next->prev = tex;
	texture_convertformat(tex);
	*lst = tex;
	return (tex);
}

/*
** std_surface will contain the converted surface format to 4 bpp
** surface only contain the raw format (wich can be any bpp)
*/

static t_texture		*texture_create_file(t_texture **lst, char *filepath)
{
	t_texture		*tex;
	SDL_Surface		*surface;
	SDL_Surface		*std_surface;

	if (!(surface = IMG_Load(filepath)))
	{
		ft_putendl_fd(IMG_GetError(), 2);
		return (NULL);
	}
	if (!(std_surface = draw_make_surface((t_v2i){surface->w, surface->h})))
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	draw_pixelsconvert(std_surface->pixels, surface->pixels,
		surface->format->BytesPerPixel, (size_t)(surface->w * surface->h));
	SDL_FreeSurface(surface);
	if (!(tex = malloc(sizeof(t_texture))))
	{
		SDL_FreeSurface(std_surface);
		return (NULL);
	}
	return (texture_create_set(tex,
		texture_cleanpath(filepath), std_surface, lst));
}

t_texture				*texture_create(t_texture **lst, char *filepath)
{
	t_v2i			noise_size;
	size_t			tab_size;
	char			**tab;

	if (ft_strncmp(filepath, "perlin:", 7))
		return (texture_create_file(lst, filepath));
	tab = ft_strsplit(filepath, ' ');
	tab_size = ft_tabcount((void**)tab);
	if (tab_size >= 3)
		noise_size = (t_v2i){ft_atoi(tab[1]), ft_atoi(tab[2])};
	else
		noise_size = (t_v2i){200, 200};
	ft_freesplit(tab);
	return (texture_perlin(lst, noise_size, filepath));
}
