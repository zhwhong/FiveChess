#### 网络交互
##### 网络交互的设计思想
为方便使用和实现, 游戏中得网络交互类采用继承CAsyncSocket类的方法实现。
通过这种方式可以很方便的进行Winsock网络通信, 而且代码比较精简

这个网络交互类主要有以下功能:
- 当前程序设置为主机时
    - 能够创建并监听一个指定端口

    - 当有客户机对指定端口连接时, 主机能够响应并建立相应的网络连接

    - 建立连接成功后, 能够发送数据到客户机

    - 建立连接成功后, 能够收到来自客户机的数据, 并调用相应处理函数

    - 当客户机断开连接时, 能够自动关闭当前连接端口, 并提示对方已经退出的信息

- 当前程序这职位客户机时

    - 能够创建并连接指定的IP地址和端口

    - 在连接成功后, 能够发送数据到主机

    - 在连接成功后, 能收到来自主机的数据, 并调用相应处理函数

    - 当主机断开连接后, 能够关闭当前连接端口, 并提示对方已经退出的信息

<div style="page-break-after: always;"></div>
##### 网络交互算法实现
- CConnect类的申明如下

```cpp
#ifndef __CONNECT_H__
#define __CONNECT_H__

#include <afxsock.h>

class CConnect: public CAsyncSocket {
public:
    CConnect();                 //构造函数
    virtual ~CConnect();        //析构函数
    // Implementation
protected:
    virtual void OnAccept( int nErrorCode );
    virtual void OnConnect( int nErrorCode );
    virtual void OnReceive( int nErrorCode );
    virtual void OnClose( int nErrorCode );
};

#endif
```

<div style="page-break-after: always;"></div>
- CConnect类的实现

```cpp
#include "Connect.h"
#include "FiveChessDlg.h"
#include "Board.h"

CConnect::CConnect() {
}

CConnect::~CConnect() {
}

/////////////////////////////////////////////////////////
// CFiveSocket member functions

void CConnect::OnAccept(int nErrorCode ) {
    CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
    pDlg->Accept();
    pDlg->SetMenuState(FALSE);
}

void CConnect::OnClose(int nErrorCode ) {
    CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();

    pDlg->MessageBox(_T("对方已经离开游戏，改日再较量不迟。"),
            _T("五子棋"),
            MB_ICONINFORMATION);
    pDlg->SetMenuState(TRUE);
    pDlg->m_board.SetWait(TRUE);
    pDlg->m_conncet.Close();
    pDlg->m_sock.Close();
    pDlg->m_bIsConnect = FALSE;
}

void CConnect::OnConnect(int nErrorCode ) {
    CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
    pDlg->Connect();
    pDlg->SetMenuState(FALSE);
}

void CConnect::OnReceive(int nErrorCode ){
    CBoard *pBoard = (CBoard *)AfxGetMainWnd()->GetDlgItem( IDC_BOARD );
    pBoard->Receive();
}
```
