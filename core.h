/**
    Authored by:
    Muhammad Nael ElNokrashy
    , Yasmin ElDokany

    For Micro Controllers course-work
    Dr Mohamed Shalan
    American University in Cairo, 2017
*/


#pragma once

#ifndef __ELECTRA_INCD_CORE_H__
#define __ELECTRA_INCD_CORE_H__

#ifndef __ELECTRA_TMR_FREQ__
#error "Electra::Scheduler requires a defined frequency `__ELECTRA_TMR_FREQ__` to function."
#endif

#include "common.h"

typedef void(*VoidFn)();

#ifndef TASKS_MAX
#define TASKS_MAX (254)
#endif

// Automatic type definitions
#if TASKS_MAX <= 254
typedef u8  Idx;
#else
typedef u16 Idx;
#endif

#if __ELECTRA_TMR_FREQ__ <= 254
typedef u8  QTime;
#else
typedef u16 QTime;
#endif
// \\ Automatic type definitions

// Scheduler feature enable
#if __ELECTRA_USE_SCHEDULER__
/**
    Scheduler:
    A Compact Task Dispatcher for Embedded Systems by Ron Kreymborg
    Implemented by:
    Muhammad Nael ElNokrashy
    , Yasmin ElDokany
*/

struct Task {
    // Unused in current implementation
    // u8          status;
    u16         delay;
    Idx         next;
    VoidFn      task_fn;
};

// Task queue
Task tasks[TASKS_MAX + 1];

// Heads and tails
Idx /*_q_ready_head,*/ _q_delayed_head, _q_ready_tail = 0;
Idx _q_running_task, _q_new_task;
Idx _q_size = 0;

Idx _q_findEmptySlot() {
    // queue is NOT full
    if(_q_size < TASKS_MAX)
        for(Idx i = 1; i <= TASKS_MAX; ++i) {
            if(tasks[i].task_fn == NULL) return i;
        }
    else return 0;
}


// q_enque
bool q_enque(VoidFn task_ptr) {
    Idx new_index = _q_findEmptySlot();
    if(!new_index) return false;

    tasks[_q_ready_tail].next = new_index;
    tasks[new_index].task_fn = task_ptr;
    ++_q_size;
    return true;
}

bool q_enqueDelayed(VoidFn task_ptr, QTime delay) {
    Idx new_index = _q_findEmptySlot();
    if(!new_index) return false;

    // Find correct positioning for new task based on delay

    // Update delays accordingly

    // Update indices
    
    return true;
}

void _q_runTask(Idx i) {
    (*tasks[i].task_fn)();
}

void q_dispatch() {
    // If there's a head, run
    if(tasks[0].next) _q_runTask(tasks[0].next);
}

void q_advanceDelay() {
    if(!_q_delayed_head) return;
    while(tasks[_q_delayed_head].delay == 0) {
        _q_delayed_head = tasks[_q_delayed_head].next;
    }
    if(_q_delayed_head) --tasks[_q_delayed_head];
}

void q_reRunMe(QTime delay = 0) {
    _q_new_task = _q_running_task;
    tasks[_q_running_task].delay = delay;
}

#endif // __ELECTRA_USE_SCHEDULER__

void initElectra() {
    #if __ELECTRA_USE_SCHEDULER__
    
    #endif
}

#endif // __ELECTRA_INCD_CORE_H__