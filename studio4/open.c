// Lorna Xiao and Vyshnavee Reddlapalli
// 9/8/17
// Studio 4: Error Checking

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define buffer_size 1571
int main(int argc, char* argv[]) {
	int fd;
	int textLen;
	int text;
	char buffer[buffer_size];
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("Error opening file!\n");
		printf("errno = %d\n", errno);
		exit(1);
	}
	while((text = read(fd, buffer, buffer_size) != 0)) {
		write(STDOUT_FILENO, buffer, buffer_size);
	}
return 0;
}

