#include "../../INCL/tty.h"

/* x86 Real Mode Memory Map : 0x000B8000 - 0x000BFFFF - Color Video Memory */

/// @brief Initializes the terminal by initializing its associated global variables
// 			and displaying the space char for every characters to display an empty terminal.
/// @param  None
void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;

    // Empty all screen buffers :
    clear_buffer(screen_buffer_a);
	cursor_pos_a = 0;
    clear_buffer(screen_buffer_b);
	cursor_pos_b = 0;
    clear_buffer(screen_buffer_c);
	cursor_pos_c = 0;

    // Load the first buffer
    load_buffer(screen_buffer_a);
    current_screen_buffer = screen_buffer_a;

	// for (size_t y = 0; y < VGA_HEIGHT; y++) {
	// 	for (size_t x = 0; x < VGA_WIDTH; x++) {
	// 		const size_t index = y * VGA_WIDTH + x;
	// 		terminal_buffer[index] = vga_entry(' ', terminal_color);
	// 	}
	// }
    enable_cursor(0x0A, 0x0C);
}
