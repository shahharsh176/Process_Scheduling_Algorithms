#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include<time.h>
#include<unistd.h>

static int myCompare (const void * a, const void * b)
{
    return strcmp (*(const char **) a, *(const char **) b);
}
 
void sort(const char *arr[], int n)
{
    qsort (arr, n, sizeof (const char *), myCompare);
}

//structure of process control block
struct pcb{

	int process_id;
	char process_name[50];
    double arr_time;
	time_t arr_time_stamp;
    double cpu_burst_time;
    double waiting_time;
    double turnaround_time;
    double response_time;
    double lastresponse_time;
	int priority;
};

struct pcb ready_queue[10];   //ready queue which have pcb of all process


int total_files=0;

//main function which creates process
void creatingprocess()
{
	//taking runnable program files from programs directory
	srand(time(0));//s.3eed for random function (current time in sec.).
	time_t t=time(0);//current time
	struct dirent *Dir;//point all file in directry  (store length of the record , name , file type , file number)
	char pname[10][50]; //array for storing name of programs
	const char *temp[4];
	char  folder[]="processes/";
	  DIR *fd;// pointer to directry
	fd=opendir("processes");// open programs directry

  while ((Dir = readdir(fd)) != NULL) {
  if (!strcmp(Dir->d_name, ".") || !strcmp(Dir->d_name, ".."))
    continue;    /* skip self and parent */
	   //char  folder[]="programs/";
	  temp[total_files] = Dir->d_name;
	 // strcat(folder,Dir->d_name);
	  //strcpy(pname[total_files],folder);
	 total_files++;
  }
  closedir(fd);
  sort(temp,total_files);
  for(int i=0;i<total_files;i++)
  {
	//printf("%s\n",temp[i]);
	
char  folder[]="processes/";
	strcat(folder,temp[i]);
	strcpy(pname[i],folder);

  }
FILE *f1;
	double count=0;
	char c;

//making pcb(part of processimage) for each program inserting all pcb fields
    for(int i=0;i<total_files;i++)
    {
        sleep(1);//for arriving time
        printf("%s enters in readyqueue\n",pname[i]);
        ready_queue[i].process_id=(i+1);
        strcpy(ready_queue[i].process_name,pname[i]);
        ready_queue[i].arr_time=difftime(time(0),t);
        ready_queue[i].arr_time_stamp=time(0);
        ready_queue[i].priority=rand() % 10;
        f1=fopen(pname[i],"r");
        for (c = getc(f1); c != EOF; c = getc(f1))
        {
            if (c == '\n')
                count = count + 1;
        }
            ready_queue[i].cpu_burst_time=count;
            fclose(f1);
            count=0;
        printf("Process id: %d, Process name:%s\n",ready_queue[i].process_id,ready_queue[i].process_name);
        printf("Arrival time of this Process:%lf\n",ready_queue[i].arr_time);
        printf("Priority of this Process: %d\n",ready_queue[i].priority);
        printf("CPU burst time of this Process:%lf\n",ready_queue[i].cpu_burst_time);
        printf("\n");

    }

}
