/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_perlin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 14:25:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/12 14:27:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "draw.h"
#include "libft.h"
#include <stdlib.h>

t_texture	*texture_perlin(t_texture **lst, t_v2i size)
{
	t_texture	*tex;

	if (!(tex = malloc(sizeof(t_texture))))
		return (NULL);
	if (!(tex->filepath = ft_strdup("perlin")))
	{
		free(tex);
		return (NULL);
	}
	if (!(tex->surface = draw_make_surface(size)))
	{
		free(tex->filepath);
		free(tex);
		return (NULL);
	}
	draw_perlin(tex->surface);
	tex->next = *lst;
	tex->prev = NULL;
	if (tex->next)
		tex->next->prev = tex;
	*lst = tex;
	return (tex);
}
