/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:42:16 by dboudy            #+#    #+#             */
/*   Updated: 2016/07/13 20:49:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include <SDL2/SDL.h>

typedef struct			s_texture
{
	struct s_texture	*next;
	SDL_Surface			*surface;
	char				*filepath;
}						t_texture;

unsigned int			texture_color_convert(unsigned int color);
void					texture_convertformat(t_texture *tex);
t_texture				*texture_search(t_texture *tex, const char *filepath);
t_texture				*texture_create(t_texture **lst, char *filepath);

#endif
