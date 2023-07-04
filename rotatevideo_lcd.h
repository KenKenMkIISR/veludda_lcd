// ベクトル式VRAM　液晶出力プログラム　ヘッダーファイル　by K.Tanaka
// 画面上部は固定VRAM

#define VRAM_X   256 // VRAMの横方向最大値
#define VRAM_Y   256 // VRAMの縦方向最大値
#define TOPLINE 8 // 画面上部の固定表示行数
#define DISPXSIZE 256 // ベクトル式VRAMの液晶出力部分の横ピクセル数
#define DISPYSIZE 216 // ベクトル式VRAMの液晶出力部分の縦ピクセル数
#define DISPLEFTMARGIN 32 // 液晶出力左余白ピクセル数
#define DISPTOPMARGIN 8 // 液晶出力上余白ピクセル数

#define VERTICAL 0
#define HORIZONTAL 1
#define LCD0TURN 0
#define LCD180TURN 2

// LCD settings for Raspberry Pi Pico, ILI9341 SPI I/F
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

void LCD_Init(unsigned char align);
void LCD_Clear(unsigned short color);
void set_lcdalign(unsigned char align);
