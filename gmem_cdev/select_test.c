#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int fd;
	fd_set rfds;
	fd_set wfds;
	char *device;
	int i;

	/*init*/
	device = argv[1];
	i = 0;

	fd = open(device, O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		printf("open fail, device=%s\n", device);
		exit(0);
	}

	while (1)
	{
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_SET(fd, &rfds);
		FD_SET(fd, &wfds);

		select(fd + 1, &rfds, &wfds, NULL, NULL);

		/*can read*/
		if (FD_ISSET(fd, &rfds))
		{
			printf("i=%d, select can read\n", i);
		}

		/*can write*/
		if (FD_ISSET(fd, &wfds))
		{
			printf("i=%d, select can write\n", i);
		}

		i++;
		sleep(1);
	}

	close(fd);
	exit(0);
}
