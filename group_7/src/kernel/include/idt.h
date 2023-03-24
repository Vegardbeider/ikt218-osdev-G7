#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

// Define the IDT entry structure
struct idt_entry_t {
  uint16_t base_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));


struct idt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));


// Initialize the GDT and IDT
void init_idt();

// Load the GDT and IDT
void idt_load();



static idt_entry_t idt[IDT_ENTRIES];
static idt_ptr_t idt_ptr;

#endif