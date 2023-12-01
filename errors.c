/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:39:08 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/01 23:06:43 by mbousbaa         ###   ########.fr       */
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
	int	fd;
	int	i;

	i = 0;
	while (type_id[i])
		i++;
	if (i > 2 || ft_strchr(type_id[1], '\t') != NULL)
		error_("Texture not valid, check if you have any extra tabs", NULL);
	if (type_id[1] && ft_strncmp(strrchr(type_id[1], '.'), ".png", 5) != 0)
		error_("Not a valid file", type_id[1]);
	fd = open(type_id[1], O_RDONLY);
	if (fd < 3)
	{
		if (!type_id[1])
			error_("No texture file specified", type_id[0]);
		error_(NULL, type_id[1]);
	}
	close(fd);
	return (1);
}

void	check_color_range(char *color)
{
	char	**tmp;
	int		i;

	tmp = ft_split(color, ',');
	i = -1;
	while (tmp[++i])
	{
		if (ft_atoi(tmp[i]) > 255 || i > 2)
			error_("Colors must be R,G,B colors in range [0,255]", NULL);
	}
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}

int	check_color_formula(char **color_line)
{
	int		i;
	char	*color;

	i = 0;
	while (color_line[i])
		i++;
	if (i > 2 || ft_strchr(color_line[1], '\t') != NULL)
		error_("Color is not in valid, check if you have any extra tab", NULL);
	i = 0;
	color = color_line[1];
	while (color[i] && (color[i] == ' '))
		i++ ;
	while (color[i])
	{
		if ((ft_isdigit(color[i]) == 0 && color[i] != ',')
			|| (color[i] == ',' && color[i + 1] == ',')
			|| color[ft_strlen(color) - 1] == ',')
			error_("Color is not valid", color);
		i++;
	}
	check_color_range(color);
	return (1);
}


void	trim_type_ids(t_map *map)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (map->map_s[++i])
	{
		j = 0;
		while (map->map_s[i][j] &&
			(map->map_s[i][j] == ' ' || map->map_s[i][j] == '\t'))
			j++;
		if (map->map_s[i][j] == '1')
		{
			map->map_idx = i;
			break ;
		}
		tmp = ft_strdup(map->map_s[i]);
		free(map->map_s[i]);
		map->map_s[i] = ft_strtrim(tmp, " \t");
		free(tmp);
	}
}
