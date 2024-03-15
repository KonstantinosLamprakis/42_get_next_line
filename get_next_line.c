/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/15 15:53:33 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	init(char **sentense, char buffer[BUFFER_SIZE], int fd);
static int	is_valid_bytes(char **sentense, int bytes_read);
static char	*update_values(char **sentense, char **temp_res, char **temp_sen);
static int	read_buf(char **sen, int bytes, char buf[BUFFER_SIZE], char **res);

// cc -Wall -Werror -Wextra *.c *.h && ./a.out | cat -e
// TODO maybe need to free prev sentense or return it before errors NULL

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		buffer[BUFFER_SIZE];
	char		*temp_str_res;
	char		*result;
	static char	*sentense;

	if (!init(&sentense, buffer, fd))
		return (NULL);
	temp_str_res = has_prev_sentense(&sentense);
	if (temp_str_res)
		return (temp_str_res);
	while (42)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!is_valid_bytes(&sentense, bytes_read))
			return (sentense);
		if (read_buf(&sentense, bytes_read, buffer, &result))
			return (result);
	}
	return (result);
}

// first checks if file descriptor (fd) is valid
// initialize the buffer with \0 values
// return 0 if fd is ivalid and free memory to terminate the program
static int	init(char **sentense, char buffer[BUFFER_SIZE], int fd)
{
	int	i;

	if (fd == -1)
	{
		if (*sentense)
			free(*sentense);
		return (0);
	}
	i = BUFFER_SIZE;
	while (--i >= 0)
		buffer[i] = '\0';
	return (1);
}

// returns 0 if need to stop the program and return sentense
// returns 1 if the program need to continue
// read_bytes == -1 means error on read and should return NULL
// read_bytes == 0 means nothing to read so return prev sentense if exists
// updates properly sentense to be eiher NULL either the initial value
static int	is_valid_bytes(char **sentense, int bytes_read)
{
	if (bytes_read == -1)
	{
		if (*sentense)
			free(*sentense);
		*sentense = NULL;
		return (0);
	}
	else if (bytes_read == 0)
	{
		if (*sentense && (*sentense)[0] != '\0')
			return (0);
		else if (*sentense)
			free(*sentense);
		*sentense = NULL;
		return (0);
	}
	return (1);
}

// returns result or NULL if nothing to return as new line
// update value of sentense
static char	*update_values(char **sentense, char **temp_res, char **temp_sen)
{
	char	*result;

	result = NULL;
	if (!(*sentense))
	{
		result = *temp_res;
		*sentense = *temp_sen;
	}
	else
	{
		result = ft_strjoin(*sentense, *temp_res);
		free (*sentense);
		*sentense = *temp_sen;
	}
	if (*temp_res)
		free (*temp_res);
	if (*sentense && !(*sentense)[0])
		free(*sentense);
	return (result);
}

// buf = buffer with the bytes we read
// byte = number of the bytes that we read
// sen = the previous sentense we have from prev iterations
// res = result, current sentese to return
// returns 1 if finished with the result, we found \n or EOF
// returns 0 if just updated sentense and need to read next buffer
// read bytes, if we have \n we retrun the result else we need read next
static int	read_buf(char **sen, int bytes, char buf[BUFFER_SIZE], char **res)
{
	char	*temp_str_res;
	char	*temp_str_sen;
	int		i;

	i = 0;
	temp_str_sen = NULL;
	while (i < bytes && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
	{
		temp_str_res = ft_substr(buf, 0, i + 1);
		temp_str_sen = ft_substr(buf, i + 1, bytes - (i + 1));
	}
	else if (bytes < BUFFER_SIZE)
		temp_str_res = ft_substr(buf, 0, i);
	else
	{
		temp_str_sen = ft_substr(buf, 0, i);
		*sen = ft_strjoin(*sen, temp_str_sen);
		if (temp_str_sen)
			free (temp_str_sen);
		return (0);
	}
	*res = update_values(sen, &temp_str_res, &temp_str_sen);
	return (1);
}

// #include <fcntl.h>
// int main(void)
// {
// 	printf("BUFFER_SIZE %i\n", BUFFER_SIZE);
// 	char	*str;
// 	int		i;

// 	int fd = open("empty.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	i = 0;
// 	while(str)
// 	{
// 		printf("\n>>>>>>\n i: %d\n result: %s\n<<<<<<\n", i, str);
// 		str = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// }
