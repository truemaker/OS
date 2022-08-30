#include "shutdown.h"

void power_shutdown() {
    clear_screen();
    print_string("Shutting down...\n\r");
    asm("cli");
    outw((uint16_t)0x604, (uint16_t)0x2000);
    asm("hlt");
}

void power_restart() {
    uint8_t temp;
    asm ("cli");
    do
    {
        temp = inb(0x64); // Read from the Keyboard Interface IO port to clear the user data
        if (((temp) & (1)) != 0) // Check if the keyboard data buffer is clear
            inb(0x60); // Read from the keyboard IO port to clear the user data
    } while (((temp) & (1<<1)) != 0); // Repeat until both buffers are clear
 
    outb(0x64, 0xFE); // Write CPU_RESET(0xfe) to the keyboard interface IO port
    while (1) { // If the above code does not work, halt the cpu.
        asm("hlt");
    }
}