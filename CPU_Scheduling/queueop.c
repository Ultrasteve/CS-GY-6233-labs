#include <stdlib.h>
#include "iolabs.h"
#include "queueop.h"

int isPCBNULL(struct PCB process) {
    return process.process_id == 0 && process.arrival_timestamp == 0 && process.total_bursttime == 0 && process.execution_starttime == 0 && process.execution_endtime == 0 && process.process_priority == 0 && process.remaining_bursttime == 0;
}

struct PCB removeIthItem(struct PCB ready_queue[QUEUEMAX], int i, int *queue_cnt);

void enqueue(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB process) {
    if(*queue_cnt == QUEUEMAX) {
        printf("Queue full\n");
        return;
    }
    // ready_queue[*queue_cnt].process_id = process.process_id;
    // ready_queue[*queue_cnt].arrival_timestamp = process.arrival_timestamp;
    // ready_queue[*queue_cnt].total_bursttime = process.total_bursttime;
    // ready_queue[*queue_cnt].execution_starttime = process.execution_starttime;
    // ready_queue[*queue_cnt].execution_endtime = process.execution_endtime;
    // ready_queue[*queue_cnt].remaining_bursttime = process.remaining_bursttime;
    // ready_queue[*queue_cnt].process_priority = process.process_priority;
    ready_queue[*queue_cnt] = process;
    *queue_cnt += 1;
}

struct PCB takeHighestPriority(struct PCB ready_queue[QUEUEMAX], int *queue_cnt) {
    if(*queue_cnt == 0) {
        printf("Queue empty\n");
        struct PCB nullpcb = {0,0,0,0,0,0,0};
        return nullpcb;
    }
    int minIndex = 0;
    for(int i = 1; i < *queue_cnt; i++) {
        struct PCB now = ready_queue[i];
        if(now.process_priority < ready_queue[minIndex].process_priority)
            minIndex = i;
    }
    *queue_cnt -= 1;
    
    return removeIthItem(ready_queue, minIndex, queue_cnt);
}

struct PCB takeSmallestBurstTime(struct PCB ready_queue[QUEUEMAX], int *queue_cnt) {
    if(*queue_cnt == 0) {
        printf("Queue empty\n");
        struct PCB nullpcb = {0,0,0,0,0,0,0};
        return nullpcb;
    }
    int minIndex = 0;
    for(int i = 1; i < *queue_cnt; i++) {
        struct PCB now = ready_queue[i];
        if(now.remaining_bursttime < ready_queue[minIndex].remaining_bursttime)
            minIndex = i;
    }
    *queue_cnt -= 1;
    return removeIthItem(ready_queue, minIndex, queue_cnt);
}

struct PCB takeEarlistTime(struct PCB ready_queue[QUEUEMAX], int *queue_cnt) {
    if(*queue_cnt == 0) {
        printf("Queue empty\n");
        struct PCB nullpcb = {0,0,0,0,0,0,0};
        return nullpcb;
    }
    int minIndex = 0;
    for(int i = 1; i < *queue_cnt; i++) {
        struct PCB now = ready_queue[i];
        if(now.arrival_timestamp < ready_queue[minIndex].arrival_timestamp)
            minIndex = i;
    }
    *queue_cnt -= 1;
    return removeIthItem(ready_queue, minIndex, queue_cnt);
}

//remove the item in the queue and return a copy of the removed item
struct PCB removeIthItem(struct PCB ready_queue[QUEUEMAX], int i, int *queue_cnt) {
    //copy
    struct PCB p;
    p.process_id = ready_queue[i].process_id;
    p.arrival_timestamp = ready_queue[i].arrival_timestamp;
    p.total_bursttime = ready_queue[i].total_bursttime;
    p.execution_starttime = ready_queue[i].execution_starttime;
    p.execution_endtime = ready_queue[i].execution_endtime;
    p.remaining_bursttime = ready_queue[i].remaining_bursttime;
    p.process_priority = ready_queue[i].process_priority;
    //remove
    for(int j = i + 1; j < *queue_cnt + 1; j++) {
        ready_queue[j - 1].process_id = ready_queue[j].process_id;
        ready_queue[j - 1].arrival_timestamp = ready_queue[j].arrival_timestamp;
        ready_queue[j - 1].total_bursttime = ready_queue[j].total_bursttime;
        ready_queue[j - 1].execution_starttime = ready_queue[j].execution_starttime;
        ready_queue[j - 1].execution_endtime = ready_queue[j].execution_endtime;
        ready_queue[j - 1].remaining_bursttime = ready_queue[j].remaining_bursttime;
        ready_queue[j - 1].process_priority = ready_queue[j].process_priority;
    }
    return p;
}
