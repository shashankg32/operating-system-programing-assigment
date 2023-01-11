#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include<pthread.h>
#include<semaphore.h>

//-----producer consumer declaration----------------------------------------
int mutex = 1;
int full = 0;
int empty = 10, x = 0;
//-----producer consumer declaration----------------------------------------


//race condition declaration-------------------
int shared=1;
//race condition declaration-----------------


//convurrency declaration----------------------------------
sem_t room;
sem_t chopstick[5];
//convurrency declaration----------------------------------

//topic 1:process creation starts here-----------------------------------------------------------------------------------------------------------------------------------------------------------------
int mainn()
{
int argc,n=100;
char *argv[n];
printf("I am: %d\n", (int) getpid());
pid_t pid = fork();
printf("fork returned: %d\n", (int) pid);
if (pid < 0) 
{
perror("Fork failed");
}
if (pid == 0) 
{
printf("I am the child with pid %d\n", (int) getpid());
printf("Child process is exiting\n");
exit(0);
}
printf("I am the parent waiting for the child process to end\n");
wait(NULL);
printf("parent process is exiting\n");
return(0);
}
//topic 1:process creation ends here-------------------------------------------------------------------------------------------------------------------------------------------------------------------


//topic 2 : file handling starts here------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------
//file handling : case1
int openwriteclose()
{
FILE *filePointer ;
char dataToBeWritten[50] = "A Computer Science Student";
filePointer = fopen("Test.txt", "w") ;
if ( filePointer == NULL )
{ printf( "Test.c file failed to open." ) ; }
else{
printf("The file is now opened.\n") ;
if ( strlen ( dataToBeWritten ) > 0 )
{
fputs(dataToBeWritten, filePointer) ;
fputs("\n", filePointer) ;
}
fclose(filePointer) ;
printf("Data successfully written in file Test.c\n");
printf("The file is now closed.\n") ;
}
return 0;	
}
//----------------------------------------
//file handling : case2
int openreadclose()
{
FILE *filePointer ;
char dataToBeRead[50];
filePointer = fopen("test.txt", "r") ;
if ( filePointer == NULL )
{
printf( "test.txt file failed to open." ) ;
}
else
{
printf("The file is now opened.\n") ;
while( fgets ( dataToBeRead, 50, filePointer ) != NULL )
{
printf( "%s" , dataToBeRead ) ;
}
fclose(filePointer) ;
printf("Data successfully read from file test.txt\n");
printf("The file is now closed.") ;
}
return 0;	
}
//-------------------------------------------
//file handling : case3
int accessingdata()
{
   FILE *fp;  
   fp = fopen("myfile.txt","w+");  
   fputs("This is javatpoint", fp);
   fseek( fp, 7, SEEK_SET );  
   fputs("sonoo jaiswal", fp);  
   fclose(fp);
   printf("Please go and check the file 'myfile.txt' to see the changes\n");
}
//-------------------------------------------------
//topic 2 : file handling ends here-------------------------------------------------------------------------------------------------------------------------------------------------------------------


//topic 3 : Synchronization Problem starts here-------------------------------------------------------------------------------------------------------------------------------------------------------
void producer()
{
	--mutex;
	++full;
	--empty;
	x++;
	printf("\nProducer produces" "item %d",x);
	++mutex;
}
void consumer()
{
	--mutex;
	--full;
	++empty;
	printf("\nConsumer consumes " "item %d",x);
	x--;
	++mutex;
}
//topic 3 : Synchronization Problem ends here---------------------------------------------------------------------------------------------------------------------------------------------------------

//race condition function starts here------------------------------------------------------------------------------------------------------------------
int *fun1()
{
    int x;
    x=shared;//thread one reads value of shared variable
    printf("Thread1 reads the value of shared variable as %d\n",x);
    x++;  //thread one increments its value
    printf("Local updation by Thread1: %d\n",x);
    sleep(1);  //thread one is preempted by thread 2
    shared=x; //thread one updates the value of shared variable
    printf("Value of shared variable updated by Thread1 is: %d\n",shared);
}

void *fun2()
 {
     int y;
     y=shared;//thread two reads value of shared variable
     printf("Thread2 reads the value as %d\n",y);
     y--;  //thread two increments its value
     printf("Local updation by Thread2: %d\n",y);
     sleep(1); //thread two is preempted by thread 1
     shared=y; //thread one updates the value of shared variable
     printf("Value of shared variable updated by Thread2 is: %d\n",shared);
 }
//race condition ends here------------------------------------------------------------------------------------------------------------------


