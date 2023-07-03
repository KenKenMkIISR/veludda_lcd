// ベクトル式VRAM　コンポジットカラー信号出力プログラム　PIC32MX370F512H用ヘッダーファイル　by K.Tanaka
// 画面上部は固定VRAM

#define VRAM_X   256 // VRAMの横方向最大値
#define VRAM_Y   256 // VRAMの縦方向最大値
#define TOPLINE 8 // 画面上部の固定表示行数

#define VERTICAL 0
#define HORIZONTAL 1
#define LCD0TURN 0
#define LCD180TURN 2

// LCD settings
#define LCD_CS 13
#define LCD_DC 10
#define LCD_RESET 11
#define LCD_SPI_TX 15
#define LCD_SPI_RX 12
#define LCD_SPI_SCK 14
#define LCD_SPICH spi1
#define LCD_COLUMN_RES 240
#define LCD_ROW_RES 320
#define LCD_SPI_BAUDRATE (64*1000*1000)
#define LCD_SPI_BAUDRATE_R (15*1000*1000)

extern int LCD_ALIGNMENT;

extern unsigned char *VRAM; // ビデオメモリ
extern unsigned char *TOPVRAM; // 画面上部の固定表示用ビデオメモリ

// (vstartx,vstarty):画面左上になるVRAM上の座標（256倍）
// (vscanv1_x,vscanv1_y):画面右方向のスキャンベクトル（256倍）
// (vscanv2_x,vscanv2_y):画面下方向のスキャンベクトル（256倍）
extern short vscanv1_x,vscanv1_y,vscanv2_x,vscanv2_y;	//映像表示スキャン用ベクトル
extern short vscanstartx,vscanstarty; //映像表示スキャン開始座標

void init_rotateLCD(unsigned char align); //液晶画面回転ライブラリ初期化
void clearscreen(void); //VRAMクリア、液晶画面クリア
void set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g); //カラーパレット設定
void putlcdall(void); //液晶に画面データを転送

void LCD_WriteComm(unsigned char comm);
void LCD_WriteData(unsigned char data);
void LCD_WriteData2(unsigned short data);
void LCD_WriteDataN(unsigned char *b,int n);
void LCD_WriteDataColor(unsigned short data);
void LCD_WriteData_notfinish(unsigned char data);
void LCD_WriteData2_notfinish(unsigned short data);
void LCD_WriteDataColor_notfinish(unsigned short data);
void LCD_WriteDataN_notfinish(unsigned char *b,int n);
void checkSPIfinish(void);
void LCD_Init(void);
void LCD_setAddrWindow(unsigned short x,unsigned short y,unsigned short w,unsigned short h);
void LCD_SetCursor(unsigned short x, unsigned short y);
void LCD_Clear(unsigned short color);
void LCD_continuous_output(unsigned short x,unsigned short y,unsigned short color,int n);
void drawPixel(unsigned short x, unsigned short y, unsigned short color);
unsigned short getColor(unsigned short x, unsigned short y);
void set_lcdalign(unsigned char align);
