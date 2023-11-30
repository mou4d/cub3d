/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:57:09 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/30 19:49:03 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_type_id(char	*type_id, int count)
{
	int		ret;
	char	**tmp;

	ret = count;
	tmp = ft_split(type_id, ' ');
	if (ft_strncmp(tmp[0], "NO", 3) == 0
		|| ft_strncmp(tmp[0], "SO", 3) == 0
		||ft_strncmp(tmp[0], "WE", 3) == 0
		|| ft_strncmp(tmp[0], "EA", 3) == 0)
	{
		// if (tmp[0][2] == '\0')
		// 	ret += 1;
		// else
		// 	ret = 0;
		check_texture_file(tmp);
		ret += 1;
	}
	else if ((tmp[0][0] == 'F' && tmp[0][1] == '\0')
			|| (tmp[0][0] == 'C' && tmp[0][1] == '\0'))
		ret += 1;
	else
		ret = 0;
	free_2d_array(tmp);
	return (ret);
}

void	init_type_ids(t_map *map, char *type)
{
	char	**tmp;

	tmp = ft_split(type, ' ');
	if (tmp == NULL)
		return ;
	if (tmp[1] == NULL)
	{
		free_2d_array(tmp);
		error_("All type identifers need to have a value !", NULL);
	}
	if (tmp[0][0] == 'F' && tmp[0][1] == '\0')
		map->F = ft_strdup(tmp[1]);
	else if (tmp[0][0] == 'C' && tmp[0][1] == '\0')
		map->C = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "NO", 2) == 0)
		map->NO = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "SO", 2) == 0)
		map->SO = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "WE", 2) == 0)
		map->WE = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "EA", 2) == 0)
		map->EA = ft_strdup(tmp[1]);
	free_2d_array(tmp);
}

/// @brief process map and initialize the type ids in map struct
/// @param map pointer to t_map struct
/// @return processed type ids count 
int	process_type_ids(t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0; // representing how many type id parocessed
	while (map->map_s[i] && i < 6)
	{
		// Checking the first char of type id && if we reached all type ids
		if (!ft_isalpha(map->map_s[i][0]) && count <= 6) 
			break ;
		// check content of line 
		count = check_type_id(map->map_s[i], count);
		// break if this line doesn't contain a type id
		if (count == 0)
			break ;
		//initialize type id in the map struct
		init_type_ids(map, map->map_s[i]);
		i++;
	}
	// if something happened and we didn't get all type ids
	if (count != 6)
		error_("Check if all the 6 type identifiers are in a correct format !", NULL);
	return (count);
}

/// @brief Read map file and return a pointer to t_map
/// @param file pointer to map file path
/// @return a poiter to t_map struct
t_map	*read_map(char *file)
{
	int		fd;
	int		r_count;
	char	buff[BUFSIZ];
	t_map	*ret;

	ret = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 3)
		error_(NULL, file);
	r_count = read(fd, buff, BUFSIZ);
	if (r_count <= 0)
		error_(NULL, NULL);
	buff[r_count] = '\0';
	ret = (t_map *) malloc(sizeof(t_map));
	if (!ret)
		return (NULL);
	ret->map_fd = fd;
	ret->map_s = ft_split(buff, '\n');
	ret->init_player_x = -1;
	ret->init_player_y = -1;
	return (ret);
}

int	process_map(t_map *map)
{
	int	ret;

	ret = 0;
	if (check_map_elements(map, map->map_s, "NSEW01 	") != 1)
		return (printf("Map elements not valid\n"));
	ret = check_top_border(map);
	ret = check_bottom_border(map);
	ret = check_side_borders(map);
	if (!ret)
		return (printf("Map not closed properly\n"));
	return (ret);
}

