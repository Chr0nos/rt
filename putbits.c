/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putbits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 22:10:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 19:14:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>

void		rt_putbits(size_t bits)
{
	unsigned char	p;
	char			buffer[65];

	buffer[64] = ' ';
	p = 64;
	while (p--)
		buffer[p] = (bits & 1u << (63 - p)) ? '1' : '0';
	write(1, buffer, 65);
}
