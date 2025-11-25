/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjuarez- <rjuarez-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-13 12:00:34 by rjuarez-          #+#    #+#             */
/*   Updated: 2025-11-13 12:00:34 by rjuarez-         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

unsigned long int	ft_strlen(const char *str);
void				*ft_bzero(void *ptr, unsigned long int len);
void				*ft_calloc(unsigned long int num, size_t size);
long long int		ft_nstrchr(const char *s, int c);

void				*ft_recalloc(unsigned char *old_ptr,
						unsigned long int new_size);
unsigned char		*ft_get_line(unsigned char **ptr1);
long long int		ft_read_concat(unsigned char **des, int fd);
unsigned char		*ft_return_last(unsigned char **rest);
char				*get_next_line(int fd);

#endif
