# 表达式求值器升级为小型编译器（1 小时计划）

## 目标（1h 内可完成）

把当前递归下降求值器升级为一个最小编译器前端：

1. 先词法分析（Tokenize）
2. 再语法分析（Parse）
3. 构造 AST
4. 打印 AST（树形文本）
5. 可选：基于 AST 再求值（Eval）

完成后你会得到一个更像编译器的结构，而不是“边解析边计算”。

---

## 当前代码主要问题

1. 全局状态过多：`expr`、`idx`、`ok`
2. 解析与求值耦合：`parse_*` 直接返回计算值
3. 错误处理不清晰：`panic()` 返回魔数
4. 缺少词法层：直接按字符解析，扩展困难
5. 无 AST：无法做打印、优化、代码生成等后续步骤

---

## 推荐目录（最小改造）

先不拆太多文件，先在一个 `.cpp` 里完成分层：

1. `Token` / `Lexer`
2. `AST` 节点定义
3. `Parser`
4. `AstPrinter`
5. `Evaluator`（可选）
6. `main()`

后续再拆成多文件。

---

## 最小文法（支持四则和括号）

```txt
expr   -> term ((+|-) term)*
term   -> factor ((*|/) factor)*
factor -> NUMBER | '(' expr ')'
```

这个文法已经是左结合，适合递归下降。

---

## AST 设计（够用版）

节点类型：

1. `NumberExpr`：保存整数值
2. `BinaryExpr`：保存操作符和左右子树

建议接口：

```cpp
struct Expr {
    virtual ~Expr() = default;
};

struct NumberExpr : Expr {
    int value;
};

struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};
```

内存管理用 `std::unique_ptr`，避免手动 `new/delete`。

---

## 关键模式（小而实用）

1. 递归下降（Parser 模式）
2. Visitor 思想（先做简单版）：
- 先写 `print(expr)` 和 `eval(expr)` 两个递归函数
- 有余力再升级为 Visitor 类层次

1h 内建议先不用完整 Visitor 模板，先把 AST 跑通。

---

## 代码风格规范（直接照这个执行）

1. 禁止 `using namespace std;`
2. 命名统一：
- 类型 `PascalCase`：`Token`, `Parser`, `BinaryExpr`
- 函数 `camelCase`：`parseExpr`, `parseFactor`
- 成员变量加后缀 `_`：`pos_`, `tokens_`
3. 错误处理：
- 用 `throw std::runtime_error("...")`
- 不再用 `panic()` + 魔数
4. 边界检查：
- 每次 `peek()/consume()` 前都判断 EOF
5. 函数职责单一：
- 词法只产 Token
- 语法只产 AST
- 求值只读 AST

---

## 1 小时实施清单（按顺序）

### 0-10 分钟：词法层

1. 定义 `enum class TokenKind`：
- `Number, Plus, Minus, Star, Slash, LParen, RParen, Eof`
2. 定义 `Token { TokenKind kind; int value; }`
3. 写 `Lexer::tokenize()`：
- 跳过空白
- 读取多位整数
- 识别操作符与括号

验收：输入 `1000*(3+5)` 输出正确 token 序列。

### 10-30 分钟：Parser + AST

1. 把 `parseExpr/parseTerm/parseFactor` 改为返回 `std::unique_ptr<Expr>`
2. `parseFactor`：
- `NUMBER` -> `NumberExpr`
- `(` expr `)` -> 返回子表达式
3. `parseExpr/parseTerm`：
- 循环吃同优先级运算符
- 每次构造 `BinaryExpr`

验收：能构造 AST，不做求值也能通过。

### 30-45 分钟：AST 打印

写 `printAst(const Expr*, int indent)`：

1. `NumberExpr` 打印：`Number(123)`
2. `BinaryExpr` 打印：
- `Binary(+)`
- 下一层打印 lhs/rhs（缩进 +2）

验收：`1+2*3` 打印出树结构（能看出 `*` 优先级高于 `+`）。

### 45-55 分钟：基于 AST 求值（可选但推荐）

写 `eval(const Expr*) -> int`：

1. Number 直接返回
2. Binary 递归计算 lhs/rhs 后按 op 计算

验收：输入表达式可得到正确值。

### 55-60 分钟：清理

1. 删除全局变量
2. 删除 `panic()` 和魔数
3. 错误信息统一：`unexpected token ...`
4. 自测 5 组数据

---

## 最低测试集（直接复制）

1. `1+2*3` -> `7`
2. `(1+2)*3` -> `9`
3. `1000*(3+5)` -> `8000`
4. `42` -> `42`
5. `1+(2*(3+(4*5)))` -> `47`

错误输入测试：

1. `1+`（缺右操作数）
2. `(1+2`（缺右括号）
3. `1+*2`（非法 token 序列）

---

## 完成标准（Done Definition）

满足以下 5 条就算完成：

1. 代码中不再有全局状态 `expr/idx/ok`
2. 有独立 Lexer，Parser 不直接读字符
3. Parser 输出 AST，不直接算值
4. 能打印 AST 树
5. 对非法输入给出明确报错，不崩溃

---

## 下一步（2-3h 扩展）

1. 支持一元负号（`-x`）
2. 支持变量与赋值（`a=1+2`）
3. 引入完整 Visitor（`PrinterVisitor`, `EvalVisitor`）
4. AST 节点加源码位置信息（行列号）
