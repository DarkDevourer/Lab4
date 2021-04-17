#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
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
			write(0, buffer, 1024);
		}
		else
		{
			write(0, buffer, rbytes);
			break;
		}
	}
	return 0;
}