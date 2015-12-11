#### 网络通信数据详细
##### 棋子消息数据包

- 棋子位置数据是传输中得主要数据, 在这里把棋盘当做二维数组.所以实际传输的棋子在二维数组中的行列号

- 游戏控制数据中得"和棋"是指游戏运行中进行"和棋"操作时, 发送的数据包, 可分为以下几类
    - 和棋请求

    - 同意和棋回应
    
    - 拒绝和棋回应

##### 其他扩展数据
其他扩扎信息, 是留给以后游戏扩展使用

##### 数据结构

```cpp
#ifndef __CONNECT_DATA_H__
#define __CONNECT_DATA_H__

#define MSG_PUTSTEP     0x01        // 落子消息
#define MSG_DRAW        0x02        // 和棋请求消息
#define MSG_AGREE_DRAW  0x03        // 同意和棋消息
#define MSG_REFUSE_DRAW 0x04        // 拒绝和棋消息
#define MSG_EXTERN      0x05        // 其他消息

typedef struct _tagMsgStruct {
    USHORT len;
    // 消息ID
    BYTE msgType;
    // 落子信息
    int x;
    int y;
    int color;
    // 其他消息内容
    BYTE byMsg[128];
} MSGSTRUCT;

#endif
```
