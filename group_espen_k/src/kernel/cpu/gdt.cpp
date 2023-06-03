#include "gdt.h"

#define GDT_ENTRIES 5

ESOS::GDT::gdt_entry_t gdt[GDT_ENTRIES];
ESOS::GDT::gdt_ptr_t gdt_ptr;

/**
 * Here we are forcing the compiler to name the function init_gdt
 * this is usefull because we a re calling this function from the
 * boot.asm file and we need to be 100% sure what its name is.
*/
void ESOS::GDT::init_gdt() asm ("init_gdt");

/**
 * Here we are doing the oposite of above, instead of allowing our
 * c++ function to be called from assembly we are now allowing the
 * assembly function gdt_flush to be called from c++
*/
extern "C" {
    extern void gdt_flush(uint32_t);
}


void ESOS::GDT::init_gdt()
{
    // Set the GDT limit
    gdt_ptr.limit = sizeof( ESOS::GDT::gdt_entry_t) * GDT_ENTRIES - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    // num, base, limit, access, granularity
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    // Flush GDT pointer
    gdt_flush((uint32_t)&gdt_ptr);
}


void ESOS::GDT::gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;
}