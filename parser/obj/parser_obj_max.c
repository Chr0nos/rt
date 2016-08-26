/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_max.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 21:29:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 21:29:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"

unsigned int			obj_max(int x, const unsigned int max)
{
	if (x < 1)
		return (1);
	return ((unsigned int)x > max) ? max : (unsigned int)x;
}
