class QueueNode{
	private:
		int custNum;
		int arrivalTime;
		QueueNode *next;
		
	public:
		QueueNode(){custNum=0;arrivalTime=0;}
		QueueNode(int num,int arriv,QueueNode * n){custNum=num,arrivalTime=arriv;next = n;}
		void setNext(QueueNode *n){next = n;}
		void setCustNum(int num){custNum=num;}
		void setArrivalTime(int arriv){arrivalTime=arriv;}

		QueueNode *getNext(){return next;}
		int getCustNum(){return custNum;}
		int getArrivalTime(){return arrivalTime;}
		int getKey(){return custNum;}
		void printInfo();
};

void QueueNode::printInfo()
{
	cout << fixed << setprecision(2) << showpoint;
//	cout << "\n\n\t\t\tQueueNode CustNum            : " << custNum<< endl;
	cout << "\t\t\tQueueNode ArrivalTime        : " << arrivalTime<< endl;
	cout << "\t\t\tQueueNode Link Address       : " << next << endl;
}

QueueNode *createNode(int custNum,int arrivalTime)
{
        QueueNode *node;

        try{
                node = new QueueNode(custNum,arrivalTime,nullptr);
                node->printInfo();
        }
        catch(bad_alloc){
                cout << "\n\n\t\t\tYikes! Out of memory!!!\n";
                node = nullptr;
        }

        return node;
}

