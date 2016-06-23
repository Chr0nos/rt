/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:16:20 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/23 14:31:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTRE_H
# define FILTRE_H

typedef unsigned int    t_uint;

typedef struct	s_filter_cfg
{
	int			bit;
	t_uint		(*filter)(t_uint);
}				t_filter_cfg;

t_uint          filtre(int keyboard, t_uint color);
t_uint          filtre_red(t_uint color);
t_uint          filtre_green(t_uint color);
t_uint          filtre_blue(t_uint color);

#endif
