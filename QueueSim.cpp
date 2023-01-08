#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

#include "Project2TaskNode.h"  //task data structure
#include "simpleQueueClass.h"  //Queue structure


struct customerStatus{  //server status data structure
	int custNum;
	int arrivalTime;
	int startTime;
	int waitTime;
	int serviceTime; 
	int responseTime;
};
struct simulationStats{  //simulation stats data structure
	float totCust;
	float totServiceTime;
	float totWaitTime;
	float totResponseTime;
	int maxQueueSize;
	float avgServiceTime;
	float avgWaitTime;
	float avgResponseTime;
};

customerStatus *createCustStatus();   //sets the functions
simulationStats *createSimStats();
void createCustomer(Queue *simQueue, QueueNode *node,int arriveTime, int clock, int duration, int *custNum,customerStatus *custStatus,int arrival);
void checkServerFree(Queue *simQueue, QueueNode *node,int clock, customerStatus *custStatus, int serveTime, bool *more,int serve);
void printStatus(customerStatus *custStatus, int waitTime);
void checkCustComplete(Queue *simQueue,int clock, customerStatus *custStatus, simulationStats *simStats, bool *more);
void printStats(simulationStats *simStats);


int main()
{
	int i,j,k;      //sets the variables
	int clock;
	int custNum;
	int duration;
	int arriveTime;
	int serveTime;
	bool more;
	customerStatus *custStatus;
	simulationStats *simStats;
	Queue *simQueue;
	QueueNode *node;
	srand(time(0));

	custStatus=createCustStatus(); 
	simStats=createSimStats();
	simQueue=createQueue();

	cout<<"Enter Duration of Simulation (Minutes): ";    //asks the user to enter information
	cin>>duration;  

	cout<<"Enter Average Arriving Time(Minutes): ";
	cin>>arriveTime;

	cout<<"Enter Average Servicing Time(Minutes): ";
	cin>>serveTime;

	more=true;
	custNum=0;
	clock=1;
	int taskNumber=0;
	int TaskID=0;

	while((clock<=duration) || (more==true)){     //simulation starts while increasing the clock

		cout<<"\n\t\t\tTime Point: "<<clock<<endl;
		int arrival=1+rand() % arriveTime; //sets random numbers
		int serve=1+rand() % serveTime;
		
		if(clock<=7200)  //calls the functions
			createCustomer(simQueue,node,arriveTime, clock, duration, &custNum,custStatus,arrival);
		checkServerFree(simQueue,node,clock,custStatus,serveTime,&more,serve);
		checkCustComplete(simQueue,clock,custStatus,simStats,&more);

		if(!simQueue->isEmptyQueue()) //if the Queue has more, continue
			more=true;
		
		clock+=1;
	}

	printStats(simStats);  //prints the final stats

	return 0;
}
void createCustomer(Queue *simQueue, QueueNode *node,int arriveTime, int clock, int duration, int *custNum,customerStatus *custStatus,int arrival) //new task 
{
	int TaskID;
	int taskNumber;
	if(arrival==arriveTime)  //if random number =average arriving time
	{
		TaskID=TaskID+1;
		custStatus->custNum++;
		taskNumber=custStatus->custNum;
		node=createNode(taskNumber,clock);  //creates node then sets varaibles
		node->setCustNum(taskNumber);
		node->setArrivalTime(clock);
		simQueue->enqueue(node);     //adds it to the queue
	}

}
void checkServerFree(Queue *simQueue, QueueNode *node, int clock, customerStatus *custStatus, int serveTime, bool *more,int serve) //check server status
{
	if(clock>(custStatus->startTime)+(custStatus->serviceTime)-1)  //if server is idle
	{
		if(!simQueue->isEmptyQueue())  //if queue is not empty
		{
		node=simQueue->dequeue();     //dequeue the node
		custStatus->custNum=node->getCustNum();        //sets all the variables in the customerStatus structure
		custStatus->arrivalTime=node->getArrivalTime();
		custStatus->startTime=clock;
		custStatus->serviceTime=serve;
		custStatus->waitTime=custStatus->startTime-custStatus->arrivalTime;
		custStatus->responseTime=custStatus->waitTime+custStatus->serviceTime;
		*more=true;
		}
	}

}
void printStatus(customerStatus *custStatus, int waitTime)
{
	cout<<"Current Task Number: "<<custStatus->custNum<<endl;      //prints the current variables in the customerStatus structure
	cout<<"Task Arrival Time  : "<<custStatus->arrivalTime<<endl;
	cout<<"Task Start Time    : "<<custStatus->startTime<<endl;
	cout<<"Task Service Time  : "<<custStatus->serviceTime<<endl;
	cout<<"Task Wait Time     : "<<custStatus->waitTime<<endl;
	cout<<"Task Response Time : "<<custStatus->responseTime<<endl;

}
void checkCustComplete(Queue *simQueue,int clock, customerStatus *custStatus, simulationStats *simStats, bool *more) //check task
{
	if(clock==(custStatus->startTime+custStatus->serviceTime)-1)
	{
		custStatus->waitTime=custStatus->startTime-custStatus->arrivalTime;
		simStats->totCust=simStats->totCust+1;	  
		simStats->totServiceTime=simStats->totServiceTime+custStatus->serviceTime;   //sets variables in simulationStats structure
		simStats->totWaitTime=simStats->totWaitTime+custStatus->waitTime;
		simStats->totResponseTime=simStats->totResponseTime+custStatus->responseTime;
	
		//queueSize=queue.Size()??
		if(simStats->maxQueueSize<simQueue->getQueueSize())
			simStats->maxQueueSize=simQueue->getQueueSize();
		printStatus(custStatus,custStatus->waitTime);    //prints the current variables
		*more=false;
	}

}
void printStats(simulationStats *simStats)
{
	simStats->avgServiceTime=float(simStats->totServiceTime/simStats->totCust);   //sets the averages
	simStats->avgWaitTime=float(simStats->totWaitTime/simStats->totCust);
	simStats->avgResponseTime=float(simStats->avgWaitTime+simStats->avgServiceTime);
	cout<<"\n\n";
	cout<<"------------------------------------"<<endl;         //prints the final stats of simulation
	cout<<"Printing Queue Simulation Statistics"<<endl;
	cout<<"------------------------------------"<<endl;
	cout<<"Total Number of Customers: "<<int(simStats->totCust)<<endl;
	cout<<"Total Service Time       : "<<int(simStats->totServiceTime)<<endl;
	cout<<"Total Wait  Time         : "<<int(simStats->totWaitTime)<<endl;      
	cout<<"Total Response  Time     : "<<int(simStats->totResponseTime)<<endl;     
	cout<<"Average Service Time     : "<<simStats->avgServiceTime<<endl;
	cout<<"Average Wait Time        : "<<simStats->avgWaitTime<<endl;
	cout<<"Average Response Time    : "<<simStats->avgResponseTime<<endl;
	cout<<"Maximum Queue Size       : "<<simStats->maxQueueSize<<endl;

}
simulationStats *createSimStats()     //create queue
{
	simulationStats *queue1;
	try{
		queue1 = new simulationStats();	
	}
	catch(bad_alloc){
		cout << "\n\n\t\t\tYikes! Out of memory!!!\n";
		queue1 = nullptr;
	}
	
	return queue1;
}

customerStatus *createCustStatus()   //create queue
{
	customerStatus *queue2;
	try{
		queue2 = new customerStatus();	
	}
	catch(bad_alloc){
		cout << "\n\n\t\t\tYikes! Out of memory!!!\n";
		queue2 = nullptr;
	}
	
	return queue2;
}

