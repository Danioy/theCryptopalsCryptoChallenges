[the cryptopals crypto challenges](http://cryptopals.com/)           

- [Challenges](http://cryptopals.com/)             
- [Set 1](http://cryptopals.com/sets/1)             
- [Challenge 1](http://cryptopals.com/sets/1/challenges/1)             



### Convert hex to base64

   The string:

```
49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
```

   Should produce:

```
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
```

   So go ahead and make that happen. You'll need to use this code for the rest of the exercises.

### Cryptopals Rule

​       Always operate on raw bytes, never on encoded strings. Only use hex       and base64 for pretty-printing.     

这里有两个稍微难点的东西： 

#### hex-string

我们直接用 golang 里面对这个 的定义吧。

解这道题，我们主要实现怎么对这个字符串进行导入。

第一，

 底层实现我们用 fd 来实现。 如果需要导入的是 txt 文件，那么直接 fopen 一个 fd. 如果是一串字符串， 那么就直接指定 fd = stdin. 在 console 中 用 pipe 的形式导进去。

第二，

就是需要如何设定 buffer。用 stream 的概念，假设文件是无限大的，我们定义 4096 的 buffer 区，每次也最多只读入 4096 个字节。 这个就是我们的 readin_hexstring_from_file() 函数了。在 common.h 中定义。

另一个就不管文件多大，直接开buffer 把文件全部读进去再说。这个晚点会完善。



#### base64 编码和解码。 

我们可以直接调用 GNU CoreUtils 的算法就好。 这个算法已经运行了几十年，在各种环境下每年都运行几十亿次。小子不可能做到更完备的代码了。 