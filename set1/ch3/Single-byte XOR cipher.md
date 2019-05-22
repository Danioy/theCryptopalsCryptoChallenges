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

![img](frequency.jpg)

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

实际计算做出来又有新发现。对于一级高频符组合测试之后，答案key 88 不止出现一次！！！！！

这个特点很容易理解，但不试一试是永远想不到这点。好玩， 可以修改一下流程了。



遇到好多 memory 方面的困难。 指针和数组传来传去，总是出问题。先解决到这个样子吧。 在后面的题目中逐步完善我们的函数。

```
$ echo 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736 | ./single_xor.exe
34: 7316?x+x413=x9x(7-6<x7>x:9;7680: Kggcafo(EK/{(dacm(i(xg}fl(gn(jikgf
82: Ieeacdm*GI-y*fcao*k*zedn*el*hkied
86: Maaeg`i.CM)}.bgek.o.~a{`j.ah.loma`
87: L``dfah/BL(|/cfdj/n/`zak/`i/mnl`a
88: Cooking MC's like a pound of bacon
89: Bnnjhof!LB&r!mhjd!`!qntoe!ng!c`bno
92: Gkkomjc$IG#w$hmoa$e$tkqj`$kb$fegkj
94: Eiimoha&KE!u&jomc&g&vishb&i`&dgeih
95: Dhhlni`'JD t'knlb'f'whric'ha'efdhi
```

暂时我是把重复出现两次及以上的key 都穷举了一下。应该有更简洁的办法的。 可惜俺的 coding 水平还需要磨练啊~~~~~~~~~~~ 