/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_isdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 23:46:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 19:30:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include <sys/stat.h>

int		ls_isdir(const char *path)
{
	struct stat		st;

	if (lstat(path, &st) < 0)
		return (-1);
	if (st.st_mode & S_IFDIR)
		return (1);
	return (0);
}
