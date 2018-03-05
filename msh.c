/*Min shell, a minimal shell program
 *Copyright (C) 2018  Max Blachman; blachmanmax at gmail dot com
 *This program is free software; you can redistribute it and/or
 *modify it under the terms of version 2 of the GNU General Public 
 *License as published by the Free Software Foundation
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program; if not, write to the Free Software
 *Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 1000 //maximum characters allowed per line of user input
#define MAX_NUM_ARGS 100 //maximum number of arguments allowed after command

//returns 1 if the last character is an ampersand and 0 otherwise
//replaces the ampersand with NULL
int dobackground(char** last_arg)
{
	char* loc;
	loc = strrchr(*last_arg, '&');
	if (loc!=NULL && *(loc+1) == '\0') {//string ends with ampersand
		if (loc == *last_arg) //whole string is &
			*last_arg = NULL;
		else
			*loc = '\0';
		return 1;
	}
	return 0;
}

/*puts the last element of  the current working directory in curdir*/
char* getdir(char* curdir, char* pthsep, int dirlen)
{
	char *wrkdir, *tmpdir;
	char wrkpth[dirlen];

	getcwd(wrkpth, dirlen);

	tmpdir = strtok(wrkpth, pthsep);
	do
		wrkdir = tmpdir;
	while((tmpdir=strtok(NULL, pthsep)) != NULL);
	return strcpy(curdir, wrkdir);
}

int main(void)
{
	int _argc, background;
	pid_t pid;
	char wrkdir[MAX_LINE];
    char input[MAX_LINE];
    char* args[MAX_NUM_ARGS];
    const char* delim = " \n";

	_argc = background = 0;
	

	while(1) {
		getdir(wrkdir, "/", MAX_LINE);
		printf("%s$ ", wrkdir); //print command prompt
		fflush(stdout);

		fgets(input, sizeof(input), stdin); //store user input
		args[_argc=0] = strtok(input, delim); //parse user input
		while(_argc<MAX_NUM_ARGS && (args[++_argc]=strtok(NULL, delim))!=NULL)
			;
		
		if (_argc>1)
			background = dobackground(&args[_argc-1]);
		if (_argc>0 && !strcmp(args[0],"exit"))
			return 0;
		if (_argc>0 && !strcmp(args[0],"cd")) {
            chdir(args[1]);
            continue;
        }

		pid = fork();
		if (pid == 0) { //child executes command
			execvp(args[0], args);
			puts("Command not recognized");
			fflush(stdout);
			_exit(-1);
		}

		if (!background)
			wait(NULL); //wait for child process
			
	}
	return 0;
}
