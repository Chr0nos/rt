/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:42:16 by dboudy            #+#    #+#             */
/*   Updated: 2016/07/13 17:51:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include <SDL2/SDL.h>

typedef struct			s_texture
{
	struct s_texture	*next;
	SDL_Surface			*texture;
	unsigned int		*pixels;
}						t_texture;

#endif
