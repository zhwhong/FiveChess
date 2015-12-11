#### 整体架构类设计

在项目实现过程中参考了网上的一些代码,但问题多多,主要表现在：

- 多数为互相抄袭,无新意,且不验证其正确性

- 仅仅实现了主要功能,很多细节和Bug都没改正

- 基本无移植性可言

- 代码可读性差、不强壮性,排版混乱,有数组越界溢出等等

- 大部分逻辑不严谨,个别的不简洁,几百行能解决的却写了几千行

- 画面闪烁问题

最后在大家的努力之下,我们自己完成了本次实验。

<div style="page-break-after: always;"></div>
- common.h 主要定义了整个程序使用的公用变量和信息

```cpp
//  公用头文件   目前只被ChessAI.h 和 Chess.h 共用；
//	此项目默认为15*15的五子棋,如需应用到象棋和其他棋类，则需自行修改；
//
//  注意: 人机对战时，默认人为黑方(先下)，机器为白方（后下）。

const int MAXCREASE	= 4;
// 此项目为五子棋，所以最大数目为5-1
const UINT ROWS = 15;
// 棋盘的行数
const UINT COLUMNS = 15;
// 棋盘的列数
enum  enumChessColor {NONE, WHITE, BLACK};
// NONE = 0 : 无棋子，WHITE =1 : 白方棋子，BLACK =2 : 黑方棋子

// 相同颜色计数的加法器
void SameColorAdder(UINT uiCol,
                    UINT uiRow,
                    enumChessColor emChessColor,
                    BOOL bResetCount,
                    int& iColorCount,
                    BOOL& bOver,
                    const enumChessColor iChess[][ROWS],
                    int* piBlankCount = NULL);

// 在某点处各方向相同颜色的棋子数
void GetSameColor(UINT uiCol,
                    UINT uiRow,
                    enumChessColor emChessColor,
                    int* iSameColor,
                    const enumChessColor iChess[][ROWS],
                    int* piCreaseDirect = NULL,
                    BOOL bIgnoreBlank = FALSE,
                    int* piBlankFlag = NULL);

// 某点是否在棋盘中
BOOL PtInBroad(UINT	uiCol, UINT uiRow);
```

<div style="page-break-after: always;"></div>
- AI.h 主要是在人机对战时,有四种不同等级的机器智能

```cpp
// 以下AI下棋速度逐渐减慢，CPU占用逐渐增高，智力也逐渐增高
// AIFoolish         虽然智力最低，但其占用的内存和CPU是最低的，
// AIPrimary         占用内存低，占用CPU也低
// AIMiddle          内存和CPU占用居中
// AIHigh            占用内存低，占用CPU高

// 这里默认机器为白方

//AIBlock 阻碍法AI：尽力阻碍对手成5连 智力较低      
BOOL AIFoolish(POINT& ptPosWhite,
            POINT ptPosBlack,
            enumChessColor emChessColor,
            const enumChessColor emChess[][ROWS]);
// 初级AI
BOOL AIPrimary(POINT &pt,
            enumChessColor emChess[][ROWS]);                     
// 中级AI     
BOOL AIMiddle(POINT &pt,
            const enumChessColor emChess[][ROWS]);
// 高级AI   博弈树,极大极小alpha-beta剪枝优化
BOOL AIHigh(POINT &pt,
            enumChessColor emChess[][ROWS]);  
```

<div style="page-break-after: always;"></div>
- Chess.h 整个游戏的框架设置

