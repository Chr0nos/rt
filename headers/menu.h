/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:39:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 22:23:31 by snicolet         ###   ########.fr       */
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

int			menu_init(t_rt *rt);
void		menu_display(t_rt *rt);
void		menu_move(t_rt *rt);
void		menu_kb_copy(t_rt *rt);
t_list		*ls_dir(const char *path, const char *mask);

#endif
