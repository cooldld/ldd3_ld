#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	char *map_buf;
	int i;

	fd = open(argv[1], O_RDWR);
	if(fd<0)
	{
		printf("open device is error, device=%s\n", argv[1]);
		return -1;
	}

	map_buf = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	for (i = 0; i < 16; i++)
	{
		printf("map_buf[%d]=0x%x\n", i, (unsigned char)map_buf[i]);
	}
	printf("map_buf=%s\n", map_buf);

	sleep(1);

	munmap(map_buf, 1024);
	close(fd);

	return 0;
}
