/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/15 11:11:02 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// cc -Wall -Werror -Wextra *.c *.h && ./a.out | cat -e
// TODO maybe need to free prev sentense or return it before errors NULL

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		buffer[BUFFER_SIZE];
	char		*temp_str_res;
	char		*temp_str_sen;
	int			i;
	char		*result;
	static char	*sentense;

	if (fd == -1)
	{
		if (sentense)
			free(sentense);
		return (NULL);
	}
	i = BUFFER_SIZE;
	while (--i >= 0)
		buffer[i] = '\0';
	i = 0;
	if (sentense)
	{
		// puts("in sentence");
		while(sentense[i] != '\n' && sentense[i] != '\0')
			i++;
		if (sentense[i] == '\n')
		{
			// puts("end of line on prev");
			temp_str_res = ft_substr(sentense, 0, i + 1);
			temp_str_sen = ft_substr(sentense, i + 1, ft_strlen(sentense) - (i + 1));
			free(sentense);
			sentense = temp_str_sen;
			// printf("first: %s\n", temp_str_res);
			// printf("rem: %s\n", temp_str_sen);
			if (sentense && !sentense[0])
				free(sentense);
			return (temp_str_res);
		}
	}
	while (42)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// printf("read bytes: %d\n", bytes_read);
		if (bytes_read == -1)
		{
			if (sentense)
				free(sentense);
			return (NULL);
		}
		else if (bytes_read == 0)
		{
			if (sentense && sentense[0])
				return (sentense);
			else if (sentense)
				free(sentense);
			return (NULL);
		}
		i = 0;
		while (i < bytes_read && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
		{
			// puts("end of line");
			// printf("index of nl: %d - hold on sentense: %d\n", i, bytes_read - (i + 1));
			temp_str_res = ft_substr(buffer, 0, i + 1);
			temp_str_sen = ft_substr(buffer, i + 1, bytes_read - (i + 1));
			// printf("first pass: %s\n", temp_str_res);
			// printf("remainder: %s\n", temp_str_sen);
		}
		else if (bytes_read < BUFFER_SIZE)
		{
			// puts("end of file");
			temp_str_res = ft_substr(buffer, 0, i);
			temp_str_sen = NULL;
		}
		else
		{
			// puts("continue reading");
			temp_str_sen = ft_substr(buffer, 0, i);
			sentense = ft_strjoin(sentense, temp_str_sen);
			if (temp_str_sen)
				free (temp_str_sen);
			continue ;
		}
		if (!sentense)
		{
			result = temp_str_res;
			sentense = temp_str_sen;
		}
		else
		{
			result = ft_strjoin(sentense, temp_str_res);
			free (sentense);
			sentense = temp_str_sen;
			if (temp_str_res)
				free (temp_str_res);
		}
		if (sentense && !sentense[0])
			free(sentense);
		return (result);
	}
	return (result);
}

// #include <fcntl.h>
// int main(void)
// {
// 	//printf("BUFFER_SIZE %i\n", BUFFER_SIZE);
// 	char	*str;
// 	int		i;

// 	int fd = open("empty.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	i = 0;
// 	while(str)
// 	{
// 		printf("\n>>>>>>>>>>>>>>>>\n i: %d\n result: %s\n<<<<<<<<<<<<<<<<\n", i, str);
// 		str = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// };
