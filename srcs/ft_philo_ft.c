#include "../includes/philosophers.h"

long long	ft_get_time(t_ph *ph, long long ret)
{
	pthread_mutex_lock(&ph->phm->var);
	gettimeofday(&ph->phm->time, NULL);
	ph->current_time = (ph->phm->time.tv_sec * 1000) + (ph->phm->time.tv_usec / 1000);
	ph->ms_time = ph->current_time - ph->start_time;
	pthread_mutex_unlock(&ph->phm->var);
	return (ret);
}

void	ft_think(t_ph *ph)
{
	pthread_mutex_lock(&ph->phm->print);
	ft_printf("%d %d is thinking\n", ph->ms_time, ph->philo_id);
	pthread_mutex_unlock(&ph->phm->print);
}

void	ft_eat(t_ph *ph)
{
	pthread_mutex_lock(&ph->phm->fork[ph->left_fork]);
	pthread_mutex_lock(&ph->phm->fork[ph->right_fork]);

	ph->since_ate = ft_get_time(ph, ph->current_time);

	pthread_mutex_lock(&ph->phm->print);
	ft_printf("%d %d is eating\n", ph->ms_time, ph->philo_id);
	pthread_mutex_unlock(&ph->phm->print);

	ph->since_ate = ft_get_time(ph, ph->current_time);
	while ((int)(ft_get_time(ph, ph->current_time) - ph->since_ate) < ph->phm->eat_time)
		usleep(5);
	pthread_mutex_unlock(&ph->phm->fork[ph->left_fork]);
	pthread_mutex_unlock(&ph->phm->fork[ph->right_fork]);
	ph->since_ate = ft_get_time(ph, ph->current_time);
}

void	ft_sleep(t_ph *ph)
{
	pthread_mutex_lock(&ph->phm->print);
	ft_printf("%d %d is sleeping\n", ph->ms_time, ph->philo_id);
	pthread_mutex_unlock(&ph->phm->print);

	while ((int)(ft_get_time(ph, ph->current_time) - ph->since_ate) < ph->phm->sleep_time)
		usleep(5);
}

void	*ft_philo_ft(void *arg)
{
	t_ph	*ph;

	ph = (t_ph *)arg;
	gettimeofday(&ph->phm->time, NULL);
	ph->current_time = (ph->phm->time.tv_sec * 1000) + (ph->phm->time.tv_usec / 1000);
	ph->start_time = ph->current_time;
	ph->since_ate = ph->current_time;
	ph->ms_time = ph->current_time - ph->start_time;
	if ((ph->philo_id % 2) == 1)
		ft_think(ph);
	else if (ph->philo_id == ph->phm->philo_count - 1)
		ft_think(ph);

	while (1)
	{
		ft_eat(ph);
		ft_sleep(ph);
		ft_think(ph);
	}
	return (NULL);
}