#include "pit.h"
#include "common.h"
#include "interrupts.h"

int tick_counter = 0;

void init_pit() {
    register_irq_handler(IRQ0, [](registers_t*, void*)
    {
        tick_counter++;          
    }, NULL);

    outb(PIT_CMD_PORT, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    auto l = (uint8_t)( DIVIDER & 0xFF );
    auto h = (uint8_t)( (DIVIDER >> 8) & 0xFF );

    // Send the frequency divisor.
    outb(PIT_CHANNEL0_PORT, l);
    outb(PIT_CHANNEL0_PORT, h);
}

int get_current_tick()
{
    return tick_counter;
}

void sleep_interrupt(uint32_t milliseconds) {
    int current_tick = get_current_tick();
    int ticks_to_wait = milliseconds * TICKS_PER_MS;
    int end_ticks = current_tick + ticks_to_wait;

    while (current_tick < end_ticks)
    {
        asm volatile("sti");
        asm volatile("hlt");

        current_tick = get_current_tick();
    }
}

void sleep_busy(uint32_t milliseconds) {
    int start_tick = get_current_tick();
    int ticks_to_wait = milliseconds * TICKS_PER_MS;
    int elapsed_ticks = 0;
    
    while (elapsed_ticks < ticks_to_wait)
    {
        while (get_current_tick() == start_tick + elapsed_ticks)
        {
            ; // Busy waiting
        }
        elapsed_ticks++;
    }
}