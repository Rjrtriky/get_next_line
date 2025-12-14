/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjuarez- <rjuarez-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-14 13:26:20 by rjuarez-          #+#    #+#             */
/*   Updated: 2025-12-14 13:26:20 by rjuarez-         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

// get_next_line utils.c
size_t			ft_strlen(const char *str);
void			*ft_bzero(void *ptr, size_t len);
void			*ft_calloc(size_t num, size_t size);
int				ft_nstrchr(const char *s, int c);
void			*ft_recalloc(unsigned char *old_ptr,
					unsigned long int new_size);

// get_next_line.c
unsigned char	*ft_get_line(unsigned char **rest);
int				ft_read_concat(unsigned char **rest, int fd);
unsigned char	*ft_return_last(unsigned char **rest);
char			*get_next_line(int fd);

#endif
