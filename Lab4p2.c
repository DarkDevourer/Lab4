#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int file_data;
	int gamma_data;
	int file_pipes[2];
	int gamma_pipes[2];
	char filebuf[BUFSIZ + 1];
	char gammabuf[BUFSIZ + 1];
	char tmpbuf[BUFSIZ + 1];
	pid_t fork_result;

	memset(filebuf, '\0', sizeof(filebuf));
	memset(gammabuf, '\0', sizeof(gammabuf)); //TODO: ПРОВЕРИТЬ BUFSIZ
	memset(tmpbuf, '\0', sizeof(tmpbuf)); //TODO: ПРОВЕРИТЬ BUFSIZ

	if ((access(argv[1], F_OK) == -1) || (access(argv[2], F_OK) == -1) || (argc == 3))
	{
		printf("SOME FILES ARE NOT ACCESSEBLE!\n");
		return -1;
	}

	if (pipe(file_pipes) != 0)
	{
		printf("COULDN'T OPEN PIPE!");
		return -2;
	}
	fork_result = fork();
	if (fork_result == (pid_t)-1)
	{
		//printf("CHILD PROCESS COMMITED SUICIDE! SOMEBODY CALL THE POLICE!")
		printf("FORK FAILED!");
		return -3;
	}
	else if (fork_result == 0)
	{
		sprintf(tmpbuf, "%d", file_pipes[1]);
		execlp("./rdfiles", "./rdfiles",  argv[1], tmpbuf, (char*)0);
		//execlp("ls", "ls", (char*)0);
		exit(EXIT_FAILURE);

	}
	else
	{
		int stat_val;
		wait(&stat_val);
		file_data = read(file_pipes[0], filebuf, BUFSIZ);
		//printf("file_data = %d\n", file_data);
	}

	close(file_pipes[0]);
	close(file_pipes[1]);
	memset(tmpbuf, '\0', sizeof(tmpbuf)); //TODO: ПРОВЕРИТЬ BUFSIZ

	if (pipe(gamma_pipes) != 0)
	{
		printf("COULDN'T OPEN PIPE!");
		return -4;
	}

	fork_result = fork();
	if (fork_result == (pid_t)-1)
	{
		//printf("CHILD PROCESS COMMITED SUICIDE! SOMEBODY CALL THE POLICE!")
		printf("FORK FAILED!");
		return -5;
	}
	else if (fork_result == 0)
	{
		sprintf(tmpbuf, "%d", gamma_pipes[1]);
		execlp("./rdfiles", "./rdfiles",  argv[2], tmpbuf, (char*)0);
		//execlp("ls", "ls", (char*)0);
		exit(EXIT_FAILURE);

	}
	else
	{
		int stat_val;
		wait(&stat_val);
		gamma_data = read(gamma_pipes[0], gammabuf, BUFSIZ);
		//printf("gamma_data = %d\n", gamma_data);
	}

	//printf("\n%s\n%s", filebuf,gammabuf);
	memset(tmpbuf, '\0', sizeof(tmpbuf)); //TODO: ПРОВЕРИТЬ BUFSIZ

	close(gamma_pipes[0]);
	close(gamma_pipes[1]);

	if (gamma_data<file_data)
	{
			printf("FILE DATA IS BIGGER THEN GAMMA KEY. CONTINUE GAMMING?\nPRINT \"Y\" TO CONTINUE.\nPRINT ANYTHING ELSE TO QUIT.\n");
			scanf("%s", tmpbuf);
			if((toupper(tmpbuf[0])!='Y')||(tmpbuf[1]!='\0'))
			{
				printf("STOP GEMMING! QUIT PROGRAMM!\n");
				return 0;
			}
	}
	memset(tmpbuf, '\0', sizeof(tmpbuf)); //TODO: ПРОВЕРИТЬ BUFSIZ

	int gammized_file = open(argv[3], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR| S_IWUSR);
	if(gammized_file == -1)
	{
		printf("COULDN'T OPEN FILE FOR WRITING GAMMIZED DATA!\n");
		return -10;
	}

	for(int i = 0;i < file_data; i++)
	{
		tmpbuf[i] = filebuf[i] ^ gammabuf[i%gamma_data];
	}
	write(gammized_file, &tmpbuf, file_data);
	close(gammized_file);
	printf("GAMMING COMPLETED SUCCESSFULLY!\n");

	return 0;
}