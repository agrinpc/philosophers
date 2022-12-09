/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:26 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/08 22:05:30 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
int	main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc !=5 && argc != 6)
	{
		printf("Error: Number of arguments is not correct - <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[number_of_times_each_philosopher_must_eat]>\n");
		return (0);
	}
	data.num_philos = argv[1];
	data.ttd = argv[2];
	data.tte = argv[3];
	data.tts = argv[4];
	if (argc == 6)
		data.num_eat = argv[5];
	return (0);
}