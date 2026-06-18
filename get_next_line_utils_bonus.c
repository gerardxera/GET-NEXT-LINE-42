/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjuan-pa <gjuan-pa@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:35:39 by gjuan-pa          #+#    #+#             */
/*   Updated: 2026/06/11 15:35:44 by gjuan-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		return (NULL);
	copy = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		copy[i++] = s2[j++];
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr(const char *str, int c)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		if (str[len] == (char)c)
			return ((char *)&str[len]);
		len++;
	}
	if ((char)c == '\0')
		return ((char *)&str[len]);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		s++;
		len++;
	}
	return (len);
}
