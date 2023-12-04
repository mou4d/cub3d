/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:09:18 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/04 23:01:19 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_line(char **map, char *line, int cy, int cx)
{
	if (ft_strchr("0NSWE", line[cx]))
	{
		if (cx == 0 || cy == 6 || !map[cy][cx + 1]
			|| (map[cy + 1] && !map[cy + 1][cx]))
			return (0);
		if (map[cy][cx - 1] == ' '
			|| ft_strchr("10NSWE", map[cy][cx + 1]) == NULL)
			return (0);
		if (!map[cy - 1][cx] || (map[cy - 1]
			&& ft_strchr("10NESW", map[cy - 1][cx]) == NULL))
			return (0);
		if ((map[cy + 1] && ft_strchr("10NSWE", map[cy + 1][cx]) == NULL))
			return (0);
		if (!map[cy + 1])
			return (0);
	}
	return (1);
}

int	check_line(char **map, char *line, int c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '1'))
		i++;
	if (!line[i])
		return (1);
	while (line[i])
	{
		ret = validate_line(map, line, c, i);
		if (ret == 0)
			break ;
		i++;
	}
	return (ret);
}

int	check_player_exist(t_map *map, char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i][0]))
			break ;
	while (str[i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (ft_strchr("NSEW", str[i][j]))
			{
				if (map->init_player_x != -1 && map->init_player_y != -1)
					return (printf("Missing/duplicated map element\n"));
				map->init_player_x = j;
				map->init_player_y = i;
			}
		}
		i++;
	}
	if (map->init_player_x == -1)
		return (printf("Missing/duplicated map element\n"));
	return (1);
}

int	check_map_elements(t_map *map, char **str, char *valid_elements)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i][0]))
			break ;
	while (str[i])
	{
		j = -1;
		while (str[i][++j])
			if (!ft_strchr(valid_elements, str[i][j]) && str[i][j] != '0')
				return (0);
		i++;
	}
	ret = check_player_exist(map, map->map_s);
	return (ret);
}

int	check_texture_file(char **type_id)
{
	int	fd;
	int	i;

	i = 0;
	while (type_id[i])
		i++;
	if (i < 2 || i > 2 || ft_strchr(type_id[1], '\t') != NULL)
		error_("Texture not valid, check if you have any extra tabs", NULL);
	if (type_id[1] && ft_strncmp(ft_strrchr(type_id[1], '.'), ".png", 5) != 0)
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
