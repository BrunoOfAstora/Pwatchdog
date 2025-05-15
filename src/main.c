#include "wd_h.h"

void readFromPipe(int file){
	FILE *stream;
	int ch;
	stream = fdopen(file, "r");
	while((ch = fgetc(stream)) != EOF)
		putchar(ch);
		fclose(stream);
}

void writeToPipe(int file){
	FILE *stream;					//Implementar nova abordagem via pipe
	stream = fdopen(file, "w");
	fprintf(stream, "MSG HERE\n");
	fclose(stream);

}

int main(void){
	pid_t pid;
	int mypipe[2];

	if(pipe(mypipe)){
	fprintf(stderr, "pipe failed\n");
	return EXIT_FAILURE;
	}

	pid = fork();
	if(pid == (pid_t) 0){
	close(mypipe[1]);
	readFromPipe(mypipe[0]);
	return EXIT_SUCCESS;
	}else if (pid < (pid_t) 0){
		fprintf(stderr, "Fork Failed\n");
		return EXIT_FAILURE;
	}else{
		close(mypipe[0]);
		writeToPipe (mypipe[1]);
		return EXIT_SUCCESS;
	}
}
