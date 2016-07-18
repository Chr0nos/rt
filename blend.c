/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:44:55 by alhote            #+#    #+#             */
/*   Updated: 2016/07/18 13:07:40 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

unsigned int		to_rgb(unsigned int a, unsigned int r,
				unsigned int g, unsigned int b)
{
	a = (a > 255 ? 255 : a);
	r = (r > 255 ? 255 : r);
	g = (g > 255 ? 255 : g);
	b = (b > 255 ? 255 : b);
	return ((a << 24) | (r << 16) | (g << 8) | (b));
}

unsigned int		blend_normal(unsigned int a, unsigned int b)
{
	(void)b;
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
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	red = (R(a) > R(b) ? R(a) : R(b));
	green = (G(a) > G(b) ? G(a) : G(b));
	blue = (B(a) > B(b) ? B(a) : B(b));
	alpha = (A(a) > A(b)) ? A(a) : A(b);
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
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	red = R(a) + R(b);
	green = G(a) + G(b);
	blue = B(a) + B(b);
	alpha = A(a) + A(b);
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
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	red = (R(a) * R(b)) / 255;
	green = (G(a) * G(b)) / 255;
	blue = (B(a) * B(b)) / 255;
	alpha = (A(a) * A(b)) / 255;
	return (to_rgb(alpha, red, green, blue));
}
