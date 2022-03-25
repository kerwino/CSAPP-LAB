## 实验四 Performancce Lab 讲解

该实验主要考察了对于CSAPP书中第五章以及第六章的相关内容，例如基本的程序优化方法和基本原理、基于 cache 高速缓存对程序进行优化。

该实验的主要目的是依据对程序的基本优化方法和存储器层次结构的理解对程序进行优化，从而提升程序性能。

## 结果演示

该实验使用根据机器特性编译出的评分程序 `driver` 对程序的优化结果进行判断。

脚本内容如下：

```bash
#!/bin/bash
make clean
make
./driver
```

脚本运行结果如下： 

```bash
Teamname: YQ
Member 1: Yanqing Du
Email 1: yanqing.du@outlook.com

Rotate: Version = naive_rotate: Naive baseline implementation:
Dim             64      128     256     512     1024    Mean
Your CPEs       1.8     2.1     3.1     4.1     7.5
Baseline CPEs   14.7    40.1    46.4    65.9    94.5
Speedup         8.0     19.1    14.7    16.0    12.6    13.5

Rotate: Version = rotate: Current working version:
Dim             64      128     256     512     1024    Mean
Your CPEs       1.7     1.7     1.8     2.0     4.4
Baseline CPEs   14.7    40.1    46.4    65.9    94.5
Speedup         8.5     23.0    25.2    33.0    21.7    20.4

Smooth: Version = smooth: Current working version:
Dim             32      64      128     256     512     Mean
Your CPEs       13.4    13.7    13.8    13.8    13.8
Baseline CPEs   695.0   698.0   702.0   717.0   722.0
Speedup         51.7    51.1    50.9    51.9    52.4    51.6

Smooth: Version = naive_smooth: Naive baseline implementation:
Dim             32      64      128     256     512     Mean
Your CPEs       50.0    49.9    10.4    50.0    50.2
Baseline CPEs   695.0   698.0   702.0   717.0   722.0
Speedup         13.9    14.0    67.6    14.3    14.4    19.3

Summary of Your Best Scores:
  Rotate: 20.4 (rotate: Current working version)
  Smooth: 51.6 (smooth: Current working version)
```

可以看到相比原始函数，两个函数的性能分别获得了50%和167%的性能提升。

## 过程讲解

### Roate

#### 原方法

1.   分别根据递增的i和j，计算出列元素的下标和与之对应的行元素的下标，进行一一赋值。
2.   其中src数组中元素是顺序读取的，dst数组中元素是列写入的。

#### 改进方法

1.   减少地址的计算次数，通过对起始地址进行累加获得新的地址。
2.   将dst数组的索引修改成顺序的，从而减少写不命中的次数。
3.   对元素进行分块处理，因为Cache Line的大小为64B，一个像素的大小是6B，因此将每一块分为8个元素可以减少写不命中的问题。

### Smooth

#### 原方法

1.   定义新的数据结构，用于在进行卷积时存储累加的和以及累加的像素数量。
2.   定义两个求极值简单函数，用于简化边界判断时的代码。
3.   定义函数对新的数据结构，将其中元素进行初始化为0的操作。
4.   定义函数用于累加像素到一个新的数据结构。
5.   定义函数用于得到给定像素位置的卷积得到的单个结果。
6.   在总的函数中，对每一个像素都调用，卷积得到单个像素值的函数，从而完成卷积操作。

#### 改进方法

1.   在原方法中，因为卷积核的大小仅为3x3，因此可以避免使用新的数据结构直接在修改已定义的数据结构 `pixel` 中，从而减少了数据的转存。

2.   由于待处理的数据内容为一个大小为NxN的 `pixel` 数组，抽象为一个NxN的像素阵列。由于四个边界的像素、四个角落的像素和中间的像素点都需要不同处理方式。在原方法中，由于需要对边界的判断这一原因，在每一个像素的卷积运算过程中，都需要数次调用函数 `max` 和 `min` 对边界元素加一区分，这样使得循环的代价很大。考虑到像素点的分类数量是固定的，一共可以分为八种情况进行处理，分别为四个顶点元素、四个除去顶点的边接元素以及中间剩余的元素。

     如此一来，大大减少了循环的代价。



