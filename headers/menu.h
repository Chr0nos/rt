/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:39:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/14 07:23:41 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# include "libft.h"
# include "rt.h"
# include <SDL2/SDL.h>
# define MENU_PADDING_X 10
# define MENU_PADDING_Y 12
# define MENU_BORDER_X 12
# define MENU_BORDER_Y 12

int				menu_init(t_rt *rt, const char *path);
void			menu_display(t_rt *rt);
void			menu_move(t_rt *rt);
void			menu_kb_copy(t_rt *rt);
int				menu_camera_reset(t_rt *rt);
int				menu_camera_save(t_rt *rt);
void			menu_update_positions(t_rt *rt);
int				menu_position_id(t_rt *rt, int x, int y);
void			menu_clean(t_rt *rt, int keep_id);
t_list			*ls_dir(const char *path, const char **masks, int mc);
int				ls_isdir(const char *path);
void			menu_degrade(SDL_Surface *surface,
	const unsigned int scolor, const unsigned int ecolor);
void			menu_background_init(t_rt *rt);
size_t			menu_configure_rts(t_rt *rt, t_list *files);
void			menu_configure_thumbs_size(t_rt *rt);

#endif
