#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	char *mapBuf;

	fd = open(argv[1], O_RDWR);
	if(fd<0)
	{
		printf("open device is error, device=%s\n", argv[1]);
		return -1;
	}

	/*测试一：查看内存映射段*/
	printf("before mmap\n");
	sleep(20);//睡眠15秒，查看映射前的内存图cat /proc/pid/maps
	mapBuf = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);//内存映射，会调用驱动的mmap函数
	printf("after mmap, mapBuf=%s\n", mapBuf);
	sleep(15);//睡眠15秒，在命令行查看映射后的内存图，如果多出了映射段，说明映射成功

	munmap(mapBuf, 1024);//去除映射
	close(fd);//关闭文件，最终调用驱动的close
	return 0;
}
