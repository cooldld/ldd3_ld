#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>

int main(int argc, char *argv[])
{
	int fd;
	struct epoll_event ep_event;
	int err;
	int ep_fd;
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

	ep_fd = epoll_create(1);
	if (ep_fd < 0)
	{
		printf("epoll_create fail\n");
		exit(0);
	}

	memset(&ep_event, 0, sizeof(struct epoll_event));
	ep_event.events = EPOLLIN | EPOLLPRI;

	err = epoll_ctl(ep_fd, EPOLL_CTL_ADD, fd, &ep_event);
	if (err < 0)
	{
		printf("epoll_ctl add fail\n");
		exit(0);
	}

	printf("epoll_wait read start, timeout=15s\n");
	err = epoll_wait(ep_fd, &ep_event, 1, 15000);
	if (err < 0)
	{
		printf("epoll_wait read fail\n");
	}
	else if (err == 0)
	{
		printf("epoll_wait read timeout\n");
	}
	else
	{
		printf("epoll_wait read ok\n");
	}

	err = epoll_ctl(ep_fd, EPOLL_CTL_DEL, fd, &ep_event);
	if (err < 0)
	{
		printf("epoll_ctl delete fail\n");
		exit(0);
	}

	close(fd);
	exit(0);
}