//concerrency functio start here--------------------------------------------------------
int * philosopher(void * num)
{
int phil=*(int *)num;
sem_wait(&room);
printf("\nPhilosopher %d has entered room\n",phil);
sem_wait(&chopstick[phil]);
sem_wait(&chopstick[(phil+1)%5]);
eat(phil);
sleep(2);
printf("\nPhilosopher %d has finished eating\n",phil);
sem_post(&chopstick[(phil+1)%5]);
sem_post(&chopstick[phil]);
sem_post(&room);
}

int eat(int phil)
{
printf("\nPhilosopher %d is eating\n",phil);
}
//concerrency ends here-----------------------------------------------------------------------


int main()
{//main open

int topic;
printf("Enter your choice: \n 1.Process Creation and Termination\n 2.File Handling\n 3.Synchronization Problem\n 4.IPC\n");
scanf("%d",&topic);

switch(topic)
{

//topic 1:process creation starts here-------------------------------------------------------------------------------------------------------------------------------------------------------------
case 1:
printf("Output for Process Creation and Termination\n ");
mainn();
break;
//topic 1:process creation ends here----------------------------------------------------------------------------------------------------------------------------------------------------------------



//topic 2:file handling------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
case 2:
printf("You have selected File Handling topic\n ");
printf("Enter your choice in File Handling : \n 1.To Open,Write And Close the File\n 2.To Open,Read And Close the File\n 3.Accessing Data and Print on Terminal Output\n");
int filehandlinhchoice;
scanf("%d",&filehandlinhchoice);
switch(filehandlinhchoice)
{
case 1:openwriteclose();break;
case 2:openreadclose();break;
case 3:accessingdata();break;
default:printf("Invalid choice in topic File Handling\n");break;
}
break;
//topic 2: file handling------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



//topic 3 : Synchronization----------------------------------------------------------------------------------
case 3:

printf("You have selected Synchronization Problem topic\n ");
printf("Enter your choice\n 1.Producer Consumer\n 2.Race Condition\n 3.Concurrency\n");
int synchronizationproblemchoice;
scanf("%d",&synchronizationproblemchoice);

switch(synchronizationproblemchoice)
{//switch for synchronizationproblemchoice open

case 1://producer consumer case 1 opened
printf("You have selected Producer Consumer Problem \n ");
printf("\nEnter your choice:\n 1. Press 1 for Producer" "\n2. Press 2 for Consumer" "\n3. Press 3 for Exit\n");
int n, i;
for (i = 1; i > 0; i++) 
{//for loop open
scanf("%d", &n);
switch(n)
{//switch inside for of producer consumer open
case 1: if ((mutex == 1) && (empty != 0)) { producer();} else { printf("Buffer is full!\n");} break;

case 2: if ((mutex == 1) && (full != 0)) { consumer(); } else { printf("Buffer is empty!\n");} break;

case 3: exit(0); break;
}//switch inside for of producer consumer close
}//for loop inside producer consumer close

break;//of producer consumer case 1 closed

case 2 : //race condition
//while running use -lpthread
 printf("Output for race condition\n");
 pthread_t thread1, thread2;
 pthread_create(&thread1, NULL, fun1, NULL);
 pthread_create(&thread2, NULL, fun2, NULL);
 pthread_join(thread1, NULL);
 pthread_join(thread2,NULL);
 printf("Final value of shared is %d\n",shared);
break;//race condition

case 3 : //concurrency
printf("Output for dining philosher problem in concerrency\n");
int a[5];
pthread_t tid[5];
sem_init(&room,0,4);
for(i=0;i<5;i++){sem_init(&chopstick[i],0,1);}
for(i=0;i<5;i++)
{
a[i]=i;
pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
}
for(i=0;i<5;i++){pthread_join(tid[i],NULL);}
break;//concurrency

default:
printf("Invalid Choice in Synchronization Problem\n");
break; //case 3 break of Synchronization topic
}//switch for synchronizationproblemchoice closed
//topic 3 : Synchronization----------------------------------------------------------------------------------



case 4://case 4 opend for topic selection
printf("You have selected Inter-Process Communication topic\n ");
printf("Enter your choice\n 1.IPC through Shared Memory\n 2.IPC through \n");
int ipcchoice;
scanf("%d",ipcchoice);
switch(ipcchoice)
{//ipcchoice switch  open
}//ipcchoice switch closed
break;//case 4 closed for topic selection



//default:
//printf("You have selected invalid choice\n");
//break;//break for topic switch 
}//switch of topic closed
}//main close
