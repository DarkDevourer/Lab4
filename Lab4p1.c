#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	if (access(argv[1], F_OK) == -1)
	{
		printf("FILE ISN'T ACCESSABLE!");
		return -1;
	}
	execlp("cat", "cat",  argv[1], (char*)0);
	return 0;
}