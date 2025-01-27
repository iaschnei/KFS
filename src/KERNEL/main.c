#include "../INCL/libc.h"
#include "../INCL/tty.h"
#include "../INCL/gdt.h"

size_t  terminal_row[3];
size_t  terminal_column[3];
uint8_t terminal_color[3];
uint16_t *terminal_buffer;
uint16_t current_window;
uint16_t terminal_windows[3][2000];

void kernel_main(void) {
    terminal_initialize();
    init_gdt();
    enter_protected();
    handle_keyboard();
}
