/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/18 13:37:29 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// cc -Wall -Werror -Wextra *.c *.h && ./a.out | cat -e
// TODO delete <stidio.h> from .h

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	char		*result;
	static char	*mem_str = NULL;
	int			num_bytes;

	result = get_first_line(&mem_str);
	if (result)
		return (result);
	while (42)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
			return get_whole_str(&mem_str);
		put_buffer(buffer, num_bytes, &mem_str);
		result = get_first_line(&mem_str);
		if (result)
			return (result);
		if (num_bytes < BUFFER_SIZE)
			return (get_whole_str(&mem_str));
	}
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
// 		printf("\n>>>>>>\n i: %d\nlength: %d\n result: %s\n<<<<<<\n", i, ft_strlen(str), str);
// 		str = get_next_line(fd);
// 		i++;
// 	}
// 	close(fd);
// }
