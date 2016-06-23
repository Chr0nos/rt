/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:12:46 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/23 11:59:25 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filtre.h"
#include "rt.h"
#include "keyboard.h"

t_uint		filtre(t_uint c, int rt_filtre)
{
	if (rt_filtre == ONE)
		return (filtre_red(c));
	else if (rt_filtre == TWO)
		return (filtre_green(c));
	else if (rt_filtre == THREE)
		return (filtre_blue(c));
	else
		return (c);
}
