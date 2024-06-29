MyShell 用户手册

欢迎使用 MyShell，这是一个基本的命令行shell程序，允许用户执行多种命令和操作。

特性
----
- 支持基本的命令行操作。
- 可以执行脚本文件。
- 显示环境变量。
- 清屏和列出目录内容的命令。

安装
----
MyShell 需要在支持 POSIX 标准的系统上编译。确保您的系统上安装了 GCC 编译器。

1. 克隆仓库到本地机器：
   git clone https://github.com/yourusername/MyShell.git
2. 进入项目目录：
   cd MyShell
3. 编译 MyShell：
   make

使用
---
运行 MyShell 程序：

./MyShell

你将看到一个 `==>` 提示符，等待用户输入命令。

命令列表
--------
- clr - 清屏。
- ls [directory] - 列出指定目录或当前目录的内容。
- environ - 打印所有环境变量。
- echo [message] - 打印消息。
- script [path] - 执行指定路径的脚本文件。
- quit - 退出 MyShell。

执行脚本
--------
MyShell 允许你执行存储在文件中的命令列表。要执行脚本，请使用以下命令：

script /path/to/your/script.sh

确保脚本文件具有可执行权限。

许可
----
MyShell 是开源软件

感谢您选择 MyShell。我们希望这个工具能为您带来便利！
 
