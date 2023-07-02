// ベクトル式VRAM　LCD出力プログラム　Raspberry Pi Pico用　by K.Tanaka
// LCD ILI9341
// 画面上部に固定表示領域あり
//
// VRAM解像度256×256ドット＋最上部固定8行
// 画面出力解像度256×216ドット＋最上部8行
// 256色同時表示、1バイトで1ドットを表す
// カラーパレット対応

// (vstartx,vstarty):画面左上になるVRAM上の座標（256倍）
// (vscanv1_x,vscanv1_y):画面右方向のスキャンベクトル（256倍）
// (vscanv2_x,vscanv2_y):画面下方向のスキャンベクトル（256倍）


#include "rotatevideo_lcd.h"
#include "LCDdriver.h"
#include "hardware/spi.h"

// グローバル変数定義
unsigned char VRAM[VRAM_X*VRAM_Y] __attribute__ ((aligned (4))); //VRAM
unsigned char TOPVRAM[VRAM_X*TOPLINE] __attribute__ ((aligned (4))); //画面上部の固定VRAM
short vscanv1_x,vscanv1_y,vscanv2_x,vscanv2_y;	//映像表示スキャン用ベクトル
short vscanstartx,vscanstarty; //映像表示スキャン開始座標
short vscanx,vscany; //映像表示スキャン処理中座標

//カラー信号波形テーブル
//256色分のカラーパレット
unsigned short ClTable[256];

void lineoutput(unsigned short x,unsigned short y,unsigned short vx,unsigned short vy,unsigned char *vp)
{
	int i;
	unsigned short d;
	for(i=0;i<256;i++){
		d=ClTable[*(vp+(y&0xff00)+(x>>8))];
		while (!spi_is_writable(LCD_SPICH))
            tight_loop_contents();
        spi_get_hw(LCD_SPICH)->dr = d&0xff;
		while (!spi_is_writable(LCD_SPICH))
            tight_loop_contents();
        spi_get_hw(LCD_SPICH)->dr = d>>8;
		x+=vx;
		y+=vy;
	}
	checkSPIfinish();
}

//液晶に画面データを転送
void putlcdall(void){
	unsigned short x,y,i;
	for(i=0;i<TOPLINE;i++){
		LCD_SetCursor(32,i+8);
		lineoutput(0,i<<8,0x100,0,TOPVRAM);
	}
	x=vscanstartx;
	y=vscanstarty;
	for(i=0;i<216;i++){
		LCD_SetCursor(32,i+16);
		lineoutput(x,y,vscanv1_x,vscanv1_y,VRAM);
		x+=vscanv2_x;
		y+=vscanv2_y;
	}
}

//  VRAMクリア、液晶画面クリア
void clearscreen(void)
{
	unsigned int *vp;
	int i;
	vp=(unsigned int *)VRAM;
	for(i=0;i<VRAM_X*VRAM_Y/4;i++) *vp++=0;
	vp=(unsigned int *)TOPVRAM;
	for(i=0;i<VRAM_X*TOPLINE/4;i++) *vp++=0;
	LCD_Clear(0);
}

void set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g)
{
	// カラーパレット設定
	// n:パレット番号0-255、r,g,b:0-255
	// R5G6B5形式で保存、ただし上位と下位を入れ替え

	unsigned short c;
	c=((r&0xf8)<<8)+((g&0xfc)<<3)+((b&0xf8)>>3);
	ClTable[n]=c<<8;
	ClTable[n]+=c>>8;
}

// 液晶画面回転ライブラリ初期化
void init_rotateLCD(unsigned char align)
{
	unsigned int i;
	LCD_Init();
	set_lcdalign(align);

	//カラーパレット初期化
	for(i=0;i<8;i++){
		set_palette(i,255*(i&1),255*((i>>1)&1),255*(i>>2));
	}
	for(i=0;i<8;i++){
		set_palette(i+8,128*(i&1),128*((i>>1)&1),128*(i>>2));
	}
	for(i=16;i<256;i++){
		set_palette(i,255,255,255);
	}
	//VRAMスキャンベクトル初期化
	vscanv1_x=256;
	vscanv1_y=0;
	vscanv2_x=0;
	vscanv2_y=256;
	vscanstartx=0;
	vscanstarty=0;

	clearscreen();
}
