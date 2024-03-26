#ifndef __LCDRGB_API_H
#define __LCDRGB_API_H

#include "config.h"

typedef uint32_t color_t;

/* 颜色 */
#define RGBLCD_BLUE 0x000000FF
#define RGBLCD_GREEN 0x0000FF00
#define RGBLCD_RED 0x00FF0000
#define RGBLCD_CYAN 0x0000FFFF
#define RGBLCD_MAGENTA 0x00FF00FF
#define RGBLCD_YELLOW 0x00FFFF00
#define RGBLCD_LIGHTBLUE 0x008080FF
#define RGBLCD_LIGHTGREEN 0x0080FF80
#define RGBLCD_LIGHTRED 0x00FF8080
#define RGBLCD_LIGHTCYAN 0x0080FFFF
#define RGBLCD_LIGHTMAGENTA 0x00FF80FF
#define RGBLCD_LIGHTYELLOW 0x00FFFF80
#define RGBLCD_DARKBLUE 0x00000080
#define RGBLCD_DARKGREEN 0x00008000
#define RGBLCD_DARKRED 0x00800000
#define RGBLCD_DARKCYAN 0x00008080
#define RGBLCD_DARKMAGENTA 0x00800080
#define RGBLCD_DARKYELLOW 0x00808000
#define RGBLCD_WHITE 0x00FFFFFF
#define RGBLCD_LIGHTGRAY 0x00D3D3D3
#define RGBLCD_GRAY 0x00808080
#define RGBLCD_DARKGRAY 0x00404040
#define RGBLCD_BLACK 0x00000000
#define RGBLCD_BROWN 0x00A52A2A
#define RGBLCD_ORANGE 0x00FFA500
#define RGBLCD_TRANSPARENT 0x00000000

#define RGBLCD_RGB(r, g, b) ((r) << 16 | (g) << 8 | (b))

#define rgblcd_UNFILLED 0
#define rgblcd_FILLED 1

inline void    rgblcd_SetColor(color_t color);
inline void    rgblcd_SetBKColor(color_t color);
inline void    rgblcd_DrawPoint(uint16_t x, uint16_t y, color_t color);
inline color_t rgblcd_ReadPoint(uint16_t x, uint16_t y);
inline void    rgblcd_Clear();
inline void    rgblcd_ClearArea(uint16_t x, uint16_t y, uint16_t Width, uint16_t Height);
void           rgblcd_ReverseArea(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height);
void           rgblcd_ShowChar(uint16_t x, uint16_t y, uint8_t ch, uint8_t fontSize, uint8_t mode, color_t color);
void           rgblcd_ShowString(uint16_t x, uint16_t y, uint8_t* str, uint8_t fontSize, uint8_t mode, color_t color);
void           rgblcd_ShowNum(uint16_t x, uint16_t y, uint16_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color);
void           rgblcd_ShowSignedNum(uint16_t x, uint16_t y, int32_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color);
void           rgblcd_ShowHexNum(uint16_t x, uint16_t y, int32_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color);
void           rgblcd_ShowBinNum(uint16_t X, uint16_t Y, int32_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color);
void           rgblcd_DrawFastHLine(uint16_t X0, uint16_t Y0, uint16_t width, color_t color);
void           rgblcd_DrawFastVLine(uint16_t X0, uint16_t Y0, uint16_t height, color_t color);
void           rgblcd_DrawLine(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, color_t color);
void           rgblcd_DrawRectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint8_t IsFilled, color_t color);
void rgblcd_DrawTriangle(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint8_t IsFilled, color_t color);
void rgblcd_DrawCircle(uint16_t X, uint16_t Y, uint16_t Radius, uint8_t IsFilled, color_t color);
void rgblcd_DrawEllipse(uint16_t X, uint16_t Y, uint16_t A, uint16_t B, uint8_t IsFilled, color_t color);

#endif
