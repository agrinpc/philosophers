/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:22 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/08 22:10:41 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

typedef struct s_data
{
	int	tte;
	int	ttd;
	int	tts;
	int	num_philos;
	int	num_eat;
} 	t_data;

typedef struct s_philo
{
	int	state;
}	t_philo;

#endif