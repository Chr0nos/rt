/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:39:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/22 15:18:23 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# include "libft.h"
# include "rt.h"
# define MENU_ITEMS_X 3
# define MENU_PADDING_X 10
# define MENU_PADDING_Y 12
# define MENU_BORDER_X 12
# define MENU_BORDER_Y 12

int			menu_init(t_rt *rt, const char *path);
void		menu_display(t_rt *rt);
void		menu_move(t_rt *rt);
void		menu_kb_copy(t_rt *rt);
int			menu_camera_reset(t_rt *rt);
t_list		*ls_dir(const char *path, const char *mask);
int			ls_isdir(const char *path);

#endif
