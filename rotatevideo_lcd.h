// ベクトル式VRAM　コンポジットカラー信号出力プログラム　PIC32MX370F512H用ヘッダーファイル　by K.Tanaka
// 画面上部は固定VRAM

#define VRAM_X   256 // VRAMの横方向最大値
#define VRAM_Y   256 // VRAMの縦方向最大値
#define TOPLINE 8 // 画面上部の固定表示行数

extern unsigned char VRAM[]; // ビデオメモリ
extern unsigned char TOPVRAM[]; // 画面上部の固定表示用ビデオメモリ
extern short vscanv1_x,vscanv1_y,vscanv2_x,vscanv2_y;	//映像表示スキャン用ベクトル
extern short vscanstartx,vscanstarty; //映像表示スキャン開始座標
// (vstartx,vstarty):画面左上になるVRAM上の座標（256倍）
// (vscanv1_x,vscanv1_y):画面右方向のスキャンベクトル（256倍）
// (vscanv2_x,vscanv2_y):画面下方向のスキャンベクトル（256倍）

void init_rotateLCD(unsigned char align); //液晶画面回転ライブラリ初期化
void clearscreen(void); //VRAMクリア、液晶画面クリア
void set_palette(unsigned char n,unsigned char b,unsigned char r,unsigned char g); //カラーパレット設定
void putlcdall(void); //液晶に画面データを転送
