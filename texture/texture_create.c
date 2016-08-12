/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/31 14:29:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/12 14:23:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "draw.h"
#include "libft.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static t_texture	*texture_create_set(t_texture *tex, char *filepath,
	SDL_Surface *std_surface, t_texture **lst)
{
	ft_printf("loaded texture: %s\n", filepath);
	tex->filepath = filepath;
	tex->surface = std_surface;
	tex->next = *lst;
	tex->prev = NULL;
	if (tex->next)
		tex->next->prev = tex;
	texture_convertformat(tex);
	(void)texture_convertformat;
	*lst = tex;
	return (tex);
}

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

t_texture			*texture_create(t_texture **lst, char *filepath)
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
	ft_free_tab(tab, tab_size);
	free(tab);
	return (texture_perlin(lst, noise_size));
}
