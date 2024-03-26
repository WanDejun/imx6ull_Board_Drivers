#include "rgblcd_api.h"
#include "font.h"
#include "math.h"
#include "rgblcd.h"

extern rgblcd_typedef rgblcd_device;

inline void rgblcd_SetColor(color_t color) { rgblcd_device.frontColor = color; }

inline void rgblcd_SetBKColor(color_t color) { rgblcd_device.backColor = color; }

inline void rgblcd_DrawPoint(uint16_t x, uint16_t y, color_t color) {
    *(__IO uint32_t*)(rgblcd_device.frameBuffer + (rgblcd_device.pixsize * (rgblcd_device.width * y + x))) = color;
}
inline void rgblcd_DrawFTPoint(x, y) { rgblcd_DrawPoint(x, y, rgblcd_device.frontColor); }

inline void rgblcd_DrawBKPoint(x, y) { rgblcd_DrawPoint(x, y, rgblcd_device.backColor); }

inline color_t rgblcd_ReadPoint(uint16_t x, uint16_t y) {
    return *(__IO uint32_t*)(rgblcd_device.frameBuffer + (rgblcd_device.pixsize * (rgblcd_device.width * y + x)));
}

inline void rgblcd_Clear() {
    uint32_t i, tot = (uint32_t)rgblcd_device.width * (uint32_t)rgblcd_device.height;
    for (i = 0; i < tot; i++) { *((uint32_t*)(rgblcd_device.frameBuffer) + i) = rgblcd_device.backColor; }
}

inline void rgblcd_ClearArea(uint16_t x, uint16_t y, uint16_t Width, uint16_t Height) {
    uint32_t  i, j;
    uint32_t* buf;
    for (i = 0; i < Height; i++) {
        buf = ((uint32_t*)rgblcd_device.frameBuffer) + (y + i) * rgblcd_device.width + x;
        for (j = 0; j < Width; j++, buf++) { *(buf) = rgblcd_device.backColor; }
    }
}

/**
 * 函    数：将rgblcd显存数组部分取反
 * 参    数：X 指定区域左上角的横坐标，范围：[0, rgblcd_device.width - 1]
 * 参    数：Y 指定区域左上角的纵坐标，范围：[0, rgblcd_device.height - 1]
 * 参    数：Width 指定区域的宽度，范围：[0, rgblcd_device.width ]
 * 参    数：Height 指定区域的高度，范围：[0, rgblcd_device.height]
 * 返 回 值：无
 **/
void rgblcd_ReverseArea(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height) {
    uint32_t  i, j;
    uint32_t* buf;

    /*参数检查，保证指定区域不会超出屏幕范围*/
    if (X > rgblcd_device.width) { return; }
    if (Y > rgblcd_device.height) { return; }
    if (X + Width > rgblcd_device.width) { Width = rgblcd_device.width - X; }
    if (Y + Height > rgblcd_device.height) { Height = rgblcd_device.height - Y; }

    for (i = 0; i < Height; i++) {
        buf = (uint32_t*)(rgblcd_device.frameBuffer) + (Y + i) * rgblcd_device.width + X;
        for (j = 0; j < Width; j++, buf++) {  // 遍历指定列
            *(buf) = ~(*buf);                 // 将显存数组指定数据取反
        }
    }
}

/*工具函数*********************/

/*工具函数仅供内部部分函数使用*/

/**
 * 函    数：次方函数
 * 参    数：X 底数
 * 参    数：Y 指数
 * 返 回 值：等于X的Y次方
 */
static uint32_t rgblcd_Pow(uint32_t X, uint32_t Y) {
    uint32_t Result = 1;  // 结果默认为1
    while (Y--) {         // 累乘Y次
        Result *= X;      // 每次把X累乘到结果上
    }
    return Result;
}

