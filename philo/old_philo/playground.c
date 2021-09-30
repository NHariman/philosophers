/*
** Literally just gonna play around with mutex lock i guess.
*/

#include "philo.h"

typedef struct s_playground
{
	pthread_t *tid;
	int			id;
	pthread_mutex_t lock;
}				t_play;

void	*thingamabob(void *arg)
{
	t_play	*play;

	play = (t_play *)arg;
	pthread_mutex_lock(&play->lock);
	printf("job test\n");
	pthread_mutex_unlock(&play->lock);
	return NULL;
}

int		main(void)
{
	t_play play;
	int		i;
	int		num;

	i = 0;
	num = 3;
	pthread_mutex_init(&play.lock, NULL);
	while (i < num)
	{
		pthread_create(&(play.tid[i]), NULL, &thingamabob, &play);
		i++;
	}
	pthread_join(play.tid[0], NULL);
	pthread_join(play.tid[1], NULL);
	pthread_mutex_destroy(&play.lock);
	return (0);
}