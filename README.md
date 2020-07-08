# Girl-Frontline-colleagues-
Self-made girl front fan small game, code construction platform Qt5, game video see Bilibili user UbuntuCXY contribute.

# 目录索引：
girl frontline > 可执行文件目录，可单独打包下载该文件夹进行本地解压，双击其bin目录下的GirlFrontline.exe文件即可运行。
GirlFrontline  > 源码工程目录，Qt版本5.4.1。
music          > 背景音乐目录
picture        > 游戏素材图片

# 增加游戏地图的方法
打开源码目录的 mapinfo.h 文件， 在Maps数组中最后添加一个MAPWIDTH * MAPHEIGHT 大小的二维数组，每个元素值代表相应位置的地图元素，地图元素的值参考 枚举变量MapElement。

# 增加人形的方法
打开源码目录下的 figureinfo.h 文件， 按照人形编号顺序在 FiguresData 相应位置添加一行人形属性，并在上方添加相应的编号宏，如有必要还需修改其他人形的宏，使得宏值与其在FiguresData中的顺序一致。另外，还需在picture目录下加入其等待、开火、移动4个方向的gif动画，大小为50 * 50，命名规则为“人形名_动作_方向”。

# 增加游戏任务的方法：
打开源码目录下的 missioninfo.h ，在 missions 数组末尾仿照前面三个任务添加一个新的任务，并且手动将宏 MISSIONUM 加一，任务格式在文件中已给出。

如有问题，请联系1484652026@qq.com。
