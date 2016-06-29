/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putbits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 22:10:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 22:11:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>

void		rt_putbits(unsigned int bits)
{
	unsigned char	p;
	char			buffer[33];

	buffer[32] = ' ';
	p = 32;
	while (p--)
		buffer[p] = (bits & 1u << (31 - p)) ? '1' : '0';
	write(1, buffer, 33);
}
