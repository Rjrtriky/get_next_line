/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjuarez- <rjuarez-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-13 12:00:37 by rjuarez-          #+#    #+#             */
/*   Updated: 2025-11-13 12:00:37 by rjuarez-         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*FT_RECALLOC
 * @def	Resize a received pointer variable with the size also received
 *
 * @param
 *		{unsigned char} <nombre del parametro> - que reibe
 *		{number} <nombre del parametro> - que reibe
 *
 * @returns {unsigned char}
 *		OK - string with changed size.
 *		KO - NULL
 *
 * @dev
 * <desarrollo de la funcion>
 * */
void	*ft_recalloc(unsigned char *old_ptr, unsigned long int new_size)
{
	unsigned char	*new_ptr;
	long long int	i;
	size_t			old_size;

	if (new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	new_ptr = (unsigned char *) ft_calloc(new_size, 1);
	if (new_ptr == NULL)
		return (NULL);
	if (old_ptr != NULL)
	{
		old_size = ft_strlen((char *) old_ptr);
		i = -1;
		while ((++i < (int) old_size) && (i < (int) new_size))
			new_ptr[i] = old_ptr[i];
	}
	free(old_ptr);
	old_ptr = new_ptr;
	return (new_ptr);
}

/*FT_GET_LINE
 * @def	It obtains a line ending in '\n' and leaves the rest in the string
 *		received as a parameter.
 *
 * @param
 *		{pointer to unsigned char} **ptr - Pointer to string with line and rest
 *
 * @returns
 *		OK - Returns the line up to '\n' and the rest in the parameter. 
 *		KO - NULL
 *
 * @dev
 * <desarrollo de la funcion>
 * 
 * */
unsigned char	*ft_get_line(unsigned char **rest)
{
	unsigned char	*line;
	size_t			found;
	size_t			aux_len;
	int				i;

	if ((rest == NULL) || (*rest == NULL))
		return (NULL);
	found = ft_nstrchr((char *)*rest, '\n');
	line = ft_calloc(found + 2, sizeof(unsigned char));
	if (line == NULL)
		return (NULL);
	i = -1;
	while (++i <= (int) found)
		line[i] = (*rest)[i];
	line[i] = '\0';
	aux_len = ft_strlen((char *)*rest);
	i = -1;
	while ((int)(found + 1 + ++i) < (int) aux_len)
		(*rest)[i] = (*rest)[found + 1 + i];
	(*rest)[i] = '\0';
	*rest = ft_recalloc(*rest, i + 1);
	if (*rest == NULL)
		return (NULL);
	return (line);
}

/*FT_READ_CONCAT
 * @def	Read from the file and concatenate what you read to an unsigned char
 *		pointer.
 *
 * @param
 *		{pointer to unsigned char} *des - 
 *		{integer number} fd - identifier descriptor of file to read.
 *
 * @returns
 *		OK - Returns the total number of characters and in the received
 *			parameter, the received value and the buffer read from the file.
 *		KO - -1
 *
 * @dev
 * <desarrollo de la funcion>
 * */
int	ft_read_concat(unsigned char **rest, int fd)
{
	size_t	buffer_len;
	size_t	rest_len;

	if (fd < 0)
		return (-1);
	if (*rest == NULL)
		*rest = (unsigned char *) ft_calloc(1, 1);
	rest_len = ft_strlen((char *) *rest);
	*rest = ft_recalloc(*rest, rest_len + BUFFER_SIZE + 2);
	if (*rest == NULL)
		return (-1);
	buffer_len = (size_t) read(fd, (*rest) + rest_len, BUFFER_SIZE);
	if (buffer_len <= 0)
		return (buffer_len);
	(*rest)[rest_len + buffer_len] = '\0';
	return ((int)rest_len + (int)buffer_len + 1);
}

/*FT_RETURN_LAST
 * @def Handles the final return of the remaining buffer when no newline
 *      character is found in the string.
 *
 * @param
 *      {pointer to unsigned char} **rest - double pointer to the buffer
 *      that stores the remaining content.
 *
 * @returns
 *      OK - Returns the last line stored in *rest if it is not empty.
 *      KO - Returns NULL if *rest is empty, freeing the memory.
 *
 * @dev
 *      If the buffer still contains characters, it is returned as the last
 *      line. Otherwise, the memory is freed and NULL is returned. In both
 *      cases, the pointer *rest is set to NULL to avoid dangling references.
 * */
unsigned char	*ft_return_last(unsigned char **rest)
{
	unsigned char	*line;

	if (rest == NULL || *rest == NULL)
		return (NULL);
	if (**rest != '\0')
		line = (*rest);
	else
	{
		free(*rest);
		line = NULL;
	}
	*rest = NULL;
	return (line);
}

/*GET_NEXT_LINE
 * @def  Calling your `get_next_line` function repeatedly (for example, using a
 *	loop) will allow you to read the contents of the file pointed to by the
 *	file descriptor, line by line, to the end.
 *	- Your function should return the line that was just read.
 *	- If there is nothing more to read or if an error has occurred, it should
 *	return NULL.
 *	- Make sure your function behaves correctly when reading from a file and when
 *	reading from stdin.
 *	- Note that the returned line must end with `\n`, unless the end of the file
 *	has been reached and it does not end with `\n`.
 *
 * @param
 *		{integer number} fd - identifier descriptor of file to read.
 * 
 * @returns {string}
 *		OK - the line read up to '\n'
 *		KO - In case of failure or if the reading ends: NULL
 * 
 * @cond
 *		- the file must be open
 * @dev
 * <desarrollo de la funcion>
 * 
 * */
char	*get_next_line(int fd)
{
	static unsigned char	*rest;
	unsigned char			*line;
	ssize_t					rest_len;

	if ((fd < 0) || (BUFFER_SIZE < 0) || (read(fd, 0, 0) < 0))
	{
		if (rest != NULL)
		{
			free(rest);
			rest = NULL;
		}
		return (NULL);
	}
	if (rest == NULL)
		rest = ft_calloc(1, 1);
	rest_len = 1;
	while ((rest_len > 0) && (ft_nstrchr((char *)rest, '\n') < 0))
		rest_len = ft_read_concat(&rest, fd);
	if (rest_len < 0 || rest == NULL)
		return (NULL);
	if (ft_nstrchr((char *)rest, '\n') >= 0)
		line = ft_get_line(&rest);
	else
		line = ft_return_last (&rest);
	return ((char *)line);
}
