这个程序是假的。

## 这个程序只是对应知乎上的问题

补充一下知乎的问题内容。

【如果把一个已经压缩过的文件和一个很大的文件的内容异或再压缩，还能获得高效率的压缩吗？】俞怡炜：… https://www.zhihu.com/question/60343952/answer/176527918?utm_source=com.rstudio.textie&utm_medium=social （分享自知乎网）

## 举个简单的例子

详细的栗子在wiki那里。

假设有一个文件a，它的内容是：

`01100111 10100011`

然后生成了一个伪随机文件b，内容：

`10110011 00110101`

二者进行异或，得到新文件c：

`11010100 10010110`

很明显，文件a和文件c的内容都毫无规律可言，压缩之后的文件c和压缩之后的文件a大小差别不大。

于是软件调整配置，生成了伪随机文件d：

`10011001 01001100`

和文件a异或，得到文件e：

`11111110 11101111`

这么多个1！压缩文件e当然可以获得更高的压缩效率！

于是软件压缩文件e并记录下配置信息，等到需要解压的时候，解压文件，再根据配置信息生成伪随机文件d，再和文件e进行异或，就能还原文件a了。

## 概率问题

这的确是一个概率问题。当然，真实的情况不可能像上面那样只重复第二次就可以获得一个压缩率很高的文件。

压缩一个大文件通常都需要循环生成很多个不同的伪随机文件（在无理数的某一个位置截取出来），然后再和文件异或（通常异或次数也可以是不同的）。再进行压缩，统计出每个压缩文件的大小。一直循环尝试不同的配置那么多次，总会有一次是能生成一个刚刚合适的伪随机文件，然后刚刚好和原文件压缩生成一个压缩率很高的文件。

程序在压缩文件后会把配置文件保存下来，记录文件通常包括2个数据：

* 无理数截取的位置

* 异或次数

如果`压缩前文件大小-压缩后文件大小≥压缩后的配置文件大小`的话，就是一次有效的压缩。

如果无限循环压缩，就可以把很大的文件压缩成很小的文件了。

不过，讲道理，怎么可能可以这样压缩？你们快来证明它可不可行吧。
