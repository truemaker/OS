#pragma once
#include <stdint.h>
#include "../interrupts/regs.h"
#include "../gatr/vga.h"

enum ProcState {
    PROC_RUNNING,
    PROC_READY,
    PROC_DEAD,
    PROC_SLEEPING,
    PROC_WAITING
};

struct Process {
    uint32_t pid;
    uint32_t parent_pid;
    ProcState state;
    void* loop;
    char* name;
    int exit_code;
};

#define MAX_PID 255

void kernel_loop();
void proc_create(void* loop_func);
void proc_quit(int exit_code);
int proc_fork(void* loop_func);
void proc_cycle();

Process proc_list[256];
uint8_t cur_pid;
uint8_t newest_pid;