#include "watchdog_main_header.h"


int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Usage: watchdog <program> [args...]\n exit code -1: 'Needs at least two(2) arguments'\n");
		return -1;
	}

	pid_t pid = fork(); //Child Procccess;

	if(pid == 0){
		freopen("std-out.log", "w", stdout);
		freopen("std-error.log", "w", stderr);

		execvp(argv[1], &argv[1]);

		perror("execvp failed | the log file was not created !\n"
			   "Verify the arguments passed.\n");
		return -1;

	}else if(pid > 0){

		//Create the log file with the timestamp of the time when the file was created;

		LogFile log_text;
		time_t currTime = time(NULL);
		log_text.timestamp = *localtime(&currTime);

		strftime(log_text.filename, sizeof(log_text.filename),
					"watchdog-log-%Hh:%Mm:%Ss.txt", &log_text.timestamp);

		log_text.file = fopen(log_text.filename, "w");

		//error handling...
		if(log_text.file == NULL){
		perror("ERROR WHILE OPENING THE LOG FILE: log_text is NULL !");
		return -1;
		}
		if(log_text.file){
		printf("Log File created successfully !\n");
		}

		//prints the first message on the file;
		fprintf(log_text.file, "###############\n"
						  		"#Opening log #\n"
						  		"###############\n");

		int status;
		waitpid(pid, &status, 0);
		fopen(log_text.filename, "a");

		if(WIFEXITED(status)){
			fprintf(log_text.file, "The program was terminated with the code %d\n", WEXITSTATUS(status));
			fclose(log_text.file);
		}else if(WIFSIGNALED(status)){
			fprintf(log_text.file, "The program was terminated by the signal %d\n", WTERMSIG(status));
			fclose(log_text.file);
		}


	}else{
		perror("FORK ERROR: THE CREATION OF A CHILD PROCESS WAS UNCCCESSFUL: PID < 0 | the log file was not created !\n");
		return -1;
	}

	return 0;
} 