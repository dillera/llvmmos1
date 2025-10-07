/*
 * Atari 800XL Test Application
 * Built with llvm-mos compiler
 */

#include <atari.h>
#include <peekpoke.h>
#include <string.h>

// Atari screen memory (text mode)
#define SCREEN_MEM 0x3C00
#define COLOR_REGISTER 0x2C8

// Function to clear the screen
void clear_screen(void) {
    unsigned char i;
    for (i = 0; i < 240; i++) {
        POKE(SCREEN_MEM + i, 0);
    }
}

// Function to print text at a specific screen position
void print_at(unsigned char x, unsigned char y, const char* text) {
    unsigned int pos = SCREEN_MEM + (y * 40) + x;
    unsigned char i = 0;
    
    while (text[i] != '\0') {
        unsigned char ch = text[i];
        
        // Convert ASCII to ATASCII screen codes
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - 'a' + 97;  // lowercase
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 33;  // uppercase (inverse video)
        } else if (ch >= '0' && ch <= '9') {
            ch = ch - '0' + 16;
        } else if (ch == ' ') {
            ch = 0;
        } else if (ch == '!') {
            ch = 1;
        }
        
        POKE(pos + i, ch);
        i++;
    }
}

// Function to set background and border colors
void set_colors(unsigned char bg, unsigned char border) {
    POKE(712, bg);      // Background color
    POKE(710, border);  // Border color
}

// Main program
int main(void) {
    unsigned char counter = 0;
    unsigned int delay;
    
    // Initialize display
    clear_screen();
    
    // Set colors (background: dark blue, border: light blue)
    set_colors(0x84, 0x7C);
    
    // Display welcome message
    print_at(5, 4, "LLVM-MOS TEST PROGRAM");
    print_at(5, 5, "=====================");
    
    print_at(3, 8, "ATARI 800XL DEVELOPMENT");
    print_at(3, 10, "Built with llvm-mos compiler");
    
    print_at(3, 14, "Counter: 0");
    
    // Main loop - simple counter animation
    while (1) {
        // Simple delay loop
        for (delay = 0; delay < 5000; delay++) {
            // Busy wait
        }
        
        counter++;
        
        // Update counter display
        POKE(SCREEN_MEM + (14 * 40) + 12, 16 + (counter / 100) % 10);
        POKE(SCREEN_MEM + (14 * 40) + 13, 16 + (counter / 10) % 10);
        POKE(SCREEN_MEM + (14 * 40) + 14, 16 + counter % 10);
        
        // Cycle background color
        if ((counter & 0x0F) == 0) {
            unsigned char color = PEEK(712);
            color = (color + 2) & 0xFE;
            POKE(712, color);
        }
    }
    
    return 0;
}
