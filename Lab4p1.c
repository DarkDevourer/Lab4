#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	/*int file_descriptor;
	sscanf(argv[2], "%d", &file_descriptor);
	int rfile = open(argv[1], O_RDONLY);
	if (rfile == -1)
	{
		return -1;
	}

	char buffer[1024];
	int rbytes;
	while (1)
	{
		if ((rbytes = read(rfile, &buffer, 1024)) == 1024)
		{
			write(file_descriptor, buffer, 1024);
		}
		else
		{
			write(file_descriptor, buffer, rbytes);
			break;
		}
	}
	close(rfile);*/
	if (access(argv[1], F_OK) == -1)
	{
		printf("FILE ISN'T ACCESSABLE!");
		return -1;
	}
	execlp("cat", "cat",  argv[1], (char*)0);
	return 0;
}