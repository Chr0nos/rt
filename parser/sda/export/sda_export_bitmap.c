/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_bitmap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:36:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:58:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#define BMP_HEADER_SIZE 0x7a

static void	sda_bmp_dump(unsigned char *dest, SDL_Surface *surface)
{
	unsigned int		color;
	t_point				px;

	px.y = surface->h;
	while (px.y--)
	{
		px.x = 0;
		while (px.x < surface->w)
		{
			color = ((unsigned int*)surface->pixels)[px.y * surface->w + px.x];
			dest[2] = (unsigned char)((color & 0xff0000) >> 16);
			dest[1] = (unsigned char)((color & 0x00ff00) >> 8);
			dest[0] = (unsigned char)(color & 0x0000ff);
			dest += 3;
			px.x++;
		}
	}
}

/*
** DONT TOUCH: it's magic.... dark magic seriously
** you have no idea how wrong the bitmap format is...
*/

static void	sda_export_bitmap_init(void *bitmap,
	SDL_Surface *surface, const unsigned int fullsize)
{
	unsigned long		data;

	(void)surface;
	data = (unsigned long)bitmap;
	ft_memset((void*)data, 0, BMP_HEADER_SIZE);
	*(unsigned short*)data = (unsigned short)0x4d42;
	*(unsigned int*)(data + 2) = (fullsize);
	*(unsigned int *)(data + 6) = 0u;
	*(unsigned char *)(data + 10) = BMP_HEADER_SIZE;
	*(unsigned int *)(data + 14) = BMP_HEADER_SIZE - 14;
	*(int*)(data + 18) = surface->w;
	*(int*)(data + 22) = surface->h;
	*(unsigned short*)(data + 26) = 1;
	*(unsigned short*)(data + 28) = 24;
	*(unsigned int*)(data + 30) = 0;
	*(unsigned int*)(data + 34) = (unsigned int)(surface->w * surface->h) * 3;
	*(int*)(data + 38) = 0x0b13;
	*(int*)(data + 42) = 0x0b13;
	*(unsigned long *)(data + 46) = 0;
	*(unsigned int *)(data + 54) = *(const unsigned int *)(unsigned long)"BGRs";
	((unsigned char *)(data))[0x6a] = 2;
}

char		*sda_export_bitmap(SDL_Surface *surface, unsigned int *size)
{
	char					*data;
	unsigned int			fullsize;
	unsigned int			img_size;

	ft_putendl("exporting bitmap");
	if (!surface)
		return (NULL);
	img_size = (unsigned int)(surface->w * surface->h) * 3;
	fullsize = BMP_HEADER_SIZE + img_size;
	*size = fullsize;
	ft_putendl("allocating memory");
	data = malloc(fullsize);
	if (!data)
		return (NULL);
	ft_putendl("creating header...");
	sda_export_bitmap_init(data, surface, fullsize);
	ft_putendl("dumping image");
	sda_bmp_dump((unsigned char*)&data[BMP_HEADER_SIZE], surface);
	ft_putendl("returning");
	return (data);
}

int			sda_export_bitmap_file(const char *filepath, SDL_Surface *surface)
{
	int				fd;
	char			*bitmap;
	unsigned int	size;

	bitmap = sda_export_bitmap(surface, &size);
	if ((fd = open(filepath, O_CREAT | O_TRUNC | O_RDWR)) <= 0)
	{
		free(bitmap);
		return (-1);
	}
	if (!bitmap)
	{
		close(fd);
		return (-2);
	}
	ft_printf("size: %d\n", size);
	write(fd, bitmap, size);
	close(fd);
	chmod(filepath, 0644);
	free(bitmap);
	ft_putendl("done");
	return (1);
}
