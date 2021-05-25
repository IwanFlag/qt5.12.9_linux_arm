1.打包指令

windeployqt  draw_label.exe





2.国际化指令

**1）lupdate –verbose draw_label.pro								//生成相应的.ts 文件**

**2）linguist																		   //启动Linguist语言翻译工具，可以翻译相应可见字符串**

**3）lrelease –verbose draw_label.pro						 //将翻译好的文件生成.qm文件**