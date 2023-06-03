/* code from cource lecture and repository
  * https://perara.notion.site/Lecture-4-Global-Descriptor-Tables-86c7a3e7252e4648a2b7f4417d472587
  * https://github.com/perara/ikt218-advanced-operating-systems/blob/1ce6e0b734968ad952275b8bbff049b8b690c5fb/src/kernel/cpu/i386/gdt.cpp
*/

#include "global_descriptor_table.h"


void init_gdt() asm ("init_gdt");


extern "C" {
    #include "system.h"
    extern void gdt_flush(uint32_t);
}

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gdt_ptr;

void init_gdt() {
  // Set the GDT limit
  gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
  gdt_ptr.base = (uint32_t) &gdt;
	
	// num, base, limit, access, granularity 
  gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

  // Load the GDT
  gdt_load(&gdt_ptr);
	
  // Flush GDT pointer
  gdt_flush((uint32_t)&gdt_ptr);

  printf("Global Descriptor Table initialized!\n");
  
}

void gdt_load(struct gdt_ptr *gdt_ptr) {
  asm volatile("lgdt %0" : : "m" (*gdt_ptr));
}

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}