

// Assign human-readable names to some common 16-bit color values:
// #define	BLACK   0x0000
// #define	BLUE    0x001F
// #define	RED     0xF800
// #define	GREEN   0x07E0
// #define CYAN    0x07FF
// #define MAGENTA 0xF81F
// #define YELLOW  0xFFE0
// #define WHITE   0xFFFF

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4


#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define SD_CS 10   

int buttons [15][4];
int bCount = 0;

String update = "update.txt";

int x = 0;
