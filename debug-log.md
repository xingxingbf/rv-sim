# GDB 调试记录

以下命令和输出都按终端截图整理，没截图里没出现过的命令。编译统一用：

```bash
gcc -g -O0 文件名.c -o 程序名
```

## 场景 1：断点、单步，看循环变量和数组

- 现象：`text.c` 能输出 `sum`，但不知道循环中间 `i` 和 `xb[i]` 是怎么变的。
- 假设：`i` 从 0 到 4，`xb[i] = i * 2`，最后 `sum` 应该是 20。
- 操作：

```text
gdb ./text
break 9
run
next
print i
print xb[0]
print xb[1]
print xb[2]
next
print i
next
print i
next
print i
print sum
continue
```

关键输出：

```text
Breakpoint 1, main () at text.c:9
9       for (i = 0; i < 5; i++)
(gdb) next
11          sum = sum + xb[i];
(gdb) print i
$1 = 0
(gdb) print xb[0]
$3 = 0
(gdb) print xb[1]
$4 = 2
(gdb) print xb[2]
$5 = 4
...
(gdb) print i
$6 = 1
...
(gdb) print i
$7 = 2
...
(gdb) print i
$8 = 3
(gdb) print sum
$9 = 6
(gdb) continue
Continuing.
sum = 32787
```

后来重新编译又跑了一次：

```text
vim text.c
gcc -g -O0 text.c -o text
gdb ./text
break 9
run
continue
```

输出变成：

```text
sum = 20
```

- 结论：`xb[0]=0`、`xb[1]=2`、`xb[2]=4`，循环变量确实在递增。第一次跑出 `sum=32787`，重新编译后是 `sum=20`，说明当时运行的不是同一份编译结果；重新编译后结果正常。

## 场景 2：空指针段错误

- 现象：`./bkcs` 直接段错误，只打印 `Segmentation fault (core dumped)`。
- 假设：`崩溃测试.c` 里 `int *p = NULL;` 之后直接 `*p = 100;`，是空指针解引用。
- 操作：

```text
gcc -g -O0 崩溃测试.c -o bkcs
gdb ./bkcs
run
bt
print p
info locals
```

关键输出：

```text
Program received signal SIGSEGV, Segmentation fault.
0x0000555555555161 in main () at 崩溃测试.c:5
5           *p = 100;
(gdb) bt
#0  0x0000555555555161 in main () at 崩溃测试.c:5
(gdb) print p
$1 = (int *) 0x0
(gdb) info locals
p = 0x0
```

- 结论：崩在 `崩溃测试.c:5`，`p` 是 `0x0`，确实是空指针解引用。改法是写入前判断 `p != NULL`，或者让 `p` 指向有效内存。

## 场景 3：条件断点和打印地址

- 现象：`all345` 里 `p` 从 `&a` 开始遍历，想在 `p->v == 5` 时停下。
- 假设：条件断点可以只在 `v = 5` 时命中。
- 操作：

```text
gdb ./all345
set pagination off
b 25 if p->>=5
b 25 if p->v == 5
run
p p
p &b
```

中间第一次写条件时终端报：

```text
A syntax error in expression, near `>=5'.
```

改成 `b 25 if p->v == 5` 后：

```text
Breakpoint 1 at 0x1204: file all345.c, line 25.
...
Breakpoint 1, main () at all345.c:25
25          printf("v = %d\n", p->v);
(gdb) p p
$1 = (Node *) 0x7ffffffdee0
(gdb) p &b
$2 = (Node *) 0x7ffffffdee0
```

- 结论：条件断点要写成 `break 行号 if 条件`，第一次漏了成员名 `v`，所以语法错误。命中时 `p` 和 `&b` 是同一个地址。

## 场景 4：watch 抓变量被改坏

- 现象：`all345` 里 `box.total` 初始为 0，循环只写 `box.xb[0..3]`，最后变成 103。
- 假设：`xb` 只有 3 个元素，循环写了 4 次，`xb[3]` 越界写到 `total`。
- 操作：

```text
break 31
run
watch box.total
continue
p i
p box.xb
```

关键输出：

```text
Breakpoint 2, main () at all345.c:31
31          for (i = 0; i < 4; i++) {
(gdb) watch box.total
Hardware watchpoint 3: box.total
(gdb) continue
Continuing.

Hardware watchpoint 3: box.total

Old value = 0
New value = 103
main () at all345.c:31
31          for (i = 0; i < 4; i++) {
(gdb) p i
$3 = 3
(gdb) p box.xb
$4 = {100, 101, 102}
```

- 结论：`i=3` 时 `box.total` 从 0 变成 103，`box.xb` 只有 3 个元素，`box.xb[3]` 越界写到了 `total`。把循环条件改成 `i < 3` 即可。

## 场景 5：调用栈回溯

- 现象：继续运行 `all345` 后触发 SIGSEGV，停在 `level3`，需要看它是从哪一层调过来的。
- 假设：`level1 -> level2 -> level3`，`level2` 把 `p->next` 传给 `level3`。
- 操作：

```text
bt
frame 1
info args
```

关键输出：

```text
Program received signal SIGSEGV, Segmentation fault.
0x0000555555555179 in level3 (p=0x0) at all345.c:13
13      int level3(Node *p) { return p->v; }
(gdb) bt
#0  level3 (p=0x0) at all345.c:13
#1  level2 (p=0x7ffffffdee0) at all345.c:14
#2  level1 (head=0x7ffffffdee0) at all345.c:15
#3  main () at all345.c:40
(gdb) frame 1
#1  level2 (p=0x7ffffffdee0) at all345.c:14
(gdb) info args
p = 0x7ffffffdee0
```

- 结论：调用链是 `main -> level1 -> level2 -> level3`；`level2` 收到的 `p` 是 `0x7ffffffdee0`，但它传给 `level3` 的 `p->next` 是 `0x0`，所以 `level3` 里 `p->v` 触发段错误。
