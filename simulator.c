#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "insoutput.c"
#include <time.h>
#include "creatingreadyqueue.c"

int choice;

pthread_mutex_t var; //mutex variable
FILE *f;//file pointer of log file

int checkthread[5];//variable checks if thread is completed or not
int times[4]={0};
int turn=0;

int StartNext(int tid)     //choose the next thread to run
{

    int i=tid;
    for(i = (tid + 1) % 4; times[i] == 0; i = (i + 1) % 4)
    {
        if(i == tid)    //if every thread has finished
	    return;
    } 

     turn = i;
  
}

void *Run(void *tid)    //thread function
{
	  int insno=1;
    int i = (int)tid;
    int output;
    char arr[50];
    char line[BUFSIZ];
    FILE *fp;
    int status;
    time_t start=time(0);
    double timetaken,waiting_time;

    fp=fopen(ready_queue[i].process_name,"r");

	    	while(times[i]!=0)
	    	{
    	    		while(turn!=i);
    	    		if(times[i]>=1)
    	    		{
    	    			
                fgets(line,sizeof(line),fp);
      	    		output=parser(line);
      					printf("output of process%d of %s is %d\n",insno,ready_queue[i].process_name,output);
      					insno++;

      					sleep(1);
                  times[i]-=1;
      					
    	    		}

    	    		 StartNext(i);
         
	    	}
        if(times[i]==0)
        {
          time_t end=time(0);
          timetaken=difftime(end, start);//time spend for arithmatic operations in parser file
          waiting_time=difftime(start,ready_queue[i].arr_time_stamp);//waitingtime=time spent after arriving till going inside parser for execution
          f = fopen("logs_rr","a");//generating logs file
          fprintf(f ,"%s process's  Arrival Time : %lf Waiting Time:%lf  cpu_burst_time : %lf \n " ,ready_queue[i].process_name,ready_queue[i].arr_time,waiting_time,timetaken);
          fclose(f);   
          printf("%s is completed\n",ready_queue[i].process_name);

        }

    pthread_exit(0);


}

void * threadfunc ( void * par )
{
	struct pcb* pcb1 =  (struct pcb *)par;
		char arr[20];

		strcpy(arr,pcb1->process_name);


	if(choice==2)
	{
		checkthread[(pcb1->process_id)-1]=0;//11
	    pause();//11
	}

	FILE *fp;
	int count=0;
	char c;
	fp=fopen(arr,"r");

	int insno= 1;
	char line[BUFSIZ];
	int output;
	double timetaken,waiting_time;//11
	sleep(1);//for waiting time
	time_t start=time(0);
	//giving instruction to the parser file
	while(fgets(line,sizeof(line),fp))
	{

		output=parser(line);
		printf("output of process%d of %s is %d\n",insno,arr,output);
		insno++;
		sleep(1);//takes 1 sec to complete each instruction

	}

	time_t end=time(0);
	fclose(fp);
	timetaken=difftime(end, start);//time spend for arithmatic operations in parser file
	waiting_time=difftime(start,pcb1->arr_time_stamp)-4;//waitingtime=time spent after arriving till going inside parser for execution

	switch(choice)
	{

	         case 1:
	         {
	            
	            f = fopen("logs_fcfs","a");
				fprintf(f , " %s process's   Arrival Time : %lf   Waiting Time : %lf   cpu_burst_time : %lf \n " , arr , pcb1->arr_time,waiting_time,timetaken);
				fclose(f);

				pthread_mutex_unlock(&var); //applying unlock
				printf("%s is completed\n",arr);
				pthread_exit(NULL);

	            break;
	         }
	         
	        case 3:
	         {
	            f = fopen("logs_sjf","a");
				fprintf(f,"%s process's  Arrival Time:%lf Waiting Time:%lf cpu_burst_time:%lf\n" ,arr,pcb1->arr_time,waiting_time,timetaken);
				fclose(f);
				pthread_mutex_unlock(&var); //applying unlock
				printf("%s is completed\n",arr);
				pthread_exit(NULL);
	            break;
	         }

	         case 4:
	         {
	            f = fopen("logs_priority","a");
				fprintf(f , " %s process's Priority:%d  Arrival Time : %lf   Waiting Time : %lf   cpu_burst_time: %lf \n " , arr ,pcb1->priority, pcb1->arr_time,waiting_time,timetaken);
				fclose(f);
				pthread_mutex_unlock(&var); //applying unlock
				printf("%s is completed\n",arr);
				pthread_exit(NULL);
	            break;
	         } 
	       
	}

}