```cpp
class CChess {
public:
    CChess(void);
    ~CChess(void);

    void Init(CRect rect);
    void Draw(CDC* pDC);        // 画棋局
    void SetPiecePos(CPoint ptCurrent);        // 设置当前棋子的位置    下棋函数

    void NewGame();     // 新游戏
    BOOL Regret();     // 悔棋
    void SetVSMode(enumVSMode emVSMode);       // 设置对战模式	enumVSMode
    void SetAIDepth(int emAIDepth);        // 设置AI智能程度
    enumWinFlag GetWinFlag();      // 获取输赢状况
    CRect GetRectBoard();      // 获取棋盘区域
private:
    enumChessColor m_iPositionPiece[COLUMNS][ROWS];
            // 棋子的信息
    CChessDraw m_chessdraw;
            // 棋局绘制类
    CRect m_rcBoard;
            // 棋盘区域
    CPoint m_ptCurrent;
            // 棋子当前位置
    enumWinFlag m_emWin;
            // 输赢状况
    enumVSMode m_emVSMode;
            // 对战模式
    STC_REGRET m_stcLastPos;
            // 记录最近一次的下棋位置
    BOOL m_bTurnBlack;
            // 是否轮到黑方下棋
    int m_emAIDepth;
            // AI智能程度,为方便外部调用SetAIDepth()，所以设为了int类型

    BOOL IsWin(UINT uiCol,
            UINT uiRow,
            enumChessColor   emChessColor);
            // 在第uiCol列第uiRow行，判断是否结束，若结束则返回TRUE
    BOOL GetBestPosByAI(UINT& uiCol,
            UINT&	uiRow,
            enumChessColor emEnemyChessColor  = BLACK);
            // 获取最好的下棋位置，机器都为白色
};
```

<div style="page-break-after: always;"></div>
- 判断输赢

```cpp
//-----------------------  判断输赢  --------------------------
    if(IsWin(uiPosX, uiPosY, m_iPositionPiece[uiPosX][uiPosY])) {
        m_ptCurrent = CPoint(uiPosX, uiPosY);
        return; // 已分出胜负
    }
```

- 控制悔棋（只准悔棋一步，若已分胜负，不可悔棋）

```cpp
//----------------------- 记录上一次的棋子位置  -------------------
    if((PERSON_VS_PERSON  == m_emVSMode)
        || (m_bTurnBlack && (PERSON_VS_MACHINE == m_emVSMode))){
            m_stcLastPos.ptLastCurPoint = m_ptCurrent;           
        }
    if(m_bTurnBlack) {
        m_stcLastPos.ptBlack = CPoint(uiPosX, uiPosY)；
    }
    else {
        m_stcLastPos.ptWhite = CPoint(uiPosX, uiPosY);
    }
    m_stcLastPos.iPieceNum++;
    m_ptCurrent  = CPoint(uiPosX, uiPosY);
```


- 下棋控制

```cpp
// ----------------------  轮到白方下棋  -------------------------
    m_bTurnBlack = ! m_bTurnBlack;
    if((!m_bTurnBlack && (PERSON_VS_MACHINE == m_emVSMode))) {
        if(!GetBestPosByAI(uiPosX,
                uiPosY,
                (!m_bTurnBlack) ? BLACK : WHITE)) {
            return; // 已分出胜负
        }
    }
    if(PERSON_VS_PERSON == m_emVSMode) {
        break;    // 如果是人人对战，则退出循环
    }
```

<div style="page-break-after: always;"></div>
- 棋局评估

