### 游戏界面

界面在VC上用MFC编写完成，主要分为棋盘界面和弹出窗口界面。对话框是windows自带的，这样更简便。
对话框的类 为各个对话框添加对应的类：

- 棋盘界面：CFivechessDlg

- 游戏设置：CGamesetDlg

- 游戏帮助：CHelpgameDlg

- 关于游戏：CAboutGameDlg

- 网络设置：CSetupDlg

为每个类添加类向导，在生成的cpp文件中实现各个对话框的功能。
