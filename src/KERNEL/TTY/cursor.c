#include "../../INCL/tty.h"
#include "../../INCL/io.h"

void scroll_buffer(void);

/// @brief  Updates cursor's position
/// @param  line_break If the char that was written is a \n, the logic changes a bit
void    update_cursor(bool line_break) {

    if (line_break == true) {
        if (terminal_row == VGA_HEIGHT - 1) {
            scroll_buffer();
        } 
        else {
            terminal_row++;
        }
        terminal_column = 0;
    }
    else {
        terminal_column++;
        if (terminal_column == VGA_WIDTH) {
            if (terminal_row == VGA_HEIGHT - 1) {
                scroll_buffer();
            } 
            else { 
                terminal_row++;
            }
            terminal_column = 0;
        }
    }

    // Updates the blinking cursor position
    // TODO: Currently updates after every char written, probaby a good idea to only do it after 
    // TODO: writing a chunk of data to optimize
    // ! OR : always keep it at the bottom of the screen and separate the input block from the display block
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

	outb(0x3D4, 0x0F); // 0x3D4 is a port that selects a screen's register, which is 0x0F (x position of cursor)
	outb(0x3D5, (uint8_t) (pos & 0xFF)); // 0x3D5 is a port that reads/writes to the selected register, we write the new x position of the cursor
	outb(0x3D4, 0x0E); // we select 0X0E register (y position of cursor)
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF)); // we write the new y position of the cursor
}

void scroll_buffer(void) {
    if (terminal_row == VGA_HEIGHT) {
        // Shift all rows up by one
        for (unsigned int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
            terminal_buffer[i] = terminal_buffer[i + VGA_WIDTH];
        }

        // Clear the last row (bottom-most row of the screen)
        for (unsigned int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
            terminal_buffer[i] = vga_entry(' ', terminal_color);
        }
    }
}

/// @brief   Moves the cursor back from one column or row if we're at col 0
void move_cursor_back(void) {
    
    if (terminal_column == 0) {
        if (terminal_row != 0) {
            terminal_row--;
            terminal_column = VGA_WIDTH;
        }
    }
    else {
        terminal_column--;
    }

    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

	outb(0x3D4, 0x0F); // 0x3D4 is a port that selects a screen's register, which is 0x0F (x position of cursor)
	outb(0x3D5, (uint8_t) (pos & 0xFF)); // 0x3D5 is a port that reads/writes to the selected register, we write the new x position of the cursor
	outb(0x3D4, 0x0E); // we select 0X0E register (y position of cursor)
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF)); // we write the new y position of the cursor
}

/// @brief                  Enable showing of blinking cursor
/// @param cursor_start     Change how large the cursor is
/// @param cursor_end       //
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}
