/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapValidation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:52:30 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/10/03 14:48:38 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	checking_rgb_number(char *secondPart, t_checking_rgb *var)
{
	var->start = var->i;
	while (ft_isdigit(secondPart[var->i]))
		var->i++;
	var->end = var->i - var->start;
	var->number = ft_substr(secondPart, var->start, var->end);
	var->colorNumber = ft_atoi(var->number);
	if (var->end > 3 || var->colorNumber < 0 || var->colorNumber > 255)
		errorMessage(WRONG_RGB_MSG);
	var->value += var->colorNumber << var->base;
	var->base -= 8;
}
int	checkingRGBFormat(char *secondPart)
{
	t_checking_rgb var;

	rgb_init(&var);
	while (secondPart[var.i])
	{
		if (ft_isdigit(secondPart[var.i]))
		{
			var.digitsCounter++;
			checking_rgb_number(secondPart, &var);
			if (!secondPart[var.i])
				break ;
		}
		else if (secondPart[var.i] == COMMA)
		{
			if (var.commasCounter == 2)
				errorMessage(WRONG_RGB_MSG);
			var.commasCounter++;
		}
		else if (secondPart[var.i] != SPACE)
			errorMessage(WRONG_RGB_MSG);
		var.i++;
	}
	// printf("the counter is : %d\n", var.digitsCounter);
	if (var.digitsCounter != 3)
		errorMessage(WRONG_RGB_MSG);
	return (1);
	// (void)firstPart;
	// t_checking_rgb var;

	// // printf("second is : |%s|\n", secondPart);
	// rgb_init(&var);
	// checkingRGBFormatUtils(secondPart, &var);
	// var.number = ft_substr(secondPart, var.start, var.end);
	// var.colorNumber = ft_atoi(var.number);
	// printf("[%d]\n", var.colorNumber);
	// var.value += var.colorNumber;
	// if (!(var.digitCounter >= 1 && var.digitCounter <= 3) \
    // || var.commasCounter != 2 \
    // || !(var.colorNumber >= 0 && var.colorNumber <= 255))
	// {
	// 	free (var.number);
	// 	errorMessage(WRONG_RGB_MSG);
	// }
	// if (var.number)
	// 	free (var.number);
	// return (var.value);
}

void    isSurroundedByWallsUtils(char *trimmed)
{
    int j;

    j = 0;
    while (trimmed[j])
    {
        if (trimmed[j] != '1' && trimmed[j] != SPACE)
            errorMessage(SURROUNDED_MSG);
        j++;
    }
}

void	isSurroundedByWalls(char **map, int map_height)
{
	int	stringLength;
	int	i;
	char	*trimmed;

	i = 0;
	stringLength = 0;
	while (map[i])
	{
		trimmed = ft_strtrim(map[i], " ");
		stringLength = ft_strlen(trimmed) - 1;
		if (trimmed[0] != '1' || trimmed[stringLength] != '1')
            errorMessage(SURROUNDED_MSG);
		if (i == 0 || i == map_height - 1)
            isSurroundedByWallsUtils(trimmed);
		free (trimmed);
		i++;
	}
}

void    correctPositionForSpaceUtils(int i, int map_height, char **map)
{
    size_t j;

    j = 0;
    while (map[i][j])
    {
        if (map[i][j] == ZERO)
        {
            if ((i < map_height - 1 && j > ft_strlen(map[i + 1]) - 1) \
            || (i < map_height - 1 && j > ft_strlen(map[i - 1]) - 1))
                errorMessage(SURROUNDED_SPACE_MSG);
            if ((i > 0 && map[i - 1][j] == SPACE) \
            || (i < map_height - 1 && map[i + 1][j] == SPACE))
                errorMessage(SURROUNDED_SPACE_MSG);
            if ((map[i][j + 1] == SPACE) \
            || (j > 0 && map[i][j - 1] == SPACE))
                errorMessage(SURROUNDED_SPACE_MSG);
        }
        j++;
    }
}

void	correctPositionForSpace(char **map, size_t map_height)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
        correctPositionForSpaceUtils(i, map_height, map);
		i++;
	}
}

void	mapValidation(t_directions *path)
{
	size_t	map_height;

	map_height = getSize(path->map);
	isSurroundedByWalls(path->map, map_height);
	correctPositionForSpace(path->map, map_height);
	unwantedCharacters(path->map, path);
}