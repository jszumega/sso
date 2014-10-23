#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define size 1024
int main(int argc, char**argv)
{
        int fd[2];
        int child, status;
        int bytes;
        char buf1[size];

        memset(buf1, 0, size);

        pipe(fd);
        printf("Main process: I'm trying to receive sth from ls programm\n");
        
        if((child=fork())==0)
        {
                close(fd[0]);
		close(1);
		dup(fd[1]);
               	execl("/bin/ls","ls",0);
        }              
       	else
	{
		close(fd[1]);
		do
		{
			read(fd[0],buf1, sizeof(buf1));
			printf("I did it!:\n%s\n", buf1);
		}while(bytes==size);
		wait(&status);
        }       
	
	return 0;   
}

     

