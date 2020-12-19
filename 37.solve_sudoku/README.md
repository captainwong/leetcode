

## norvig test result

### CPU: I7-8700

OVERALL: 

```
solved 50 of 50 easy50 puzzles, total 966ms, avg 19.32ms, max 218ms
solved 90 of 95 top95 puzzles, total 540807ms, avg 5692.71ms, max 137558ms
solved 11 of 11 hardest puzzles, total 799ms, avg 72.64ms, max 230ms
```
DETAILED: [norvig_I7-8700.txt](./norvig_I7-8700.txt)

### I5-4590

OVERALL: 

```
solved 50 of 50 easy50 puzzles, total 634ms, avg 12.68ms, max 189ms
solved 90 of 95 top95 puzzles, total 550935ms, avg 5799.32ms, max 131285ms
solved 11 of 11 hardest puzzles, total 719ms, avg 65.36ms, max 201ms
```

DETAILED: [norvig_I5-4590.txt](./norvig_I5-4590.txt)


不得不说表现太差劲了，时间太长不说，还有解不出来的。。。

## norvig_cpp test result

直接翻译python代码，使用了std::optional, 需要 c++17

### CPU: I7-8700

OVERALL:

```
solved 50 of 50 easy50 puzzles, total 3609ms, avg 72.18ms, max 100ms
solved 95 of 95 top95 puzzles, total 26709ms, avg 281.15ms, max 1413ms
solved 11 of 11 hardest puzzles, total 1120ms, avg 101.82ms, max 152ms
```

DETAILED: [norvig_with_optional_I7-8700.txt](./norvig_with_optional_I7-8700.txt)

可以全解了，但是慢悠悠

## norvig_cpp_without_std_optional test result

在 `norvig_cpp` 的基础上移除了 `std::optional`，表现大为改善

### CPU: I7-8700

OVERALL: 

```
solved 50 of 50 easy50 puzzles, total 105ms, avg 2.10ms, max 3ms
solved 95 of 95 top95 puzzles, total 763ms, avg 8.03ms, max 40ms
solved 11 of 11 hardest puzzles, total 24ms, avg 2.18ms, max 4ms
```
DETAILED: [norvig_no_optional_I7-8700.txt](./norvig_no_optional_I7-8700.txt)

### I5-4590

OVERALL: 

```
solved 50 of 50 easy50 puzzles, total 90ms, avg 1.80ms, max 2ms
solved 95 of 95 top95 puzzles, total 600ms, avg 6.32ms, max 24ms
solved 11 of 11 hardest puzzles, total 42ms, avg 3.82ms, max 15ms
```

DETAILED: [norvig_no_optional_I5-4590.txt](./norvig_no_optional_I5-4590.txt)

很奈斯啊！


## norvig_cpp_optimize test result

### I7-8700

OVERALL:

```
solved 50 of 50 easy50 puzzles, total 0ms, avg 0.00ms, max 0ms
solved 95 of 95 top95 puzzles, total 1ms, avg 0.01ms, max 1ms
solved 11 of 11 hardest puzzles, total 0ms, avg 0.00ms, max 0ms
```

DETAILED: [norvig_cpp_optimize_I7-8700.txt](./norvig_cpp_optimize_I7-8700.txt)


### I5-4590

OVERALL: 

```
solved 50 of 50 easy50 puzzles, total 0ms, avg 0.00ms, max 0ms
solved 95 of 95 top95 puzzles, total 2ms, avg 0.02ms, max 1ms
solved 11 of 11 hardest puzzles, total 0ms, avg 0.00ms, max 0ms
```

DETAILED: [norvig_cpp_optimize_I5-4590.txt](./norvig_cpp_optimize_I5-4590.txt)

非常奈斯！


## norvig_c test result

继续优化为 `C` 版本


### I7-8700

OVERALL:

```
solved 50 of 50 easy50 puzzles, total 0ms, avg 0.00ms, max 0ms
solved 95 of 95 top95 puzzles, total 0ms, avg 0.00ms, max 0ms
solved 11 of 11 hardest puzzles, total 0ms, avg 0.00ms, max 0ms
```

DETAILED: [norvig_c_I7-8700.txt](./norvig_c_I7-8700.txt)


### I5-4590

OVERALL: 

```
```

DETAILED: [norvig_c_I5-4590.txt](./norvig_c_I5-4590.txt)
