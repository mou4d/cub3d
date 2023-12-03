/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:57:09 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/03 23:24:58 by mbousbaa         ###   ########.fr       */
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
		check_texture_file(tmp);
		ret += 1;
	}
	else if ((!ft_strncmp(tmp[0], "F", 2) || !ft_strncmp(tmp[0], "C", 2))
		&& check_color_formula(tmp))
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
		//removing spaces & tabs from the beginning of type ids
		trim_type_ids(map);
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

int	check_line(char **map, char *line, int c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] == '1')
		i++;
	if (!line[i])
		return (1);
	while (line[i])
	{
		if (ft_strchr("0NSWE", line[i]))
		{
			//if 0 in the 1st line or the 1st of a line or at the last
			if (i == 0 || c == 6 || !map[c][i + 1])
				return (0);
			//if 0 is the 1st after space or before
			if (map[c][i - 1] == ' ' || ft_strchr("10NSWE", map[c][i + 1]) == NULL)
				return (0);
			//if 0 is last and nothing above
			if (!map[c - 1][i] || (map[c - 1]
				&& ft_strchr("10NESW", map[c - 1][i]) == NULL))
				return (0);
			//check if no space or emty below a 0
			if (map[c + 1] && ft_strchr("10NSWE", map[c + 1][i]) == NULL)
				return (0);
			if (!map[c + 1])
				return (0);
		}
		i++;
	}
	return (1);
}

void	check_walls(char **map)
{
	int	i;
	int	j;

	i = 6;
	while (map[i])
	{
		printf("line %d\n", i);
		if (!check_line(map, map[i], i))
			error_("map not closed correctly (check_walls())", NULL);
		i++;
	}
}

int	process_map(t_map *map)
{
	int	ret;

	ret = 0;
	if (check_map_elements(map, map->map_s, "NSEW01 	") != 1)
		return (printf("Map elements not valid\n"));
	// ret = check_top_border(map);
	// ret = check_bottom_border(map);
	// ret = check_side_borders(map);
	/// Temporary 
	check_walls(map->map_s);
	ret  = 5;
	while (map->map_s[++ret])
		printf("%s\n", map->map_s[ret]);
	// ret = 6;
	// while (map->map_s_copy[ret])
	// {
	// 	while (*(map->map_s_copy[ret]))
	// 	{
	// 		if (*(map->map_s_copy[ret]) == '0')
	// 			error_("Map not closed :(", NULL);
	// 		(map->map_s_copy[ret])++;
	// 	}
	// 	ret++;
	// }
	printf("\nmap closed (y)\n");
	exit(0);
	/// ##############
	if (!ret)
		return (printf("Map not closed properly\n"));
	return (ret);
}

