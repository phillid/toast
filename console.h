#ifndef __CONSOLE_H
#define __CONSOLE_H

#define console_width		80
#define console_height		25
#define console_x_pos		(console_pointer%(2*console_width))
#define console_y_pos		(uint8_t)(console_pointer/(2*console_width))

#define COLOR_BLACK			0x0
#define COLOR_BLUE			0x1
#define COLOR_GREEN			0x2
#define COLOR_TEAL			0x3
#define COLOR_BROWN			0x4
#define COLOR_PURPLE		0x5
#define COLOR_GOLD			0x6
#define COLOR_BRIGHT_GREY	0x7
#define COLOR_BRIGHT_GRAY	0x7 // Alias for grey vs gray
#define COLOR_GRAY			0x8
#define COLOR_GREY			0x8 // Alias for grey vs gray
#define COLOR_BRIGHT_BLUE	0x9
#define COLOR_BRIGHT_GREEN	0xA
#define COLOR_LIME			0xA // Alias for lime vs bright green
#define COLOR_AQUA			0xB
#define COLOR_RED			0xC
#define COLOR_PINK			0xD
#define COLOR_YELLOW		0xE
#define COLOR_WHITE			0xF


char* console_buffer;
uint16_t console_pointer;
uint8_t console_color;

void console_init();
void console_update_cursor();
void console_clear();
void console_set_colors(uint8_t fg, uint8_t bg);
void console_set_color(uint8_t fg);
void console_print(char *string);

#endif