# C++ 算法题开发工作流（macOS + VS Code）

## 项目配置（基础信息）

- 源码：`chapter*/**/*.cpp`、`playground/*.cpp`
- 统一产物目录：`output/<源码相对目录>/<文件名无后缀>`
- 例子：`chapter1/two_pointer.cpp` -> `output/chapter1/two_pointer`
- Git：已初始化仓库，`output/` 不纳入版本管理
- 目标：按章节写题，当前文件可一键编译、运行、调试

## 最短使用路径

1. 打开任意 `.cpp` 文件。
2. `F6`：编译并运行当前文件。
3. `F7`：编译并调试当前文件。
4. `Cmd+Shift+B`：仅编译当前文件。

## 已配置内容

- 构建任务：`.vscode/tasks.json`
  - `g++ build active file`：编译当前文件（`-std=c++17 -O0 -g3 -Wall -Wextra`）
  - `g++ run active file`：单终端内“编译并运行”当前文件
- 调试配置：`.vscode/launch.json`
  - `C++ Debug (g++/CodeLLDB)`：编译 + 断点调试
  - `C++ Run (compile + run)`：编译 + 运行（不进调试）
- 工作区设置：`.vscode/settings.json`
  - C++ 标准：`c++17`
  - 默认编译器：`/usr/bin/clang++`（用于 IntelliSense）
- IntelliSense 配置：`.vscode/c_cpp_properties.json`
  - `intelliSenseMode: macos-clang-arm64`
  - `includePath: ${workspaceFolder}/**`

## 推荐快捷键

- `F6`：运行任务 `g++ run active file`
- `F7`：启动调试（使用当前工作区 `launch.json`）
- `Cmd+Shift+B`：执行默认构建任务（仅编译）

建议：

1. 运行/调试始终针对“当前活动文件”，先确认焦点在目标 `.cpp` 编辑器。
2. 若 F 键被系统功能占用，使用 `fn+F6` / `fn+F7`。
3. 调试异常时先 `Shift+F5` 停止会话，再重启调试。

## 直接运行在哪里

1. 最快：按 `F6`（会执行 `g++ run active file`）。
2. 菜单入口：`Terminal` -> `Run Task...` -> 选择 `g++ run active file`。
3. 结果位置：在下方面板的 `Terminal` 标签页（共享同一个任务终端，不会反复新开一堆）。

## 依赖扩展

- `vadimcn.vscode-lldb`（调试）
- `ms-vscode.cpptools`（语法与智能提示）

## 常见问题

- 报错：`The program "xxx" is already running. Please close it before compiling again.`
  - 原因：目标可执行文件仍被后台进程占用（窗口关了但进程未退出）。
  - 当前项目已处理：构建前会自动尝试清理占用该可执行文件的进程。
  - 仍出现时：先执行 `Shift+F5` 停止调试，再重新编译。
