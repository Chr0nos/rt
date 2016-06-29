/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:44:55 by alhote            #+#    #+#             */
/*   Updated: 2016/06/29 22:44:56 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

unsigned int		blend_add(unsigned int a, unsigned int b)
{
	unsigned int result;

	result = ((((a & 0xFF0000) >> 16) + ((b & 0xFF0000) >> 16)) << 16) +
			((((a & 0x00FF00) >> 8) + ((b & 0x00FF00) >> 8)) << 8) +
			((((a & 0x0000FF)) + ((b & 0x0000FF))));
	return ((result > 0xFFFFFF ? 0xFFFFFF : result));
}

unsigned int		blend_multiply(unsigned int a, unsigned int b)
{
	unsigned int result;

	result = (((((a & 0xFF0000) >> 16) * ((b & 0xFF0000) >> 16)) / 255) << 16) +
			(((((a & 0x00FF00) >> 8) * ((b & 0x00FF00) >> 8)) / 255) << 8) +
			((((a & 0x0000FF)) * ((b & 0x0000FF))) / 255);
	return ((result > 0xFFFFFF ? 0xFFFFFF : result));
}
