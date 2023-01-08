
class Queue{
	private:
		int count;
		QueueNode *front;
		QueueNode *rear;
	public:

		Queue();
		~Queue(){deleteAllQueue();};
		void enqueue(QueueNode *node);
		QueueNode *dequeue();
		void traverseQueue();
		void deleteAllQueue();
		bool isEmptyQueue();
		int getQueueSize();
		QueueNode *queueFront();
		QueueNode *queueRear();
};

Queue::Queue()
{
	count = 0;
	front   = nullptr;
}

QueueNode *Queue::queueFront()
{
	return front;
}

QueueNode *Queue::queueRear()
{
	return rear;
}

int Queue::getQueueSize()
{
	return count;
}

bool Queue::isEmptyQueue()
{
	return front == nullptr;
}

void Queue::enqueue(QueueNode *node)
{
	//QueueNode *current;

	cout << "\n\t\t\tInserting New Node into Queue ....";

	//Inserting into empty queue:
	if(front == nullptr){
		front = node;
		rear = node;

	}
	else{	//Inserting into non-empty queue:

		rear->setNext(node);
		rear = node;	
	}

	count += 1;

	cout << "\n\t\t\tNumber of Items in Queue: " << count <<endl;

	return;

}

void Queue::deleteAllQueue()
{
	QueueNode *node;

	cout << "\n\n\t\t\tDeleting All Items in Queue ....";

	while(count > 0){
		
		node = front;
		front = node->getNext();
		cout <<"\n\t\t\tDeleting Node: \n";
		node->printInfo();

		delete node;
		count--;

		cout << "\n\t\t\tNumber of Remaining Items is: " << count << "\n\n";
	}

	cout << "\n\n";

	return;

}

QueueNode *Queue::dequeue()
{
	QueueNode *node;
	QueueNode *prev;

	if(count > 0){
		cout << "\n\t\t\tDequeuing Node ...\n";
		
		node = front;
		front  = node->getNext();

		count--;

		cout << "\n\t\t\tNumber of Remaining Items is: " << count << "\n\n";
	}
	else{
		cout << "\n\t\t\tQueue is Empty..." <<endl;	
		node = nullptr;
	}

	return node;
}

void Queue::traverseQueue()
{
        QueueNode *node;

        cout << "\n\n\t\t\tTraversing Queue ....";

        node = front;
        while(node != nullptr){

                node->printInfo();
                node = node->getNext();
        }

        cout << "\n\n";

        return;
}


Queue *createQueue()
{
	Queue *queue;

	queue = new Queue();
	
	return queue;
}

void destroyQueue(Queue *queue)
{
	if(queue != nullptr){

		if(queue->getQueueSize() >0){
			cout << "\n\n\t\t\tFailure: Attempting to delete a non-empty queue\n\n";
		}
		else{
			delete queue;
			queue = nullptr;
			cout << "\n\n\t\t\tQueue Successfully Deleted\n\n";
		}
	}
	
	return;	
}

