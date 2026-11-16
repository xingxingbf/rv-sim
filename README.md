# 任务1：Linux 开发环境与 C 语言工程化

## 构建

```bash
make
```

## 运行

```bash
./sim
```

菜单：

- `1` 头插，输入 `姓名 分数`
- `2` 尾插，输入 `姓名 分数`
- `3` 按名删除，输入姓名
- `4` 按名查找，输入姓名
- `5` 打印整表
- `9` 释放整表
- `0` 退出

## 测试

```bash
bash tests/run_tests.sh
```

## 清理

```bash
make clean
```

## 目录

```text
include/   list.h io.h
src/       list.c io.c main.c
GDB/       GDB 实验程序
tests/     5 个边界用例
debug-log.md
study-log.md
```
