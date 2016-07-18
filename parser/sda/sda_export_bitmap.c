/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_bitmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:36:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/18 18:25:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include <SDL2/SDL.h>

char	*sda_export_bitmap(SDL_Surface *surface)
{
	char					*data;
	char					*image;
	t_sda_bitmap_header		header;
	unsigned int			img_size;

	if (!surface)
		return (NULL);
	img_size = (unsigned int)(surface->pitch * surface->h);
	header.magic = 0;
	header.filesize = img_size;
	header.data_start = sizeof(t_sda_bitmap_header);
	data = malloc(sizeof(t_sda_bitmap_header) + (header.filesize));
	if (!data)
		return (NULL);
	image = &data[header.data_start];
	ft_memcpy(data, &header, sizeof(t_sda_bitmap_header));
	ft_memcpy(image, surface->pixels, img_size);
	return (data);
}
