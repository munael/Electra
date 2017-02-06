/**
    Authored by:
    Muhammad Nael ElNokrashy
    , Yasmin ElDokany

    For Micro Controllers course-work
    Dr Mohamed Shalan
    American University in Cairo, 2017
*/

#pragma once

#include "common.h"

typedef void(*VoidFn)();

#ifndef TASKS_MAX
#define TASKS_MAX (254)
#endif

#if TASKS_MAX <= 254
typedef u8 Idx;
#else
typedef u16 Idx;
#endif

#if __ELECTRA_USE_SCHEDULER__

struct Task {
    // u8 status;
    u16         delay;
    Idx         next;
    VoidFn      task_fn;
};

Task tasks[TASKS_MAX + 1];
Idx q_head, q_tail, q_delay_head, q_new_task;
Idx q_tasks_count;

Task running_task;

Idx _findEmptyTask() {
    if(q_tasks_count <= TASKS_MAX) {
        for(Idx i = 1; i <= TASKS_MAX; ++i) {
            if(tasks[i].task_fn == NULL) {
                return i;
            }
        }
    }
    return 0;
}

int electraInit() {
#if __ELECTRA_USE_SCHEDULER__
    q_head = 1;
    q_tail = 1;
    q_delay_head = 0;
#endif
    return 0;
}

bool qEnque(VoidFn task_fn) {
    Idx new_index = _findEmptyTask();
    if(!new_index) {
        return false;
    }
    Task* new_task = &tasks[new_index];
    new_task->task_fn = task_fn;
    new_task->next = 0;
    new_task->delay = 0;
    tasks[q_tail].next = new_index;
    return true;
}

void qDecDelay() {
    // There are delayed tasks
    if(tasks[tasks[q_delay_head].next] != 0) {
        Task* task = &tasks[tasks[q_delay_head].next];
        // head delayed task delay expired
        if((--(task->delay)) == 0)
            q_delay_head = task;
    }
}

bool qEnqueDelayed(VoidFn task_fn, u16 delay) {
    Idx new_index = _findEmptyTask();
    Idx d = q_delay_head;
    if(!new_index) {
        return false;
    }
    // Idx prev = q_delay_head, next = 0;
    Task* new_task = &tasks[new_index];
    new_task->task_fn = task_fn;
    // new_task->delay = delay;
    while(tasks[tasks[d].next].delay <= delay) {
        delay -= tasks[tasks[d].next].delay;
        d = tasks[d].next;
    }
    new_task->next = tasks[d].next;
    tasks[d].next = new_index;

    return true;
}

/*
qEnqu
qDispatch
qEnquDelayed
qDecDelay

*/

#endif // __ELECTRA_USE_SCHEDULER__