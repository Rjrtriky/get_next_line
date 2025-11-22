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
/*FT_STRLEN
 * @def Calculates the length of a string (number of characters before '\0').
 *
 * @param
 *      {string} *str - string whose length is to be calculated.
 *
 * @returns {number}
 *      OK - Length of the string as size_t.
 *      KO - Undefined if str is NULL (no control implemented).
 *
 * @dev
 *      Iterates character by character until reaching the null terminator '\0'.
 *      Counts the number of iterations and returns it as the length.
 * */

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*FT_BZERO
 * @def Sets a block of memory to zero.
 *
 * @param
 *      {pointer} *ptr - pointer to the memory block to be cleared.
 *      {number} len - number of bytes to set to zero.
 *
 * @returns {pointer}
 *      OK - Returns the same pointer received, now zeroed.
 *      KO - Undefined if ptr is NULL (no control implemented).
 *
 * @dev
 *      Iterates over each byte of the memory block and assigns 0.
 *      Useful for initializing memory to a clean state.
 * */
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

/*FT_CALLOC
 * @def Allocates memory for an array of elements and initializes it to zero.
 *
 * @param
 *      {number} num - number of elements to allocate.
 *      {number} size - size of each element in bytes.
 *
 * @returns {pointer}
 *      OK - Pointer to the allocated and zero-initialized memory.
 *      KO - NULL if allocation fails or if overflow is detected.
 *
 * @dev
 *      Checks for multiplication overflow between num and size.
 *      Uses malloc to allocate the required memory.
 *      Calls ft_bzero to initialize the allocated memory to zero.
 * */
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
