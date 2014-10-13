#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPILE_STR "gcc -o ./user_home/a.out ./user_home/user_code.c"
#define COMPILE_TAIL  " 2> compile.dat"
#define CHMOD_STR "chmod 777 ./user_home/a.out" 
#define RUN_STR "./user_home/a.out"
#define RUN_TAIL  " &> run.dat"
#define MAX_STRING 100

int main() {
	FILE *fd = fopen("data","w");
	FILE *fd_com = 0;
    	char cmd_str[200] = "";
	char str_com[MAX_STRING];
    	int  ret;
	fprintf(fd,"you are in run_handler.cgi!\n");
   	printf("%s%c%c\n","Content-Type:text/html;charset=GB2312",13,10);
    	printf("</HEAD><TITLE>Code Run Page</TITLE>\n");
 	printf("<link rel=\"stylesheet\" href=\"../remote.css\" type=\"text/css\" /></HEAD>");
    	printf("<h1>Welcom to Code Run Page</h1>\n");
        strcat(cmd_str,COMPILE_STR);
        strcat(cmd_str,COMPILE_TAIL);

	printf("<hr/>");
        printf("<h4>compile cmd = %s</h4>",cmd_str);
        ret = system(cmd_str);
	fd_com = fopen("compile.dat","r");
	if(!feof(fd_com))
        	printf("<h4>Compile Error</h4>");
	while(!feof(fd_com))
	{
		fgets(str_com,MAX_STRING,fd_com);
		printf("<p>%s</p>",str_com);
	}
	fclose(fd_com);
        printf("<h4>compile status = %d</h4>",ret);

	printf("<hr/>");
        ret = system(CHMOD_STR);
        printf("<h4>chmod status = %d</h4>",ret);

	printf("<hr/>");
	cmd_str[0] = '\0';
        strcat(cmd_str,RUN_STR);
        strcat(cmd_str,RUN_TAIL);
        ret = system(cmd_str);
        printf("<h4>run cmd = %s</h4>",cmd_str);
        printf("<h4>run status = %d</h4>",ret);
	fd_com = fopen("run.dat","r");
	printf("<h4>Run Time Output</h4>");
	while(!feof(fd_com))
	{
		fgets(str_com,MAX_STRING,fd_com);
		printf("<p>%s<p>",str_com);
	}
	fclose(fd_com);
	
}
