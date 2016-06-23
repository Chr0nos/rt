/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:16:20 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/23 11:57:11 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTRE_H
# define FILTRE_H

typedef unsigned int    t_uint;

t_uint          filtre(t_uint color, int rt_filtre);
t_uint          filtre_red(t_uint color);
t_uint          filtre_green(t_uint color);
t_uint          filtre_blue(t_uint color);

#endif
