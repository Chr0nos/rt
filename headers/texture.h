/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 11:42:16 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/09 03:38:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include "draw.h"
# include "libft.h"
# include <SDL2/SDL_ttf.h>

typedef struct s_obj	t_obj;
typedef struct			s_texture
{
	struct s_texture	*next;
	struct s_texture	*prev;
	SDL_Surface			*surface;
	char				*filepath;
}						t_texture;

unsigned int			texture_color_convert(unsigned int color);
void					texture_convertformat(t_texture *tex);
t_texture				*texture_search(t_texture *tex, const char *filepath);
t_texture				*texture_create(t_texture **lst, char *filepath);
void					textures_free(t_texture *t);
void					textures_freetex(t_texture *t);
t_texture				*texture_perlin(t_texture **lst, t_v2i size, char *str);
t_list					*textures_used(t_obj *root);
void					textures_used_display(t_obj *root);
t_texture				*texture_last(t_texture *lst);
void					textures_cleanup(t_obj *node, t_texture **lst);
t_texture				*texture_remove(t_texture *tex, t_texture **root);
void					textures_display(t_texture *t);
char					*texture_cleanpath(char *filepath);

#endif
