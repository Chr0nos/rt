/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_bitmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:36:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/18 19:28:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <SDL2/SDL.h>

char	*sda_export_bitmap(SDL_Surface *surface)
{
	char					*data;
	char					*image;
	t_sda_bitmap_header		header;
	unsigned int			fullsize;

	if (!surface)
		return (NULL);
	header.img_size = (unsigned int)(surface->w * surface->h) * 4;
	fullsize = sizeof(t_sda_bitmap_header) + (header.img_size);
	header.magic = 0x424d;
	header.filesize = fullsize;
	header.data_start = 14;
	header.plans = 1;
	header.img_head_size = 28;
	header.w = (unsigned int)surface->w;
	header.h = (unsigned int)surface->h;
	header.bpp = 24;
	header.compression = 0;
	header.palette_colors = 0;
	header.palette_important = 0;
	header.x = header.h;
	header.y = header.w;
	data = malloc(fullsize);
	if (!data)
		return (NULL);
	image = &data[header.data_start];
	ft_printf("x: %d y: %d s: %d\n",
		(unsigned int)header.x, (unsigned int)header.w,
		(unsigned int)header.filesize);
	ft_memcpy(data, &header, sizeof(t_sda_bitmap_header));
	//ft_memset(image, 0, header.img_size);
	ft_memcpy(image, surface->pixels, header.img_size);
	return (data);
}

int		sda_export_bitmap_file(const char *filepath, SDL_Surface *surface)
{
	int				fd;
	char			*bitmap;

	if (!(fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC)))
		return (-1);
	bitmap = sda_export_bitmap(surface);
	if (!bitmap)
	{
		close(fd);
		return (-2);
	}
	write(fd, bitmap, ((t_sda_bitmap_header*)(unsigned long)bitmap)->filesize);
	close(fd);
	free(bitmap);
	return (1);
}
