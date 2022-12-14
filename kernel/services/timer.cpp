#include "timer.h"
#include "../ring3/tss.h"
#include "../proc/task.h"

void timer_phase(int hz)
{
	int divisor = 1193180 / hz;	   /* Calculate our divisor */
	outb(0x43, 0x36);			 /* Set our command byte 0x36 */
	outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
	outb(0x40, divisor >> 8);	 /* Set high byte of divisor */
}

void timer_handler(struct regs *r)
{
    //set_kernel_stack(r->esp); // Eventually i will add this
    /* Increment our 'tick count' */
    timer_ticks++;
    swap_buffers();
    end_interrupt(r);
    asm("sti"); // End the interrupt
    if (tasking) {
        runningTask->current_quantum--;
        if (runningTask->current_quantum < 0) {
            schedule();
        }
    }
}

void sleep (int ms){
    int start = timer_ticks;
    while(timer_ticks < start + ms){
        asm("nop");
    }
    return;
}

void timer_install()
{
    print_string("Installing timer...      \r");
    irq_install_handler(0, timer_handler);
    timer_phase(1000);
}

uint64_t read_counter() {
    return timer_ticks;
}