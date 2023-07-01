#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "../libft/libft.h"
#include "pthread.h"
#include "sys/time.h"

typedef struct s_phm
{
	int eat_time;
	int sleep_time;
	int die_time;
	int eat_count;
	int philo_count;
	pthread_t *philo;
	pthread_t check_dead;
	pthread_mutex_t *fork;
	pthread_mutex_t print;
	pthread_mutex_t var;
	struct timeval time;
	struct s_ph **ph;
	int alive;
}	t_phm;

typedef struct s_ph
{
	int philo_id;
	int left_fork;
	int right_fork;
	long long since_ate;
	long long start_time;
	long long current_time;
	int ms_time;
	int ph_eat_count;
	t_phm *phm;
}	t_ph;

void		*ft_philo_ft(void *arg);
t_phm		*ft_create_struct(int argc, char **argv);
void		ft_free_all(t_phm *phm);
long long	ft_get_time(t_ph *ph, long long ret);

#endif