#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#define MAX_STRING 2000
#define DATAFILE "./user_home/user_example.c"

static void cgiGetenv(char **s, char *var){
        *s = getenv(var);
        if (!(*s)) {
                *s = "";
        }
}
int cgiMain() {
	FILE *fd = fopen(DATAFILE,"r");
	char str_com[MAX_STRING];
	int  ret;
	char * cgiHostAddr;
    	cgiHeaderContentType("text/html");
    	fprintf(cgiOut, "<HTML><HEAD>\n");
    	fprintf(cgiOut, "<TITLE>Example View Page</TITLE>\n");
	fprintf(cgiOut, "<link rel=\"stylesheet\" href=\"../remote.css\" type=\"text/css\" /></HEAD>");
    	fprintf(cgiOut, "<BODY>");
	fprintf(cgiOut, "<h1>Welcom to Example View Page</h1>");
	fprintf(cgiOut, "<P>The Example Code Is:</p>");
	
	fprintf(cgiOut, "<pre>");
	while(!feof(fd))
	{
		fgets(str_com,MAX_STRING,fd);
		fprintf(cgiOut,"%s",str_com);
	}
	fprintf(cgiOut, "</pre>");

    	fprintf(cgiOut, "</BODY>\n");
    	fprintf(cgiOut, "</HTML>\n");
	close(fd);
    	return 0;
}
