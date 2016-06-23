/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:16:20 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/23 16:33:36 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H

typedef unsigned int    t_uint;

typedef struct	s_filter_cfg
{
	int			bit;
	t_uint		(*filter)(t_uint);
}				t_filter_cfg;

t_uint          filter(int keyboard, t_uint color);
t_uint          filter_red(t_uint color);
t_uint          filter_green(t_uint color);
t_uint          filter_blue(t_uint color);
t_uint          filter_magenta(t_uint color);
t_uint          filter_yellow(t_uint color);
t_uint          filter_cyan(t_uint color);

#endif
