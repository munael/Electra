# Electra RTOS

_Description:_

A minimal library providing Real Time Operating System functionalities, written in C.

---

### Scheduler:

#### API:

**q_enque**:
```c
bool q_enque(VoidFn task_ptr)
```
Add task pointer `task_ptr` to normal queue to be executed in time after all currently scheduled tasks are executed normally.

<br />

**q_enqueDelayed**:
```c
bool q_enqueDelayed(VoidFn task_ptr, QTime delay)
```
Add task pointer to the delay queue to be automatically added to the normal queue after its delay period is elapsed (`delay` reaches `0`).


<br />

**q_dispatch**:
```c
void q_dispatch()
```
Fetch and execute current top task in queue. Does nothing when queues are empty.

<br />

**q_advanceDelay**:
```c
void q_advanceDelay()
```
Advance the delay timers of all queued delayed tasks by 1 unit time.

<br />

**q_reRunMe**:
```c
void q_reRunMe(QTime delay = 0)
```
Re-add latest executed task parent to the currently running task to the end of the __ready__ queue or optionally to the __delay__ queue with delay period `delay`.