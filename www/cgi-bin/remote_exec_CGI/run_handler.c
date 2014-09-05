#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATAFILE "./user_home/user_code.c"

int main() {
	FILE *fd = fopen("data","w");
    	char cmd_str[200] = "gcc -o ./user_home/a.out ";
    	int  ret;
	fprintf(fd,"you are in run_handler.cgi!\n");
   	printf("%s%c%c\n","Content-Type:text/html;charset=GB2312",13,10);
    	printf("<TITLE>Code Run Page</TITLE>\n");
    	printf("<h1>Welcom to Code Run Page</h1>\n");
        strcat(cmd_str,DATAFILE);
        printf("<p>cmd = %s</p>",cmd_str);
        ret = system(cmd_str);
        printf("<p>compile = %d</p>",ret);
        ret = system("chmod 777 ./user_home/a.out");
        printf("<p>chmod = %d</p>",ret);
        ret = system("./user_home/a.out");
        printf("<p>run = %d</p>",ret);
	
}
