/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:39:08 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/30 19:58:36 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

/// @brief prints Error\n thetn some error details
/// @param custom_error set to NULL if you willing to print error msg depending
///	on errno, or set the error msg string to be printed
/// @param file_name the fiel causing the error if it's called after an open()
/// if not just set it to NULL
void	error_(char *custom_error, char *file_name)
{
	char	*err_string;

	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (file_name)
	{
		ft_putstr_fd(file_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (!custom_error)
		err_string = strerror(errno);
	else
		err_string = custom_error;
	ft_putstr_fd(err_string, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(errno);
}

void	free_2d_array(char **var)
{
	int	i;

	i = -1;
	while (var[++i])
		free(var[i]);
	free(var);
}

// to be moved later 
int	check_texture_file(char **type_id)
{
	int		fd;

	fd = open(type_id[1], O_RDONLY);
	if (fd < 3)
	{
		if (!type_id[1])
			error_("No texture file specified", type_id[0]);
		error_(NULL, type_id[1]);
	}
	return (1);
}
