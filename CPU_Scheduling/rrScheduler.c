#include "iolabs.h"
#include "queueop.h"

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum) {
    //if no current process
    if(isPCBNULL(current_process)) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + (new_process.total_bursttime > time_quantum ? time_quantum : new_process.total_bursttime);
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }
    new_process.execution_starttime = 0;
    new_process.execution_endtime = 0;
    new_process.remaining_bursttime = new_process.total_bursttime;
    enqueue(ready_queue, queue_cnt, new_process);

    return current_process;
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum) {
    if(queue_cnt == 0) {
        struct PCB nullpcb = {0,0,0,0,0,0,0};
        return nullpcb;
    }
    struct PCB nextProcess = takeEarlistTime(ready_queue, queue_cnt);
    nextProcess.execution_starttime = timestamp;
    nextProcess.execution_endtime = timestamp + (nextProcess.remaining_bursttime > time_quantum ? time_quantum : nextProcess.remaining_bursttime);
    return nextProcess;
}