/**
 * 函    数：判断指定点是否在指定多边形内部
 * 参    数：nvert 多边形的顶点数
 * 参    数：vertx verty 包含多边形顶点的x和y坐标的数组
 * 参    数：testx testy 测试点的X和y坐标
 * 返 回 值：指定点是否在指定多边形内部，1：在内部，0：不在内部
 */
static uint8_t rgblcd_pnpoly(uint8_t nvert, int16_t* vertx, int16_t* verty, int16_t testx, int16_t testy) {
    int16_t i, j, c = 0;

    /*此算法由W. Randolph Franklin提出*/
    /*参考链接：https://wrfranklin.org/Research/Short_Notes/pnpoly.html*/
    for (i = 0, j = nvert - 1; i < nvert; j = i++) {
        if (((verty[i] > testy) != (verty[j] > testy)) &&
            (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i])) {
            c = !c;
        }
    }
    return c;
}

/*********************工具函数*/

/**
 * @description	: 在指定位置显示一个字符
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - ch	: 显示字符
 * @param - fontSize: 字体大小, 可选12/16/24/32
 * @param - mode: 叠加方式(1)还是非叠加方式(0)
 * @return 		: 无
 **/

void rgblcd_ShowChar(uint16_t x, uint16_t y, uint8_t ch, uint8_t fontSize, uint8_t mode, color_t color) {
    uint32_t temp, t1, t;
    uint32_t y0 = y;
    uint32_t csize = (fontSize / 8 + ((fontSize % 8) ? 1 : 0)) * (fontSize / 2); /* 得到字体一个字符对应点阵集所占的字节数	 */
    ch = ch - ' '; /*得到偏移后的值（ASCII字库是从空格开始取模，所以-'
                      '就是对应字符的字库）  */
    for (t = 0; t < csize; t++) {
        if (fontSize == 12)
            temp = asc2_1206[ch][t]; /* 调用1206字体 */
        else if (fontSize == 16)
            temp = asc2_1608[ch][t]; /* 调用1608字体 */
        else if (fontSize == 24)
            temp = asc2_2412[ch][t]; /* 调用2412字体 */
        else if (fontSize == 32)
            temp = asc2_3216[ch][t]; /* 调用3216字体 */
        else
            return; /* 没有的字库 		*/
        for (t1 = 0; t1 < 8; t1++) {
            if (temp & 0x80)
                rgblcd_DrawPoint(x, y, color);
            else if (mode == 0)
                rgblcd_DrawBKPoint(x, y, color);
            temp <<= 1;
            y++;
            if (y >= rgblcd_device.height) return; /* 超区域了 */
            if ((y - y0) == fontSize) {
                y = y0;
                x++;
                if (x >= rgblcd_device.width) return; /* 超区域了 */
                break;
            }
        }
    }
}
/**
 * @description	: 在指定位置显示一个字符
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - ch	: 显示字符串
 * @param - fontSize: 字体大小, 可选12/16/24/32
 * @param - mode: 叠加方式(1)还是非叠加方式(0)
 * @return 		: 无
 */
void rgblcd_ShowString(uint16_t x, uint16_t y, uint8_t* str, uint8_t fontSize, uint8_t mode, color_t color) {
    uint32_t i;
    for (i = 0; str[i] != '\0'; i++) {  // 遍历字符串的每个字符

        /*调用rgblcd_ShowChar函数，依次显示每个字符*/
        rgblcd_ShowChar(x + i * fontSize, y, str[i], fontSize, mode, color);
    }
}

/**
 * @description	: 在指定位置显示一个十进制数字
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - number	: 显示数字
 * @param - fontSize: 字体大小, 可选12/16/24/32
 * @param - mode: 叠加方式(1)还是非叠加方式(0)
 * @return 		: 无
 */
