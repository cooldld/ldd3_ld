#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

static void sigio_handler(int signum)
{
	printf("%s, signum=%d\n", __FUNCTION__, signum);
}

int main(int argc, char *argv[])
{
	int fd;
	int oflags;
	char *device;

	/*init*/
	device = argv[1];

	signal(SIGIO, sigio_handler);

	fd = open(device, O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		printf("open fail, device=%s\n", device);
		exit(0);
	}

	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

	while (1)
	{
		sleep(1);
	}

	close(fd);
	exit(0);
}
