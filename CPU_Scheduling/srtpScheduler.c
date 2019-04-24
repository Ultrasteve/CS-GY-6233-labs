#include "iolabs.h"
#include "queueop.h"

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp) {
    //if no current process
    if(isPCBNULL(current_process)) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }

    //new_process do not have shorter remain time
    if(current_process.remaining_bursttime <= new_process.total_bursttime) {
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        enqueue(ready_queue, queue_cnt, new_process);
        return current_process;
    }
    else {
        //modify new process info
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        //modify current process info
        current_process.remaining_bursttime -= (timestamp - current_process.execution_starttime);
        current_process.execution_starttime = 0;
        current_process.execution_endtime = 0;
        enqueue(ready_queue, queue_cnt, current_process);
        return new_process;
    }
}

struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {
    if(queue_cnt == 0) {
        struct PCB nullpcb = {0,0,0,0,0,0,0};
        return nullpcb;
    }
    struct PCB nextProcess = takeSmallestBurstTime(ready_queue, queue_cnt);
    nextProcess.execution_starttime = timestamp;
    nextProcess.execution_endtime = timestamp + nextProcess.remaining_bursttime;
    return nextProcess;
}

