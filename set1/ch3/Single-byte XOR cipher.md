### Single-byte XOR cipher

   The hex encoded string:

```
1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
```

   ... has been XOR'd against a single character. Find the key, decrypt   the message.

   You can do this by hand. But don't: write code to do it for you.

   How? Devise some method for "scoring" a   piece of English plaintext. Character frequency is a good metric.   Evaluate each output and choose the one with the best score.

### Achievement Unlocked

​       You now have our permission to make "ETAOIN SHRDLU" jokes on Twitter.     

几样数据：

cornell.edu 的 letter frequency 数据和分布:

| Letter | Count |      | Letter | Frequency（%） |
| ------ | ----- | ---- | ------ | -------------- |
| E      | 21912 |      | E      | 12.02          |
| T      | 16587 |      | T      | 9.10           |
| A      | 14810 |      | A      | 8.12           |
| O      | 14003 |      | O      | 7.68           |
| I      | 13318 |      | I      | 7.31           |
| N      | 12666 |      | N      | 6.95           |
| S      | 11450 |      | S      | 6.28           |
| R      | 10977 |      | R      | 6.02           |
| H      | 10795 |      | H      | 5.92           |
| D      | 7874  |      | D      | 4.32           |
| L      | 7253  |      | L      | 3.98           |
| U      | 5246  |      | U      | 2.88           |
| C      | 4943  |      | C      | 2.71           |
| M      | 4761  |      | M      | 2.61           |
| F      | 4200  |      | F      | 2.30           |
| Y      | 3853  |      | Y      | 2.11           |
| W      | 3819  |      | W      | 2.09           |
| G      | 3693  |      | G      | 2.03           |
| P      | 3316  |      | P      | 1.82           |
| B      | 2715  |      | B      | 1.49           |
| V      | 2019  |      | V      | 1.11           |
| K      | 1257  |      | K      | 0.69           |
| X      | 315   |      | X      | 0.17           |
| Q      | 205   |      | Q      | 0.11           |
| J      | 188   |      | J      | 0.10           |
| Z      | 128   |      | Z      | 0.07           |

![img](E:\beyond\cryptochallenge\ch3\frequency.jpg)

经过第一题之后，应该很容易得到 题目中的 数字序列和 重复频率。

```
27 55 55 51 49 54 63 120 21 27 127 43 120 52 49 51 61 120 57 120 40 55 45 54 60 120 55 62 120 58 57 59 55 54
```
频率对:
```
21: 2.9%
27: 5.9%
40: 2.9%
43: 2.9%
45: 2.9%
49: 5.9%
51: 5.9%
52: 2.9%
54: 8.8%
55: 15%
57: 5.9%
58: 2.9%
59: 2.9%
60: 2.9%
61: 2.9%
62: 2.9%
63: 2.9%
120: 18%
127: 2.9%
```

我们仔细观察两个表格，会发现 cornell.edu 的分布明显有几个阶梯： 

1. ETAOI 明显是 6% 以上的。
2. NSHRDL 明显显是3% 以上的。
3. 稍微模糊放大一下边界，再利用一下题目中的提示，高 freq 的 一级我们放 ETAOIN 六个， 阀值放到5%;
4. 二级 freq 的也放 SHRDLU 六个， 区间大概是 [2%, 5%].
5. 最少的是 xqjz, 基本不会超过 千分之五。

那么再观察我们的密文表，超过 5% 的有 27, 49, 51, 54, 55, 57, 120 七个。

也就是说第一个区我们可以构成 6 * 7 = 42 个尝试的 key。 实际上，即使是暴力破解法，也只需要尝试127-32 个再加上 空格，\t, \r, \n 大约100个key就可以了。 暴力破解法省掉了大量的浮点和排序运算，说不定反而更快。因为现在单核计算速度已经达到普遍 3G/秒, 10000 次异或运算 可能就是纳秒级。而浮点排序需要处理太多次存储读写，反而慢。  

与其以运算速度为目标，不如在结果判断上缩短人工时间更靠谱。



不管如何，先把算法构建起来。