void rgblcd_ShowNum(uint16_t x, uint16_t y, uint16_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color) {
    uint32_t i;
    for (i = 0; i < length; i++)  // 遍历数字的每一位
    {
        /*调用rgblcd_ShowChar函数，依次显示每个数字*/
        /*Number / rgblcd_Pow(10, length - i - 1) % 10
         * 可以十进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        rgblcd_ShowChar(x + i * fontSize, y, number / rgblcd_Pow(10, length - i - 1) % 10 + '0', fontSize, mode, color);
    }
}

/**
 * @description	: 在指定位置显示一个有符号数
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - number	: 显示数字
 * @param - fontSize: 字体大小, 可选12/16/24/32
 * @param - mode: 叠加方式(1)还是非叠加方式(0)
 * @return 		: 无
 */
void rgblcd_ShowSignedNum(uint16_t x, uint16_t y, int32_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color) {
    uint32_t i;
    uint32_t number1;

    if (number >= 0) {                                      // 数字大于等于0
        rgblcd_ShowChar(x, y, '+', fontSize, mode, color);  // 显示+号
        number1 = number;                                   // number1直接等于Number
    }
    else {                                                  // 数字小于0
        rgblcd_ShowChar(x, y, '-', fontSize, mode, color);  // 显示-号
        number1 = -number;                                  // number1等于Number取负
    }

    for (i = 0; i < length; i++) {  // 遍历数字的每一位
        /*调用rgblcd_ShowChar函数，依次显示每个数字*/
        /*number1 / rgblcd_Pow(10, Length - i - 1) % 10
         * 可以十进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        rgblcd_ShowChar(x + (i + 1) * fontSize, y, number1 / rgblcd_Pow(10, length - i - 1) % 10 + '0', fontSize, mode, color);
    }
}

/**
 * @description	: 在指定位置显示一个十六进制数
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - number	: 显示数字
 * @param - fontSize: 字体大小, 可选12/16/24/32
 * @param - mode: 叠加方式(1)还是非叠加方式(0)
 * @return 		: 无
 */
void rgblcd_ShowHexNum(uint16_t x, uint16_t y, int32_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color) {
    uint32_t i, SingleNumber;
    for (i = 0; i < length; i++)  // 遍历数字的每一位
    {
        /*以十六进制提取数字的每一位*/
        SingleNumber = number / rgblcd_Pow(16, length - i - 1) % 16;

        if (SingleNumber < 10)  // 单个数字小于10
        {
            /*调用rgblcd_ShowChar函数，显示此数字*/
            /*+ '0' 可将数字转换为字符格式*/
            rgblcd_ShowChar(x + i * fontSize, y, SingleNumber + '0', fontSize, mode, color);
        }
        else  // 单个数字大于10
        {
            /*调用rgblcd_ShowChar函数，显示此数字*/
            /*+ 'A' 可将数字转换为从A开始的十六进制字符*/
            rgblcd_ShowChar(x + i * fontSize, y, SingleNumber - 10 + 'A', fontSize, mode, color);
        }
    }
}

/**
 * @description	: 在指定位置显示一个二进制数
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - number	: 显示数字
 * @param - fontSize: 字体大小, 可选12/16/24/32
 * @param - mode: 叠加方式(1)还是非叠加方式(0)
 * @return 		: 无
 */
void rgblcd_ShowBinNum(uint16_t X, uint16_t Y, int32_t number, uint16_t length, uint8_t fontSize, uint8_t mode, color_t color) {
    uint32_t i;
    for (i = 0; i < length; i++)  // 遍历数字的每一位
    {
        /*调用rgblcd_ShowChar函数，依次显示每个数字*/
        /*Number / rgblcd_Pow(2, Length - i - 1) % 2 可以二进制提取数字的每一位*/
        /*+ '0' 可将数字转换为字符格式*/
        rgblcd_ShowChar(X + i * fontSize, Y, number / rgblcd_Pow(2, length - i - 1) % 2 + '0', fontSize, mode, color);
    }
}
/**
 * @description	: 在指定起始位置和终点位置之间画直线
 * @param - X0	: 起始坐标X轴
 * @param - Y0	: 起始坐标Y轴
 * @param - X1  : 终点坐标X轴
 * @param - Y1  : 终点坐标Y轴
 * @param - color  : 颜色
 * @return 		: 无
 */
void rgblcd_DrawLine(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, color_t color) {
    int32_t x, y, dx, dy, d, incrE, incrNE, temp;
    int32_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
    uint8_t yflag = 0, xyflag = 0;

    if (y0 == y1) {  // 横线单独处理

        /*0号点X坐标大于1号点X坐标，则交换两点X坐标*/
        if (x0 > x1) {
            temp = x0;
            x0 = x1;
            x1 = temp;
        }

        /*遍历X坐标*/
        for (x = x0; x <= x1; x++) {
            rgblcd_DrawPoint(x, y0, color);  // 依次画点
        }
    }
    else if (x0 == x1) {  // 竖线单独处理
        /*0号点Y坐标大于1号点Y坐标，则交换两点Y坐标*/
        if (y0 > y1) {
            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        /*遍历Y坐标*/
        for (y = y0; y <= y1; y++) {
            rgblcd_DrawPoint(x0, y, color);  // 依次画点
        }
    }
    else {  // 斜线

        /*使用Bresenham算法画直线，可以避免耗时的浮点运算，效率更高*/
        /*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
        /*参考教程：https://www.bilibili.com/video/BV1364y1d7Lo*/

        if (x0 > x1) {  // 0号点X坐标大于1号点X坐标
            /*交换两点坐标*/
            /*交换后不影响画线，但是画线方向由第一、二、三、四象限变为第一、四象限*/
            temp = x0;
            x0 = x1;
            x1 = temp;
            temp = y0;
            y0 = y1;
            y1 = temp;
        }

        if (y0 > y1) {  // 0号点Y坐标大于1号点Y坐标
            /*将Y坐标取负*/
            /*取负后影响画线，但是画线方向由第一、四象限变为第一象限*/
            y0 = -y0;
            y1 = -y1;

            /*置标志位yflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
            yflag = 1;
        }

        if (y1 - y0 > x1 - x0) {  // 画线斜率大于1

            /*将X坐标与Y坐标互换*/
            /*互换后影响画线，但是画线方向由第一象限0~90度范围变为第一象限0~45度范围*/
            temp = x0;
            x0 = y0;
            y0 = temp;
            temp = x1;
            x1 = y1;
            y1 = temp;

            /*置标志位xyflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
            xyflag = 1;
        }

        /*以下为Bresenham算法画直线*/
        /*算法要求，画线方向必须为第一象限0~45度范围*/
        dx = x1 - x0;
        dy = y1 - y0;
        incrE = 2 * dy;
        incrNE = 2 * (dy - dx);
        d = 2 * dy - dx;
        x = x0;
        y = y0;

        /*画起始点，同时判断标志位，将坐标换回来*/
        if (yflag && xyflag) { rgblcd_DrawPoint(y, -x, color); }
        else if (yflag) { rgblcd_DrawPoint(x, -y, color); }
        else if (xyflag) { rgblcd_DrawPoint(y, x, color); }
        else { rgblcd_DrawPoint(x, y, color); }

        while (x < x1) {  // 遍历X轴的每个点

            x++;
            if (d < 0)  // 下一个点在当前点东方
            {
                d += incrE;
            }
            else  // 下一个点在当前点东北方
            {
                y++;
                d += incrNE;
            }

            /*画每一个点，同时判断标志位，将坐标换回来*/
            if (yflag && xyflag) { rgblcd_DrawPoint(y, -x, color); }
            else if (yflag) { rgblcd_DrawPoint(x, -y, color); }
            else if (xyflag) { rgblcd_DrawPoint(y, x, color); }
            else { rgblcd_DrawPoint(x, y, color); }
        }
    }
}

/**
 * @description	: 在指定起始位置绘制指定水平线
 * @param - X0	: 起始坐标X轴
 * @param - Y0	: 起始坐标Y轴
 * @param - width : 宽度
 * @param - color  : 颜色
 * @return 		: 无
 */
void rgblcd_DrawFastHLine(uint16_t X0, uint16_t Y0, uint16_t width, color_t color) {
    uint32_t* buf = ((uint32_t*)rgblcd_device.frameBuffer) + X0 + Y0 * (rgblcd_device.width);
    uint32_t  i;
    for (i = 0; i < width; i++, buf++) {
        *(buf) = color;
    }
}

/**
 * @description	: 在指定起始位置绘制指定竖直线
 * @param - X0	: 起始坐标X轴
 * @param - Y0	: 起始坐标Y轴
 * @param - height : 高度
 * @param - color  : 颜色
 * @return 		: 无
 */
void rgblcd_DrawFastVLine(uint16_t X0, uint16_t Y0, uint16_t height, color_t color) {
    uint32_t* buf = ((uint32_t*)rgblcd_device.frameBuffer) + X0 + Y0 * (rgblcd_device.width);
    uint32_t  i;
    for (i = 0; i < height; i++, buf += rgblcd_device.width) {
        *(buf) = color;
    }
}

/**
 * 函    数：rgblcd矩形
 * 参    数：X 指定矩形左上角的横坐标
 * 参    数：Y 指定矩形左上角的纵坐标
 * 参    数：Width 指定矩形的宽度
 * 参    数：Height 指定矩形的高度
 * 参    数：IsFilled 指定矩形是否填充
 *           范围：rgblcd_UNFILLED		不填充
 *                 rgblcd_FILLED			填充
 * 返 回 值：无
 * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void rgblcd_DrawRectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint8_t IsFilled, color_t color) {
    uint32_t i, j;
    if (!IsFilled) {  // 指定矩形不填充
        /*遍历上下X坐标，画矩形上下两条线*/
        for (i = X; i < X + Width; i++) {
            rgblcd_DrawPoint(i, Y, color);
            rgblcd_DrawPoint(i, Y + Height - 1, color);
        }
        /*遍历左右Y坐标，画矩形左右两条线*/
        for (i = Y; i < Y + Height; i++) {
            rgblcd_DrawPoint(X, i, color);
            rgblcd_DrawPoint(X + Width - 1, i, color);
        }
    }
    else {  // 指定矩形填充
        /*遍历X坐标*/
        for (i = X; i < X + Width; i++) {
            /*遍历Y坐标*/
            for (j = Y; j < Y + Height; j++) {
                /*在指定区域画点，填充满矩形*/
                rgblcd_DrawPoint(i, j, color);
            }
        }
    }
}

/**
 * 函    数：rgblcd三角形
 * 参    数：X0 指定第一个端点的横坐标
 * 参    数：Y0 指定第一个端点的纵坐标
 * 参    数：X1 指定第二个端点的横坐标
 * 参    数：Y1 指定第二个端点的纵坐标
 * 参    数：X2 指定第三个端点的横坐标
 * 参    数：Y2 指定第三个端点的纵坐标
 * 参    数：IsFilled 指定三角形是否填充
 *           范围：rgblcd_UNFILLED		不填充
 *                 rgblcd_FILLED			填充
 * 返 回 值：无
 * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void rgblcd_DrawTriangle(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint8_t IsFilled, color_t color) {
    uint32_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
    uint32_t i, j;
    int16_t  vx[] = { X0, X1, X2 };
    int16_t  vy[] = { Y0, Y1, Y2 };

    if (!IsFilled)  // 指定三角形不填充
    {
        /*调用画线函数，将三个点用直线连接*/
        rgblcd_DrawLine(X0, Y0, X1, Y1, color);
        rgblcd_DrawLine(X0, Y0, X2, Y2, color);
        rgblcd_DrawLine(X1, Y1, X2, Y2, color);
    }
    else  // 指定三角形填充
    {
        /*找到三个点最小的X、Y坐标*/
        if (X1 < minx) { minx = X1; }
        if (X2 < minx) { minx = X2; }
        if (Y1 < miny) { miny = Y1; }
        if (Y2 < miny) { miny = Y2; }

        /*找到三个点最大的X、Y坐标*/
        if (X1 > maxx) { maxx = X1; }
        if (X2 > maxx) { maxx = X2; }
        if (Y1 > maxy) { maxy = Y1; }
        if (Y2 > maxy) { maxy = Y2; }

        /*最小最大坐标之间的矩形为可能需要填充的区域*/
        /*遍历此区域中所有的点*/
        /*遍历X坐标*/
        for (i = minx; i <= maxx; i++) {
            /*遍历Y坐标*/
            for (j = miny; j <= maxy; j++) {
                /*调用rgblcd_pnpoly，判断指定点是否在指定三角形之中*/
                /*如果在，则画点，如果不在，则不做处理*/
                if (rgblcd_pnpoly(3, vx, vy, i, j)) { rgblcd_DrawPoint(i, j, color); }
            }
        }
    }
}

/**
 * 函    数：rgblcd画圆
 * 参    数：X 指定圆的圆心横坐标
 * 参    数：Y 指定圆的圆心纵坐标
 * 参    数：Radius 指定圆的半径，范围：0~255
 * 参    数：IsFilled 指定圆是否填充
 *           范围：rgblcd_UNFILLED		不填充
 *                 rgblcd_FILLED			填充
 * 返 回 值：无
 * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void rgblcd_DrawCircle(uint16_t X, uint16_t Y, uint16_t Radius, uint8_t IsFilled, color_t color) {
    int32_t x, y, d, j;

    /*使用Bresenham算法画圆，可以避免耗时的浮点运算，效率更高*/
    /*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
    /*参考教程：https://www.bilibili.com/video/BV1VM4y1u7wJ*/

    d = 1 - Radius;
    x = 0;
    y = Radius;

    /*画每个八分之一圆弧的起始点*/
    rgblcd_DrawPoint(X + x, Y + y, color);
    rgblcd_DrawPoint(X - x, Y - y, color);
    rgblcd_DrawPoint(X + y, Y + x, color);
    rgblcd_DrawPoint(X - y, Y - x, color);

    if (IsFilled) {  // 指定圆填充
        /*遍历起始点Y坐标*/
        for (j = -y; j < y; j++) {
            /*在指定区域画点，填充部分圆*/
            rgblcd_DrawPoint(X, Y + j, color);
        }
    }

    while (x < y) {  // 遍历X轴的每个点
        x++;
        if (d < 0) {  // 下一个点在当前点东方

            d += 2 * x + 1;
        }
        else {  // 下一个点在当前点东南方
            y--;
            d += 2 * (x - y) + 1;
        }

        /*画每个八分之一圆弧的点*/
        rgblcd_DrawPoint(X + x, Y + y, color);
        rgblcd_DrawPoint(X + y, Y + x, color);
        rgblcd_DrawPoint(X - x, Y - y, color);
        rgblcd_DrawPoint(X - y, Y - x, color);
        rgblcd_DrawPoint(X + x, Y - y, color);
        rgblcd_DrawPoint(X + y, Y - x, color);
        rgblcd_DrawPoint(X - x, Y + y, color);
        rgblcd_DrawPoint(X - y, Y + x, color);

        if (IsFilled) {  // 指定圆填充

            /*遍历中间部分*/
            for (j = -y; j < y; j++) {
                /*在指定区域画点，填充部分圆*/
                rgblcd_DrawPoint(X + x, Y + j, color);
                rgblcd_DrawPoint(X - x, Y + j, color);
            }

            /*遍历两侧部分*/
            for (j = -x; j < x; j++) {
                /*在指定区域画点，填充部分圆*/
                rgblcd_DrawPoint(X - y, Y + j, color);
                rgblcd_DrawPoint(X + y, Y + j, color);
            }
        }
    }
}

/**
 * 函    数：rgblcd画椭圆
 * 参    数：X 指定椭圆的圆心横坐标
 * 参    数：Y 指定椭圆的圆心纵坐标
 * 参    数：A 指定椭圆的横向半轴长度，范围：0~255
 * 参    数：B 指定椭圆的纵向半轴长度，范围：0~255
 * 参    数：IsFilled 指定椭圆是否填充
 *           范围：rgblcd_UNFILLED		不填充
 *                 rgblcd_FILLED			填充
 * 返 回 值：无
 * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void rgblcd_DrawEllipse(uint16_t X, uint16_t Y, uint16_t A, uint16_t B, uint8_t IsFilled, color_t color) {
    int32_t x, y, j;
    int32_t a = A, b = B;
    float   d1, d2;

    /*使用Bresenham算法画椭圆，可以避免部分耗时的浮点运算，效率更高*/
    /*参考链接：https://blog.csdn.net/myf_666/article/details/128167392*/

    x = 0;
    y = b;
    d1 = b * b + a * a * (-b + 0.5);

    if (IsFilled) {  // 指定椭圆填充

        /*遍历起始点Y坐标*/
        for (j = -y; j < y; j++) {
            /*在指定区域画点，填充部分椭圆*/
            rgblcd_DrawPoint(X, Y + j, color);
            rgblcd_DrawPoint(X, Y + j, color);
        }
    }

    /*画椭圆弧的起始点*/
    rgblcd_DrawPoint(X + x, Y + y, color);
    rgblcd_DrawPoint(X - x, Y - y, color);
    rgblcd_DrawPoint(X - x, Y + y, color);
    rgblcd_DrawPoint(X + x, Y - y, color);

    /*画椭圆中间部分*/
    while (b * b * (x + 1) < a * a * (y - 0.5)) {
        if (d1 <= 0) {  // 下一个点在当前点东方

            d1 += b * b * (2 * x + 3);
        }
        else {  // 下一个点在当前点东南方

            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            y--;
        }
        x++;

        if (IsFilled) {  // 指定椭圆填充

            /*遍历中间部分*/
            for (j = -y; j < y; j++) {
                /*在指定区域画点，填充部分椭圆*/
                rgblcd_DrawPoint(X + x, Y + j, color);
                rgblcd_DrawPoint(X - x, Y + j, color);
            }
        }

        /*画椭圆中间部分圆弧*/
        rgblcd_DrawPoint(X + x, Y + y, color);
        rgblcd_DrawPoint(X - x, Y - y, color);
        rgblcd_DrawPoint(X - x, Y + y, color);
        rgblcd_DrawPoint(X + x, Y - y, color);
    }

    /*画椭圆两侧部分*/
    d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

    while (y > 0) {
        if (d2 <= 0) {  // 下一个点在当前点东方

            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
        }
        else {  // 下一个点在当前点东南方

            d2 += a * a * (-2 * y + 3);
        }
        y--;

        if (IsFilled)  // 指定椭圆填充
        {
            /*遍历两侧部分*/
            for (j = -y; j < y; j++) {
                /*在指定区域画点，填充部分椭圆*/
                rgblcd_DrawPoint(X + x, Y + j, color);
                rgblcd_DrawPoint(X - x, Y + j, color);
            }
        }

        /*画椭圆两侧部分圆弧*/
        rgblcd_DrawPoint(X + x, Y + y, color);
        rgblcd_DrawPoint(X - x, Y - y, color);
        rgblcd_DrawPoint(X - x, Y + y, color);
        rgblcd_DrawPoint(X + x, Y - y, color);
    }
}

/*********************功能函数*/