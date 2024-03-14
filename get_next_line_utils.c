/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:42:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/14 20:09:52 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_empty(void);
static char	*ft_strcpy(char	*dest, const char	*src);

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
		return (get_empty());
	if (ft_strlen(s) - start < len)
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

static char	*get_empty(void)
{
	char	*result;

	result = malloc(1 * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (result);
}

char	*ft_strdup(const char	*s1)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (dst);
	ft_strcpy(dst, s1);
	return (dst);
}

static char	*ft_strcpy(char	*dest, const char	*src)
{
	int		i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
