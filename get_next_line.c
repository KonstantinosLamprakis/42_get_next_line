/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/14 19:54:19 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// cc -Wall -Werror -Wextra *.c *.h && ./a.out | cat -e
// TODO maybe need to free prev sentense or return it before errors NULL

char	*get_next_line(int fd)
{
	int			bytes_read;
	static		buffer[BUFFER_SIZE];
	char		*temp_str_res;
	char		*temp_str_sen;
	int			i;
	char		*result;
	static char	*sentense;

	if (fd == -1)
		return (NULL);
	i = BUFFER_SIZE;
	while (--i >= 0)
		buffer[i] = '\0';
	while (42)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
		{
			result = ft_strdup(sentense);
			free (sentense);
			return (result);
		}
		i = 0;
		while (i < bytes_read && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
		{
			temp_str_res = ft_substr(buffer, 0, i + 1);
			temp_str_sen = ft_substr(buffer, i + 2, bytes_read - (i + 1));
		}
		else if (bytes_read < BUFFER_SIZE)
		{
			temp_str_res = ft_substr(buffer, 0, i);
			temp_str_sen = NULL;
		}
		else
		{
			temp_str_sen = ft_substr(buffer, 0, i);
			sentense = ft_strjoin(sentense, temp_str_sen);
			if (temp_str_sen)
				free (temp_str_sen);
			continue ;
		}
		result = ft_strjoin(sentense, temp_str_res);
		if (sentense)
			free (sentense);
		sentense = temp_str_sen;
		if (temp_str_res)
			free (temp_str_res);
	}
	return (result);
}

int	main(void)
{
	get_next_line(1);
}

// // read_dict: read the dict-file and initialize dict num-words and their size
// // return: 0 on error, 1 on success
// int	read_dict(char *file, char d_n[L][C], char d_w[L][C], int *size)
// {
// 	int		fd;
// 	ssize_t	bytes_read;
// 	char	c_j_k[3];
// 	int		is_n_spb_nl[3];

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		return (0);
// 	is_n_spb_nl[0] = 1;
// 	is_n_spb_nl[1] = 1;
// 	is_n_spb_nl[2] = 1;
// 	bytes_read = read(fd, c_j_k, 1);
// 	c_j_k[2] = 0;
// 	while (bytes_read > 0)
// 	{
// 		if (is_n_spb_nl[2] && !is_space(c_j_k[0]) && c_j_k[0] != '\n')
// 			is_n_spb_nl[2] = 0;
// 		if (!(c_j_k[0] == '\n' && is_n_spb_nl[2]))
// 			*size += r_c(d_n, d_w, c_j_k, is_n_spb_nl);
// 		bytes_read = read(fd, c_j_k, 1);
// 	}
// 	if (bytes_read == -1)
// 		return (0);
// 	close(fd);
// 	return (1);
// }
