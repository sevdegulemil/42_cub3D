/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:48:03 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:59 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_free_all(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static int	ft_word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	*copy_word(const char *s, char c, int *j)
{
	int		word_len;
	char	*word;
	int		k;

	word_len = ft_word_len(&s[*j], c);
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	k = 0;
	while (k < word_len)
	{
		word[k] = s[*j + k];
		k++;
	}
	word[word_len] = '\0';
	*j += word_len;
	return (word);
}

char	**allocate_words(const char *s, char c, int word_count)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!arr)
		return (NULL);
	while (i < word_count)
	{
		while (s[j] == c)
			j++;
		arr[i] = copy_word(s, c, &j);
		if (!arr[i])
		{
			ft_free_all(arr, i - 1);
			return (NULL);
		}
		i++;
	}
	arr[word_count] = NULL;
	return (arr);
}

char	**ft_split_a(const char *s, char c)
{
	int	j;
	int	word_count;

	j = 0;
	word_count = 0;
	if (!s)
		return (NULL);
	while (s[j])
	{
		if (s[j] != c && (j == 0 || s[j - 1] == c))
			word_count++;
		j++;
	}
	return (allocate_words(s, c, word_count));
}
