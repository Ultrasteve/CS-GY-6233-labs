void enqueue(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB process);
struct PCB takeHighestPriority(struct PCB ready_queue[QUEUEMAX], int *queue_cnt);
struct PCB takeSmallestBurstTime(struct PCB ready_queue[QUEUEMAX], int *queue_cnt);
struct PCB takeEarlistTime(struct PCB ready_queue[QUEUEMAX], int *queue_cnt);
int isPCBNULL(struct PCB process);
