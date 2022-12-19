/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:22 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/18 03:36:24 by miahmadi         ###   ########.fr       */
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

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				is_available;
}					t_fork;

typedef struct s_data
{
	int				tte;
	int				ttd;
	int				tts;
	int				num_philos;
	int				num_eat;
	int				dead;
	t_fork			*forks;
	long long		start;
	pthread_mutex_t	general_mutex;
	pthread_mutex_t	msg_mutex;
	void			*philos;
}					t_data;

typedef struct s_philo
{
	int			id;
	int			state;
	int			num_ate;
	long long	last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread;
	t_data		*data;
}				t_philo;

int		eat(t_philo	*d);
int		ft_atoi(const char *nptr);
int		check_data(int argc, char **argv);
int		check_dead(t_philo *philo);
void	set_data(t_data *data, char **argv, int argc);
void	free_it(t_data	*data, t_philo *philos);
void	print_msg(char *msg, t_philo *philo, int mod, char *color);
void	check_all(t_philo *philos, t_data *data);
void	grab_forks(pthread_mutex_t *m, t_philo *d);
void	*philo_act(void	*philo);
void	mod_sleep(int ms);
long	get_time(void);
t_fork	*set_forks(int num);
t_fork	*get_fork(int i, t_data *data, int mod);
t_philo	*set_philos(t_data *data);

#endif