/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 18:02:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 19:11:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "texture.h"
#include "libft.h"
#include "draw.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static unsigned int	texture_color_convert(unsigned int color)
{
	//return (color);
	return (((color & 0xff0000) >> 16) |
		((color & 0x000000ff) << 16) |
		(color & 0xff00ff00));
}

static void			sda_setup_texture_convertformat(t_texture *tex)
{
	size_t			size;
	unsigned int	*pixels;

	pixels = tex->surface->pixels;
	size = (size_t)(tex->surface->w * tex->surface->h);
	while (size--)
		pixels[size] = texture_color_convert(pixels[size]);
}

static t_texture	*texture_search(t_texture *tex,
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

static t_texture	*texture_create(t_texture **lst, char *filepath)
{
	t_texture		*tex;
	SDL_Surface		*surface;

	if (!(surface = IMG_Load(filepath)))
	{
		free(filepath);
		return (NULL);
	}
	tex = malloc(sizeof(t_texture));
	tex->filepath = filepath;
	tex->surface = surface;
	tex->next = *lst;
	*lst = tex;
	return (tex);
}

int					sda_setup_texture(t_sda *e, t_obj *obj, char **av)
{
	t_texture	*tex;
	char		*filepath;
	int			ret;

	(void)sda_setup_texture_convertformat;
	ret = 0;
	filepath = ft_strunsplit((const char **)(unsigned long)av, ' ');
	if ((tex = texture_search(e->rt->textures, filepath)))
		ret = 1;
	else if ((tex = texture_create(&e->rt->textures, filepath)))
		ret = 1;
	else
	{
		ft_putendl_fd("error: failed to load texture", 2);
		ret = -1;
	}
	((t_sphere*)obj->content)->texture = tex;
	return (ret);
}
