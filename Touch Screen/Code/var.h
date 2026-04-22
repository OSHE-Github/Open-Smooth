

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

//#define PING Serial.println("ping");

#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define SD_CS 10   

//how long the file linereader is
#define FILELINE 40

//stores buttons locations
int buttons [15][4];
int bCount = 0;

//reference files
String update = "text.txt";
String bFile = "button.txt";

int x = 0;

//file control
unsigned long filePosition = 0;
char fileName[12];

// input text and parsing data
unsigned int input[7];
char Fileline [FILELINE];
char comand [15];

//timeing
unsigned long Time = 0;
#define UPDATE_TIME 1000

//buzzer on pin 28
short buzzer = 28;
short Buzz = EEPROM.read(9);
int pitch = 650;
