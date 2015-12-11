#### 游戏设置

游戏设置的响应函数如下：

```cpp
void CFiveChessDlg::OnUpdateSetGameMenu(CCmdUI* pCmdUI) {
    m_gameset.DoModal();
    // TODO: Add your command update UI handler code here
}
```

其中m_gameset是游戏设置CGamesetDlg类的一个对象。鼠标左键点击游戏中设置时,弹出窗口如上图所示。
窗口中添加了3个单选按钮以及2个按钮,确定按钮的响应函数的实现如下：

```cpp
void CGamesetDlg::OnOk1() {
    if(flag == 1) {
        WritePrivateProfileString("WEB", "STATUS", "true", ".\\config.ini");
    }
    else if(flag == 2) {
        WritePrivateProfileString("PVC", "STATUS", "true", ".\\config.ini");
    }
    else if(flag == 3) {
        WritePrivateProfileString("PVP", "STATUS", "true", ".\\config.ini");
    }
    CDialog::OnOk();
    // TODO: Add your control notification handler code here
}
```

flag用来记录用户选择的是网络对战、人人对战、人机对战这3个单选按钮中的哪一个,并将其记录在config.ini文件中。

在前面的开始按钮那里,就会查看config_.ini文件,如果记录的是网络对战就调用网络设置窗口
