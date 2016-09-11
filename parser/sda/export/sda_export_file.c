/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 14:18:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:57:54 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"
#include <fcntl.h>
#include <sys/stat.h>

static int		sda_export_fileexists(const char *filepath)
{
	struct stat		st;

	if (stat(filepath, &st) < 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (2);
	return (1);
}

int				sda_export_file(const char *filepath)
{
	int				fd;
	const int		exists = sda_export_fileexists(filepath);

	if (exists)
	{
		ft_putstr_fd("error: file exists\n", 2);
		return (-1);
	}
	fd = open(filepath, O_CREAT | O_TRUNC | O_WRONLY);
	return (fd);
}
