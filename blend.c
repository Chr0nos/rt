/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:44:55 by alhote            #+#    #+#             */
/*   Updated: 2016/08/25 04:18:59 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

unsigned int		to_rgb(unsigned int a, unsigned int r,
				unsigned int g, unsigned int b)
{
	return ((((a > 0xff) ? 0xff : a) << 24) |
		(((r > 0xff) ? 0xff : r) << 16) |
		(((g > 0xff) ? 0xff : g) << 8) |
		((b > 0xff) ? 0xff : b));
}

unsigned int		blend_normal(unsigned int a, unsigned int b)
{
	if (!A(a))
		return (a);
	else
		return (blend_add(
			blend_multiply(to_rgb(A(a), A(a), A(a), A(a)), b), a));
}

unsigned int		blend_overlay(unsigned int a, unsigned int b)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = ((R(b) < 128) ? (2 * R(a) * R(b) / 255) : (255 - 2 * (255 - R(a))
	* (255 - R(b)) / 255));
	green = ((G(b) < 128) ? (2 * G(a) * G(b) / 255) : (255 - 2 * (255 - G(a))
	* (255 - G(b)) / 255));
	blue = ((B(b) < 128) ? (2 * B(a) * B(b) / 255) : (255 - 2 * (255 - B(a))
	* (255 - B(b)) / 255));
	return (to_rgb(0, red, green, blue));
}

unsigned int		blend_lighten(unsigned int a, unsigned int b)
{
	const unsigned int	red = (R(a) > R(b) ? R(a) : R(b));
	const unsigned int	green = (G(a) > G(b) ? G(a) : G(b));
	const unsigned int	blue = (B(a) > B(b) ? B(a) : B(b));
	const unsigned int	alpha = (A(a) > A(b)) ? A(a) : A(b);

	return (to_rgb(alpha, red, green, blue));
}

unsigned int		blend_darken(unsigned int a, unsigned int b)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	red = (R(a) < R(b) ? R(a) : R(b));
	green = (G(a) < G(b) ? G(a) : G(b));
	blue = (B(a) < B(b) ? B(a) : B(b));
	alpha = (A(a) < A(b)) ? A(a) : A(b);
	return (to_rgb(alpha, red, green, blue));
}

unsigned int		blend_add(unsigned int a, unsigned int b)
{
	const unsigned int	red = R(a) + R(b);
	const unsigned int	green = G(a) + G(b);
	const unsigned int	blue = B(a) + B(b);
	const unsigned int	alpha = A(a) + A(b);

	return (to_rgb(alpha, red, green, blue));
}

unsigned int		blend_sub(unsigned int a, unsigned int b)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	red = R(a) - R(b);
	green = G(a) - G(b);
	blue = B(a) - B(b);
	alpha = A(a) - A(b);
	return (to_rgb(alpha, red, green, blue));
}
unsigned int		blend_multiply(unsigned int a, unsigned int b)
{
	const unsigned int	red = (R(a) * R(b)) / 255;
	const unsigned int	green = (G(a) * G(b)) / 255;
	const unsigned int	blue = (B(a) * B(b)) / 255;
	const unsigned int	alpha = (A(a) * A(b)) / 255;

	return (to_rgb(alpha, red, green, blue));
}
