#include <stddef.h>
#include <stdint.h>

// color constants
enum vga_color{
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GRAY    = 7,
    VGA_COLOR_DARK_GRAY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_GREEN   = 11,
    VGA_COLOR_PINK          = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str){
    size_t len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

size_t console_row;
size_t console_col;
uint8_t console_color;
uint16_t* console_buffer = (uint16_t*)VGA_MEMORY;

void set_console_color(uint8_t color){
    console_color = color;
}

void insert_entry_at(char c, uint8_t color, size_t x, size_t y){
    const size_t idx = y * VGA_WIDTH + x;
    console_buffer[idx] = vga_entry(c, color);
}

void insert_char(char c){
    insert_entry_at(c, console_color, console_col, console_row);
    if(++console_col == VGA_WIDTH){
        console_col = 0;
        if(++console_row == VGA_HEIGHT) console_row = 0;
    }
}

void console_write(const char* data, size_t size){
    for(size_t i = 0; i < size; i++){
        insert_char(data[i]);
    }
}

void console_write_string(const char* data){
    console_write(data, strlen(data));
}

void console_init(void){
    console_row = 0;
    console_col = 0;
    console_color = VGA_COLOR_WHITE, VGA_COLOR_BLACK;

    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for (size_t x = 0; x < VGA_WIDTH; x++){
            const size_t idx = y * VGA_WIDTH + x;
            console_buffer[idx] = vga_entry(' ', console_color);
        }
    }
}