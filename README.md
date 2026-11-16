# 任务1：Linux 开发环境与 C 语言工程化

这是任务1的代码。链表在 `list.c`，菜单在 `io.c`，`main.c` 只负责调用。

## 编译

```bash
make
```

## 运行

```bash
./sim
```

菜单：

- 1 头插，输入姓名和分数
- 2 尾插，输入姓名和分数
- 3 按名删除
- 4 按名查找
- 5 打印整表
- 9 释放整表
- 0 退出

## 测试

```bash
bash tests/run_tests.sh
```

## 清理

```bash
make clean
```

一开始菜单是写在 `main.c` 里的，后来按任务书拆成了 `io.c` / `io.h`。如果 `make` 报错，先 `make clean` 再 `make`。
