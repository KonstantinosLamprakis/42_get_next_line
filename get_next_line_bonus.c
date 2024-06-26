/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/18 15:52:56 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// cc -Wall -Werror -Wextra *.c *.h && ./a.out | cat -e

static char	*return_null(char **mem_str);

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	char		*result;
	static char	*mem_str[100];
	int			num_bytes;

	if (fd < 0 || fd >= 100)
		return (NULL);
	result = get_first_line(&(mem_str[fd]));
	if (result)
		return (result);
	while (42)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
			return (return_null(&(mem_str[fd])));
		put_buffer(buffer, num_bytes, &(mem_str[fd]));
		result = get_first_line(&(mem_str[fd]));
		if (result)
			return (result);
		if (num_bytes < BUFFER_SIZE)
			return (get_whole_str(&(mem_str[fd])));
	}
}

static char	*return_null(char **mem_str)
{
	if (*mem_str)
		free(*mem_str);
	*mem_str = NULL;
	return (NULL);
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

// #include <fcntl.h>
// int main(void)
// {
// 	// char	*test;
// 	// test = NULL;
// 	// get_first_line(&test);
// 	printf("BUFFER_SIZE %i\n", BUFFER_SIZE);
// 	char	*str;
// 	int		i;

// 	int fd = open("empty.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	i = 0;
// 	while(str && i != 6)
// 	{
// 		printf("\n>\n i: %d\nlen: %d\n res: %s\n<\n", i, ft_strlen(str), str);
// 		str = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// }
