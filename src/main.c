/*
 * Atari 800XL Test Application
 * Built with llvm-mos compiler
 */

#include <stdio.h>
#include <peekpoke.h>
#include <atari.h>

// Screen memory and OS locations
#define SAVMSC  0x58    // Screen memory pointer (2 bytes)

// OS shadow registers for colors
#define COLOR0  0x2C4  // Background color
#define COLOR1  0x2C5  // Border color
#define COLOR2  0x2C6
#define COLOR4  0x2C8  // Text color

// Function to set colors
void set_colors(unsigned char bg, unsigned char border) {
    POKE(712, bg);      // Background (OS shadow of COLOR2)
    POKE(710, border);  // Border (OS shadow of COLOR1)
    POKE(709, 0x0F);    // Text color (bright white)
}

// Convert digit to ATASCII screen code
unsigned char digit_to_screen(unsigned char digit) {
    return digit + 16;  // 0-9 -> screen codes 16-25
}

// Main program
int main(void) {
    unsigned int counter = 0;
    unsigned int delay;
    unsigned char color = 0x84;
    unsigned int screen_mem;
    unsigned int counter_pos;
    
    // Get screen memory location
    screen_mem = PEEK(SAVMSC) | (PEEK(SAVMSC + 1) << 8);
    
    // Set initial colors
    set_colors(color, 0x74);
    
    // Clear screen and print header
    printf("%c", CH_CLR);  // Clear screen
    
    printf("\n\n");
    printf("  ===========================\n");
    printf("   LLVM-MOS TEST PROGRAM\n");
    printf("  ===========================\n\n");
    
    printf("  Atari 800XL Development\n\n");
    printf("  Built with llvm-mos\n");
    printf("  compiler toolkit\n\n\n");
    
    printf("  Counter: 00000\n");
    
    // Calculate screen position for counter digits
    // Row 12 (0-indexed from top), column 11 (after "  Counter: ")
    counter_pos = screen_mem + (12 * 40) + 11;
    
    // Main loop - counter display
    while (1) {
        // Update counter digits directly to screen memory
        POKE(counter_pos + 0, digit_to_screen((counter / 10000) % 10));
        POKE(counter_pos + 1, digit_to_screen((counter / 1000) % 10));
        POKE(counter_pos + 2, digit_to_screen((counter / 100) % 10));
        POKE(counter_pos + 3, digit_to_screen((counter / 10) % 10));
        POKE(counter_pos + 4, digit_to_screen(counter % 10));
        
        // Simple delay
        for (delay = 0; delay < 3000; delay++) {
            // Busy wait
        }
        
        counter++;
        if (counter > 99999) counter = 0;  // Reset at 100000
        
        // Cycle background color every 16 counts
        if ((counter & 0x0F) == 0) {
            color = (color + 4) & 0xFE;
            if (color < 0x20) color = 0x84;  // Reset if too dark
            POKE(712, color);
        }
    }
    
    return 0;
}