int main(){

    
    printf("........................MENU..........................\n");
    printf("......................1.FCFS..........................\n");
    printf("...................2.ROUND ROBIN......................\n");
    printf("................3.SHORTEST JOB FIRST..................\n");
    printf("..................4.PRIORITY VISE.....................\n");
    printf("ENTER YOUR CHOICE\n");
    scanf("%d",&choice);

    
    switch(choice)
    {

         case 1:
         {
            creatingprocess();//creates pcb of each process from 'programs' folder 

			int maxthread = total_files;
			pthread_t threads[maxthread];//array of threads
			pthread_mutex_init(&var,NULL);//initialize mutex 
			
			struct pcb fcfs_array[10];//array of processes according to fcfs
			
			double temp;
			char tempname[20];
			int pos;
			int tempid;
			int status;
			
			//copying ready_queue to fcfs array for sorting
			memcpy(&fcfs_array,&ready_queue,sizeof(ready_queue));
			
			//sorting
			for(int i=0;i<total_files;i++)
		    {
		        pos=i;
		        for(int j=i+1;j<total_files;j++)
		        {
		            if(fcfs_array[j].arr_time<fcfs_array[pos].arr_time)
		                pos=j;
		        }
		 
		        temp=fcfs_array[i].arr_time;
		        fcfs_array[i].arr_time=fcfs_array[pos].arr_time;
		        fcfs_array[pos].arr_time=temp;
		 
		        tempid=fcfs_array[i].process_id;
		        fcfs_array[i].process_id=fcfs_array[pos].process_id;
		        fcfs_array[pos].process_id=tempid;
				

				strcpy(tempname,fcfs_array[i].process_name);
				strcpy(fcfs_array[i].process_name,fcfs_array[pos].process_name);
				strcpy(fcfs_array[pos].process_name,tempname);
				
		    }
			

		   //creating threads of each process taken from 'programs' folder	
			for(int i=0;i<maxthread;i++)
			{
		          status = pthread_create(&threads[i], NULL, threadfunc,    (void *) &fcfs_array[i] );
				//error handling
		          if (status != 0)
		            {
		              printf("error in creating threads");
		              exit(1);
		            }
				pthread_join(threads[i], NULL);
			}
	

            break;
         }
         
         case 2:
         {
           	
			    creatingprocess();

			    int ins[4]={0};
			    pthread_t threads[4];
			    
			    int i, status;
			    char arr[50];
			    char line[BUFSIZ];
			    char *b;
			   
				for(i=0;i<4;i++)
				{
					strcpy(arr,ready_queue[i].process_name);
					 FILE *fp;
				    fp=fopen(arr,"r");
				    while(fgets(line,sizeof(line),fp))
				    {
				    	ins[i]++;

				    }
			      fclose(fp);
				}
			   
			    for(i=0;i<4;i++)
				{
					
				    	times[i] =ins[i];
				    
				}
			 
				for(i = 0; i < 4; i++)
			     {
			            status = pthread_create(&threads[i], NULL, Run, (void *)i);    //Create threads
			            if(status != 0)
			            {
			                printf("While creating thread %d, pthread_create returned error code %d\n", i, status);
			                exit(-1);
			            }
			               
			     }
			     for(i=0;i<4;i++)
			           pthread_join(threads[i], 0);
					 
            break;
         }

         case 3:
         {
            
            creatingprocess();//creates pcb of each process from 'programs' folder 
			struct pcb sjf_array[10];//array of processes according to sjf
				
			
			double temp;
			char tempname[50];
			int pos;
			int status;
		    int maxthread = total_files;
		    pthread_mutex_init(&var,NULL);//initialize mutex
		    pthread_t threads[maxthread];//array of threads

		    memcpy(&sjf_array,&ready_queue,sizeof(ready_queue));
			
			//sorting sjf array according to cpu_burst_time time
			for(int i=0;i<total_files;i++)
		    {
		        pos=i;
		        for(int j=i+1;j<total_files;j++)
		        {
		            if(sjf_array[j].cpu_burst_time<sjf_array[pos].cpu_burst_time)
		                pos=j;
		        }
		 
		        temp=sjf_array[i].cpu_burst_time;
		        sjf_array[i].cpu_burst_time=sjf_array[pos].cpu_burst_time;
		        sjf_array[pos].cpu_burst_time=temp;
		 
		        temp=sjf_array[i].process_id;
		        sjf_array[i].process_id=sjf_array[pos].process_id;
		        sjf_array[pos].process_id=temp;
				
				
				strcpy(tempname,sjf_array[i].process_name);
				strcpy(sjf_array[i].process_name,sjf_array[pos].process_name);
		        strcpy(sjf_array[pos].process_name,tempname);
				
		    }
			
			//creating threads of each process taken from 'programs' folder
			for(int i=0;i<total_files;i++)
			{
			 status = pthread_create(&threads[i], NULL, threadfunc,    (void *) &sjf_array[i]);
				//error handling
		          if (status != 0)
		            {
		              printf("error in creating thread");
		              exit(1);
		            }
				pthread_join(threads[i], NULL);
			}	
		 
					

            break;
         }

         case 4:
         {
            
            creatingprocess();//creates pcb of each process from 'programs' folder 
			int maxthread = total_files;
		    pthread_t threads[maxthread];//array of threads
		    pthread_mutex_init(&var,NULL);//initialize mutex
			
			struct pcb priority_array[10];//array of processes according to priority
			
			int temp;
			double temparrival;
			int tempid;
			char tempname[20];
			int pos;
			int status;
				//copying ready_queue to priority array for sorting
			memcpy(&priority_array,&ready_queue,sizeof(ready_queue));
			//sorting
			for(int i=0;i<total_files;i++)
		    {
		        pos=i;
		        for(int j=i+1;j<total_files;j++)
		        {
		            if(priority_array[j].priority<priority_array[pos].priority)
		                pos=j;
		        }
		 
		        temp=priority_array[i].priority;
		        priority_array[i].priority=priority_array[pos].priority;
		        priority_array[pos].priority=temp;
		 
				temparrival=priority_array[i].arr_time;
		        priority_array[i].arr_time=priority_array[pos].arr_time;
		        priority_array[pos].arr_time=temparrival;
				
		        tempid=priority_array[i].process_id;
		        priority_array[i].process_id=priority_array[pos].process_id;
		        priority_array[pos].process_id=tempid;
				
					strcpy(tempname,priority_array[i].process_name);
				strcpy(priority_array[i].process_name,priority_array[pos].process_name);
				strcpy(priority_array[pos].process_name,tempname);
				
		    }
			
		//creating threads of each process taken from 'programs' folder	

			for(int i=0;i<maxthread;i++)
			{
		          status = pthread_create(&threads[i], NULL, threadfunc,    (void *) &priority_array[i] );
				//error handling
		          if (status != 0)
		            {
		              printf("error in creating threads");
		              exit(1);
		            }
				pthread_join(threads[i], NULL);
			} 

            break;
         } 
       



    }

   return 0;

}
