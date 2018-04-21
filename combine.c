#include<stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main()
{
    int n,burst[500],burst_fcfs[500],wait_fcfs[500];
    int turn_around_fcfs[500],avg_wait_fcfs=0,avg_turn_around_fcfs=0,i,j;
    int burst_sjf[500],p[500],wait_sjf[500];
    int turn_around_sjf[500],total=0,pos,temp,avg_wait_sjf,avg_turn_around_sjf;
    int burst_pr[500],pn[500],wait_pr[500];
    int turn_around_pr[500],pr[500],total_pr=0,pos_pr,temp_pr,avg_wait_pr,avg_turn_around_pr;
    int count,time_rr,remain,flag=0,time_slice;
    int wait_time=0,turnaround_time=0,at[500],burst_rr[500],rt[500]; 

    printf("\nEnter the total number of processes: ");
    scanf("%d",&n);
    remain = n;
    srand(time(NULL));
    for(i=0;i<n;i++)
    {
      pr[i] = rand() % 100;
      burst[i] = rand() % 100;
      burst_fcfs[i] = burst[i];
      burst_sjf[i] = burst[i];
      burst_pr[i] = burst[i];
      burst_rr[i] = burst[i];
      rt[i] = burst[i];
      at[i] = 0;
      p[i]=i+1; 
      pn[i]=i+1;                             
    }
      printf("\nEnter Time Quantum: "); 
        scanf("%d",&time_slice); 


    wait_fcfs[0]=0;                           
    for(i=1;i<n;i++)                        
    {
        wait_fcfs[i]=0;
        for(j=0;j<i;j++)
            wait_fcfs[i]+=burst_fcfs[j];
    }
    printf("\n-----------------------FCFS---------------------------");
    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)                       
    {
        turn_around_fcfs[i]=burst[i]+wait_fcfs[i];
        avg_wait_fcfs+=wait_fcfs[i];
        avg_turn_around_fcfs+=turn_around_fcfs[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,burst_fcfs[i],wait_fcfs[i],turn_around_fcfs[i]);
    }
    
    avg_wait_fcfs/=i;
    avg_turn_around_fcfs/=i;
    printf("\n\nAverage Waiting Time:%d",avg_wait_fcfs);
    printf("\nAverage Turnaround Time:%d\n",avg_turn_around_fcfs);
    
    printf("------------------------------------------------------");
 



    for(i=0;i<n;i++)                            
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(burst_sjf[j]<burst_sjf[pos])
                pos=j;
        }
        temp=burst_sjf[i];
        burst_sjf[i]=burst_sjf[pos];
        burst_sjf[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
    wait_sjf[0]=0;                                 
    for(i=1;i<n;i++)                           
    {
        wait_sjf[i]=0;
        for(j=0;j<i;j++)
            wait_sjf[i]+=burst_sjf[j];
 
        total+=wait_sjf[i];
    }
    avg_wait_sjf=(float)total/n;                          
    total=0;
    printf("\n\n---------------------------SJF-----------------------");
    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        turn_around_sjf[i]=burst_sjf[i]+wait_sjf[i];                    
        total+=turn_around_sjf[i];
        printf("\np[%d]\t\t%d\t\t%d\t\t%d",p[i],burst_sjf[i],wait_sjf[i],turn_around_sjf[i]);
    }
    
    avg_turn_around_sjf=(float)total/n;                         
    printf("\n\nAverage Waiting Time=%d",avg_wait_sjf);
    printf("\nAverage Turnaround Time=%d\n",avg_turn_around_sjf);
    printf("------------------------------------------------------");



    for(i=0;i<n;i++)                
    {
        pos_pr=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos_pr])
                pos_pr=j;
        }
 
        temp_pr=pr[i];
        pr[i]=pr[pos_pr];
        pr[pos_pr]=temp_pr;
 
        temp_pr=burst_pr[i];
        burst_pr[i]=burst_pr[pos_pr];
        burst_pr[pos_pr]=temp_pr;
 
        temp_pr=pn[i];
        pn[i]=pn[pos_pr];
        pn[pos_pr]=temp_pr;
    }
 
    wait_pr[0]=0;    
 
    for(i=1;i<n;i++)
    {
        wait_pr[i]=0;
        for(j=0;j<i;j++)
            wait_pr[i]+=burst_pr[j];
 
        total_pr+=wait_pr[i];
    }
 
    avg_wait_pr=total_pr/n;      
    total_pr=0;
    printf("\n\n-----------------------Priority---------------------------");
    printf("\nProcess\t\tPriority\tBurst Time\tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        turn_around_pr[i]=burst_pr[i]+wait_pr[i];     
        total_pr+=turn_around_pr[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d\t\t%d",pn[i],pr[i],burst_pr[i],wait_pr[i],turn_around_pr[i]);
    }
     
    avg_turn_around_pr=total_pr/n;     
    printf("\n\nAverage Waiting Time=%d",avg_wait_pr);
    printf("\nAverage Turnaround Time=%d\n",avg_turn_around_pr);
    printf("------------------------------------------------------\n");


  printf("\n-----------------------RR---------------------------");
  printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n"); 
  for(time_rr=0,i=0;remain!=0;) 
  { 
    if(rt[i]<=time_slice && rt[i]>0) 
    { 
      time_rr+=rt[i]; 
      rt[i]=0; 
      flag=1; 
    } 
    else if(rt[i]>0) 
    { 
      rt[i]-=time_slice; 
      time_rr+=time_slice; 
    } 
    if(rt[i]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t\t%d\t\t%d\t\t%d\n",i+1,burst_rr[i],time_rr-at[i]-burst_rr[i],time_rr-at[i]); 
      wait_time+=time_rr-at[i]-burst_rr[i]; 
      turnaround_time+=time_rr-at[i]; 
      flag=0; 
    } 
    if(i==n-1) 
      i=0; 
    else if(at[i+1]<=time_rr) 
      i++; 
    else 
      i=0; 
  }
    
  printf("\nAverage Waiting Time= %d\n",wait_time/n); 
  printf("Avg Turnaround Time = %d",turnaround_time/n);  
  printf("\n------------------------------------------------------\n");
  return 0; 
}