#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



int parser(char arr[])
{

char *ch;
	char *splitarray[3];
	int i=0;
	ch=strtok(arr," ");
	while (ch != NULL) {
 	 
		splitarray[i]=ch;
	 ch=strtok(NULL," ");
		i++;
	}
	char operator[4];
	
strcpy(operator,splitarray[0]);
	
int value1=atoi(splitarray[1]);
int value2=atoi(splitarray[2]);
int output;

if(strcmp(operator,"Add")==0)
{
	output=value1+value2;

}
else if(strcmp(operator,"Sub")==0)
{
	output=value1-value2;
}
else if(strcmp(operator,"Mov")==0)
{
	value1=value2;
	output=value1;

}
else if(strcmp(operator,"Mul")==0)
{
	output=value1*value2;

}
else if(strcmp(operator,"Div")==0)
{
	output=value1/value2;

}
else if(strcmp(operator,"Mod")==0)
{
	output=value1%value2;
}
	
	return output;
}
