/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miahmadi <miahmadi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:19:26 by miahmadi          #+#    #+#             */
/*   Updated: 2022/12/19 14:40:33 by miahmadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	run(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)(data->philos);
	i = -1;
	while (++i < data->num_philos)
		if (pthread_create(&(philos[i].thread), NULL, \
			&philo_act, &philos[i]) != 0)
			return (1);
	check_all(philos, data);
	i = -1;
	while (++i < data->num_philos)
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;
	t_philo	*philos;
	t_fork	*forks;

	if (!check_data(argc, argv))
		return (0);
	set_data(&data, argv, argc);
	forks = set_forks(data.num_philos);
	if (!forks)
		return (0);
	data.forks = forks;
	philos = set_philos(&data);
	if (!philos)
		return (0);
	data.philos = (void *)philos;
	ret = run(&data);
	if (ret != 0)
		return (ret);
	free_it(&data, philos);
	return (0);
}
