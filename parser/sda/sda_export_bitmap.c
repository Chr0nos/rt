/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_bitmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:36:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/18 21:51:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <SDL2/SDL.h>

static void	sda_bmp_dump(unsigned char *dest, SDL_Surface *surface)
{
	const unsigned int	end = (unsigned int)(surface->w * surface->h);
	unsigned int		color;
	unsigned int		p;

	p = 0;
	while (p < end)
	{
		color = ((unsigned int*)surface->pixels)[p];
		dest[0] = (unsigned char)((color & 0xff0000) >> 16);
		dest[1] = (unsigned char)((color & 0x00ff00) >> 8);
		dest[2] = (unsigned char)(color & 0x0000ff);
		dest += 3;
		p++;
	}
}

static void	sda_export_bitmap_init(t_sda_bitmap_header *header,
	SDL_Surface *surface, const unsigned int fullsize)
{
	header->img_size = (unsigned int)(surface->w * surface->h) * 3;
	//header->magic = 0x424d;
	header->magic = 0x4d42;
	header->filesize = fullsize;
	header->data_start = 10;
	header->plans = 1;
	header->img_head_size = 0x28;
	header->w = (unsigned int)surface->w;
	header->h = (unsigned int)surface->h;
	header->bpp = 24;
	header->compression = 0;
	header->palette_colors = 0;
	header->palette_important = 0;
	header->x = header->h;
	header->y = header->w;
}

char	*sda_export_bitmap(SDL_Surface *surface)
{
	char					*data;
	t_sda_bitmap_header		*header;
	unsigned int			fullsize;
	unsigned int			img_size;

	if (!surface)
		return (NULL);
	img_size = (unsigned int)(surface->w * surface->h) * 3;
	fullsize = sizeof(t_sda_bitmap_header) + img_size;
	data = malloc(fullsize);
	if (!data)
		return (NULL);
	header = (t_sda_bitmap_header*)(unsigned long)data;
	sda_export_bitmap_init(header, surface, fullsize);
	ft_printf("x: %d y: %d s: %d\n",
		(int)header->x, (int)header->w,
		(int)header->filesize);
	sda_bmp_dump((unsigned char*)&data[header->data_start], surface);
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
