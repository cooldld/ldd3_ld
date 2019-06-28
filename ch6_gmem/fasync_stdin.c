#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

static void sigio_handler(int signum)
{
	char data[100];
	int len;

	len = read(STDIN_FILENO, &data, sizeof(data));
	data[len] = 0;
	printf("%s, signum=%d, len=%d, data=%s", __FUNCTION__, signum, len, data);
}

int main(int argc, char *argv[])
{
	int fd;
	int oflags;

	signal(SIGIO, sigio_handler);

	fd = STDIN_FILENO;
	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

	while (1)
	{
		sleep(1);
	}

	exit(0);
}
