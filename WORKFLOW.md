# C++ 算法题开发工作流（macOS + VS Code）

## 项目约定

- 源码：`chapter1/*.cpp`、`playground/*.cpp`
- 统一产物目录：`output/<源码相对目录>/<文件名无后缀>`
- 例子：`chapter1/two_pointer.cpp` -> `output/chapter1/two_pointer`

## 已配置内容

- 构建任务：`.vscode/tasks.json`
  - `g++ build active file`：编译当前文件（`-std=c++17 -O0 -g3 -Wall -Wextra`）
  - `g++ run active file`：单终端内“编译并运行”当前文件
- 调试配置：`.vscode/launch.json`
  - `C++ Debug (g++/CodeLLDB)`：编译 + 断点调试
  - `C++ Run (compile + run)`：编译 + 运行（不进调试）

## 推荐快捷键

- `F5`：启动当前选中的调试配置
- `Ctrl+F5`：运行当前选中的配置（无调试）
- `Cmd+Shift+B`：执行默认构建任务（编译当前文件）

建议：

1. 想断点调试时，先在 Run and Debug 中选择 `C++ Debug (g++/CodeLLDB)`，然后按 `F5`。
2. 想一把跑结果时，先选择 `C++ Run (compile + run)`，然后按 `Ctrl+F5`。
3. 任务始终针对“当前活动文件”，确保光标在 `.cpp` 文件里再执行构建或运行。

## 直接运行在哪里

1. 最快：按你绑定的 `Cmd+R`（会执行 `g++ run active file`）。
2. 菜单入口：`Terminal` -> `Run Task...` -> 选择 `g++ run active file`。
3. 结果位置：在下方面板的 `Terminal` 标签页（共享同一个任务终端，不会反复新开一堆）。

## 给 Compile&Run 绑定专用快捷键（可选）

VS Code 的快捷键是用户级设置。可在 Keyboard Shortcuts(JSON) 里添加：

```json
{
    "key": "cmd+r",
    "command": "workbench.action.tasks.runTask",
    "args": "g++ run active file",
    "when": "editorTextFocus"
}
```

这样 `Cmd+R` 就会执行“编译并运行当前文件”。

## 依赖扩展

- `vadimcn.vscode-lldb`（调试）
- `ms-vscode.cpptools`（语法与智能提示）

> 注意：不要使用 C/C++ 的 Debug File 快捷入口，它在 mac 上走 MI 模式，容易触发 `--interpreter=mi` 类报错。

## 常见问题

- 报错：`The program "xxx" is already running. Please close it before compiling again.`
  - 原因：目标可执行文件仍被后台进程占用（窗口关了但进程未退出）。
  - 当前项目已处理：构建前会自动尝试清理占用该可执行文件的进程。
  - 仍出现时：先执行 `Shift+F5` 停止调试，再重新编译。
