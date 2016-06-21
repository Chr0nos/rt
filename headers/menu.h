/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 13:39:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 17:16:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# include "libft.h"
# include "rt.h"

int			menu_init(t_rt *rt);
void		menu_display(t_rt *rt);
t_list		*ls_dir(const char *path, const char *mask);

#endif
