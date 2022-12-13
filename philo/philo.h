/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:22 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/13 01:42:21 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t fork;
	int				is_available;
}				t_fork;

typedef struct	s_data
{
	int				tte;
	int				ttd;
	int				tts;
	int				num_philos;
	int				num_eat;
	int				dead;
	t_fork			*forks;
	long long		start;
	pthread_mutex_t	general;
} 				t_data;

typedef struct	s_philo
{
	int			id;
	int			state;
	long long	last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread;
	t_data		*data;
}				t_philo;

#endif