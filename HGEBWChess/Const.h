#ifndef CONST_H
#define CONST_H


#define WWID 700
#define WHEI 600

#define START_X 30
#define START_Y 60
#define BOXLEN  60

#define BOARDSIZE 8

#define PI 3.14

enum ChessClr { Black = -1, None, White };

enum WinLose { BlackWin = -1, NoWin, WhiteWin, Even };

enum Direction { Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft };

enum Role { Computer, Human };

// 0：失败 1：成功 -1：（用户）没有落子
enum PlayResult { Nop = -1, Fail, Succ };

//控件位置
#define TITLE_X 190
#define TITLE_Y 20

#define BTN1_X 250
#define BTN1_WID 200
#define BTN1_HEI 60
#define PVCFIR_Y 150
#define PVCLAS_Y 220
#define PVP_Y 290
#define RPLY_Y 360
#define ESC_Y 430

#define BTN2_X (START_X + BOARDSIZE * BOXLEN + 20)
#define BTN2_WID 60
#define BTN2_HEI 30
#define BLBL_Y 60
#define WLBL_Y 100
#define NOWLBL_Y 140
#define TIMER_Y 180
#define SAVE_Y 220
#define LOAD_Y 260
#define UNDO_Y 300
#define EXIT_Y 340
#define HINT_Y 380

#endif