/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 10:35:39 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/13 15:17:44 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYL_H
# define CYL_H

typedef struct	s_cyl_inter
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		sol1;
	double		sol2;
}				t_cyl_inter;

#endif
