/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjuarez- <rjuarez-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-13 14:32:28 by rjuarez-          #+#    #+#             */
/*   Updated: 2025-11-13 14:32:28 by rjuarez-         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str);
void	*ft_bzero(void *ptr, size_t len);
void	*ft_calloc(size_t num, size_t size);
int		ft_nstrchr(const char *s, int c);

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_bzero(void *ptr, size_t len)
{
	unsigned char	*aux_ptr;
	size_t			i;

	i = 0;
	aux_ptr = ptr;
	while (i < len)
	{
		*aux_ptr = 0;
		aux_ptr++;
		i++;
	}
	return (ptr);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if ((num == 0) || (size == 0))
		return (malloc(0));
	if (size > 0 && num > __SIZE_MAX__ / size)
		return (NULL);
	ptr = malloc(num * size);
	if ((ptr == NULL) || (ft_bzero(ptr, (num * size)) != ptr))
		return (NULL);
	else
		return (ptr);
}

/*FT_NSTRCHAR
 * @def	Searches a string for a character and gives its relative numerical
 *		position within the string.
 *
 * @param
 *		{string} *s - string where to search.
 *		{number} c - character to search.
 * 
 * @returns {number}
 * 		OK - Relative position within the string.
 *		KO - -1
 *
 * @dev
 * <desarrollo de la funcion>
 * */
int	ft_nstrchr(const char *s, int c)
{
	size_t	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}
