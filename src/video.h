#ifndef CEDA_PRINT_H
#define CEDA_PRINT_H

#include <stdbool.h>
#include <stdint.h>

extern char *const VIDEO_MEMORY;

void video_cls(void);
void video_put(uint8_t x, uint8_t y, char c);
char video_get(uint8_t x, uint8_t y);
void video_locate(uint8_t row, uint8_t column);
void video_enableHorizontalStretch(bool enable);
void video_enableVerticalStretch(bool enable);
void video_enableUnderline(bool enable);
void video_putchar(char c);

#endif // CEDA_PRINT_H
