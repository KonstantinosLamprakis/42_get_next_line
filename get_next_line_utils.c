/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/15 14:43:22 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[j + i] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter] != '\0')
		counter++;
	return (counter);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	if ((int) len < 0)
		len = ft_strlen(s);
	if (start > ft_strlen(s) || len < 0)
		result = malloc(1 * sizeof(char));
	else if (ft_strlen(s) - start < len)
		result = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i + start] != '\0' && i < len)
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup(const char	*s1)
{
	char	*dst;
	int		i;

	dst = malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (dst);
	i = 0;
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

// returns:
// NULL if sentense is null or doesn't contain a whole sentense yet
// sub-sentense allocated if exists in sentense and update its values
// args:
// sen: contains the sentence that should be checked for \n
// if \n found, temp_str_res holds this line, sentense updated to hold the rest
char	*has_prev_sentense(char **sen)
{
	int		i;
	char	*temp_str_sen;
	char	*temp_str_res;

	if (!(*sen))
		return (NULL);
	i = 0;
	while ((*sen)[i] != '\n' && (*sen)[i] != '\0')
		i++;
	if ((*sen)[i] == '\0')
		return (NULL);
	temp_str_res = ft_substr((*sen), 0, i + 1);
	if (i == 0)
	{
		free((*sen));
		return (temp_str_res);
	}
	temp_str_sen = ft_substr((*sen), i + 1, ft_strlen((*sen)) - (i + 1));
	free((*sen));
	(*sen) = temp_str_sen;
	return (temp_str_res);
}