```cpp
// SCORE_BLACK[i][j]
// 表示连续j+1个黑棋(且两边共i个空位)的评分
// i = 0表示两边都被堵住， i = 1表示有一边没被堵住， i = 2 表示两边都有空位

const double SCORE_WHITE[][5] = {
    {0, 0, 0, 0, 10000000},
    {1, 25, 500, 2500, 10000000},
    {5, 100, 2500, 50000, 10000000}
};
const double SCORE_BLACK[][5] = {
    {0, 0, 0, 0, -1000000},
    {-5, -100, -500, -10000, -1000000},
    {-25, -500, -10000, -250000, -1000000}
};

// 这里假设i=0的分数最低，i>0时，子越多越好，
// 如：[1][3]>[2][2]  即死四>活三，因为再下一棋，死四即成五连
// 死三>活二,因为己方再下一棋,可以使死三成死四,或者活二成活三,就变成了死四>活三
// 敌方再下一棋，可以使死四变成死棋(两边都被堵)，或者活三变成死三

// 为了不使分数重叠，[i+1][j] >= 4*[i][j] +1，[i][j+1] >= 4*[i+1][j] +1
// 这里采取向最高位取整，即9取整为10,     81取整为100
// 黑方的负分要更大,这样多一个黑方会大大拉低总分,就使白棋去堵黑棋
// 这里黑棋的负分为白棋的10倍, 当然，五子相连时白方分数要大，不然总是去堵黑方，自己不赢

/*
白方活三 > 黑方死四
所以当白方有活二，黑方有死三时，应该填活三位置，
这样即使黑方填成了死四，那么也只需要一步即可拦住
*/
```

<div style="page-break-after: always;"></div>
- Alpha-beta剪枝控制：

```cpp
long double AlphaBetaMax(long double dbAlphaMin,
                long double dbBetaMax,
                int iDepthleft, enumChessColor emChess[][ROWS],
                POINT& ptBest) {
    ptBest = CPoint(-1, -1);
        // 如果函数调用完后，ptBest还是CPoint(-1, -1)，说明棋子下满了
    if(iDepthleft == 0) {
        return ScoreEvaluate(emChess);
    }
    CPoint  ptTmp;
        // 做为一个参数传递，不要关心

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < ROWS; j++) {
            if(NONE == emChess[i][j]){
                if(ptBest.x == -1) {
                    ptBest = CPoint(i, j);
                        // 如果是第一次进入
                }

                emChess[i][j] = WHITE ;
                    // 走一步棋

                long double dbScore = AlphaBetaMin(dbAlphaMin,
                                            dbBetaMax,
                                            iDepthleft - 1,
                                            emChess,ptTmp);
                    // 找出Min走棋后能找到的最大分数

                emChess[i][j] = NONE;
                    // 撤销上面走的那一步棋

                if(dbScore >= dbBetaMax) {
                    ptBest = CPoint(i, j);
                    return dbBetaMax;
                        // dbBetaMax-cutoff
                }
                if(dbScore > dbAlphaMin) {
                    ptBest = CPoint(i, j);
                    dbAlphaMin = dbScore;
                        // dbAlphaMin acts like max in MiniMax
                }
            }
        }
    }
    return dbAlphaMin;  //Max
}
```

<div style="page-break-after: always;"></div>
```cpp
long double AlphaBetaMin(long double dbAlphaMin,
                long double dbBetaMax,
                int iDepthleft, enumChessColor emChess[][ROWS],
                POINT& ptBest) {
    ptBest = CPoint(-1, -1);
    if(iDepthleft == 0) {
        //  当AlphaBetaMax()中iDepthleft为2时，加不加负号都差不多
        // 当iDepthleft为3时，加负号能很快剪枝得出结果，但结果并不正确，所以这里不加负号
        return ScoreEvaluate(emChess);      
    }

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < ROWS; j++) {
            if(NONE == emChess[i][j]) {
                emChess[i][j] = BLACK ;
                    // 走一步棋

                long double dbScore = AlphaBetaMax(dbAlphaMin,
                                            dbBetaMax,
                                            iDepthleft - 1,
                                            emChess,
                                            ptBest);
                    // 找出Max走棋后能找到的最小分数

                emChess[i][j] = NONE;
                    // 撤销上面走的那一步棋

                if(dbScore <= dbAlphaMin) {   
                    ptBest = CPoint(i, j);
                    return dbAlphaMin;
                    // dbAlphaMin-cutoff
                }
                if(dbScore < dbBetaMax) {
                    ptBest = CPoint(i, j);
                    dbBetaMax = dbScore;
                    // dbBetaMax acts like min in MiniMax
                }
            }
        }
    }
    return dbBetaMax; // Min
}
```
