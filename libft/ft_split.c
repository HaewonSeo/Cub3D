/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:24:01 by haseo             #+#    #+#             */
/*   Updated: 2020/11/23 16:42:17 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free_arr(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static size_t	ft_wordlen(char const *word, char c)
{
	size_t len;

	len = 0;
	while (word[len] != c && word[len] != '\0')
		len++;
	return (len);
}

static char		**ft_split_str(char **split_arr, char const *s, char c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(split_arr[j] = ft_substr(s, i, ft_wordlen(&s[i], c))))
			{
				ft_free_arr(split_arr);
				return (NULL);
			}
			j++;
			i += ft_wordlen(&s[i], c);
		}
		else
			i++;
	}
	return (split_arr);
}

static size_t	ft_cnt_words(char const *s, char c)
{
	size_t		count;
	int			word_start;

	count = 0;
	word_start = 1;
	while (*s)
	{
		if (*s == c)
			word_start = 1;
		else if (word_start == 1)
		{
			count++;
			word_start = 0;
		}
		s++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	size_t		cnt_word;
	char		**split_arr;

	if (!s)
		return (NULL);
	cnt_word = ft_cnt_words(s, c);
	if (!(split_arr = ft_calloc(cnt_word + 1, sizeof(char *))))
		return (NULL);
	split_arr = ft_split_str(split_arr, s, c);
	return (split_arr);
}
