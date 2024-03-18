/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/18 14:21:46 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// return NULL if mem_str == NUL or mem_str not contain any new line
// return the first new line of mem_str and updates mem_str with the rest of it
char	*get_first_line(char **mem_str)
{
	int		i;
	int		j;
	char	*result;
	char	*temp_mem_str;

	if(!(*mem_str))
		return (NULL);
	i = 0;
	while ((*mem_str)[i] != '\0' && (*mem_str)[i] != '\n')
		i++;
	if ((*mem_str)[i] == '\0')
		return (NULL);
	result = malloc ((i + 2) * sizeof(char));
	if (!result)
		return (NULL);
	j = -1;
	while (++j <= i)
		result[j] = (*mem_str)[j];
	result[j] = '\0';
	if ((*mem_str)[i + 1] == '\0')
	{
		free(*mem_str);
		*mem_str = NULL;
		return (result);
	}
	temp_mem_str = malloc((ft_strlen(*mem_str) - i) * sizeof(char));
	if (!temp_mem_str)
	{
		free(result);
		return (NULL);
	}
	j = 0;
	while ((*mem_str)[++i] != '\0')
		temp_mem_str[j++] = (*mem_str)[i];
	temp_mem_str[j] = '\0';
	free (*mem_str);
	*mem_str = temp_mem_str;
	return (result);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// puts first num_butes of buffer at the end of mem_str
// if error returns NULL
// if mem_str == NULL, it creates it
void	put_buffer(char buffer[BUFFER_SIZE], int num_bytes, char **mem_str)
{
	int		i;
	int		j;
	char	*temp_str;

	if (!buffer || num_bytes == 0)
		return ;
	if (buffer[0] == '\0')
		return ;
	j = ft_strlen(*mem_str);
	temp_str = malloc ((j + num_bytes + 1) * sizeof (char));
	if (!temp_str)
		return ;
	i = 0;
	while (i < j)
	{
		temp_str[i] = (*mem_str)[i];
		i++;
	}
	j = 0;
	while (j < num_bytes)
		temp_str[i++] = buffer[j++];
	temp_str[i] = '\0';
	if (*mem_str)
		free(*mem_str);
	*mem_str = temp_str;
}

// free the mem_str and returns a new identical string
char	*get_whole_str(char **mem_str)
{
	char	*result;
	int		i;

	if (!(*mem_str))
		return (NULL);
	result = malloc((ft_strlen(*mem_str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while ((*mem_str)[i] != '\0')
	{
		result[i] = (*mem_str)[i];
		i++;
	}
	result[i] = '\0';
	free(*mem_str);
	*mem_str = NULL;
	return (result);
}
