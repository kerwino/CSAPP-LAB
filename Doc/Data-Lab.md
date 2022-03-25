## 实验一 Data Lab 讲解

该实验考察了对于 CSAPP 书中第二章的相关内容，例如整数的表示、整数的运算、浮点数等具体内容的理解和掌握。

该试验的主要内容是依据对于计算机中整数及浮点数的表示和运算规则，在有限的条件下实现一些特定的函数功能。

## 结果演示

该实验提供了三个工具来对实验任务的完成情况进行检查

1.   **dlc：**一个“数据实验编译器”，用 bits.c 检查每个函数是否符合编码准则，检查学生是否使用少于最大数量的运算符，是否只使用直线代码，是否只使用合法运算符。其源代码和一个 Linux 二进制文件都包含在实验中。
2.   **btest：**一个测试工具，用于检查 bits.c 中函数的正确性。这个工具已经得到了显著的改进，现在可以检查整数和浮点表示的大范围（wide swaths）边缘用例（edge cases），比如 0、最小有符号数（Tmin）、非规格化的数和规格化的数的边界（denorm-norm boundary） 和无限大（inf）。
3.   **driver.pl：**一个自动评分驱动程序，它使用 dlc 和 btest 来检查 bits.c 中每个测试函数的正确性，以及是否符合编码准则。

基于这三个工具我使用脚本对实验进行验证，脚本内容如下

```bash
#!/bin/bash
make clean
make
echo "----------dlc----------"
./dlc -e bits.c
echo -e "-----------------------\n"
echo "---------btest---------"
./btest
echo -e "-----------------------\n"
echo "-------check.pl--------"
./bddcheck/check.pl 
echo -e "-----------------------"
```

得到的结果如下

```bash
----------dlc----------
dlc:bits.c:155:bitXor: 7 operators
dlc:bits.c:167:tmin: 1 operators
dlc:bits.c:183:isTmax: 9 operators
dlc:bits.c:200:allOddBits: 7 operators
dlc:bits.c:218:negate: 2 operators
dlc:bits.c:245:isAsciiDigit: 9 operators
dlc:bits.c:260:conditional: 8 operators
dlc:bits.c:281:isLessOrEqual: 20 operators
dlc:bits.c:301:logicalNeg: 5 operators
dlc:bits.c:341:howManyBits: 36 operators
dlc:bits.c:374:float_twice: 14 operators
dlc:bits.c:424:float_i2f: 22 operators
dlc:bits.c:463:float_f2i: 22 operators
-----------------------

---------btest---------
Score	Rating	Errors	Function
 1	1	0	bitXor
 1	1	0	tmin
 2	2	0	isTmax
 2	2	0	allOddBits
 2	2	0	negate
 3	3	0	isAsciiDigit
 3	3	0	conditional
 3	3	0	isLessOrEqual
 4	4	0	logicalNeg
 4	4	0	howManyBits
 4	4	0	float_twice
 4	4	0	float_i2f
 4	4	0	float_f2i
Total points: 37/37
-----------------------

-------check.pl--------
Comparing bits.c:bitXor to tests.c:test_bitXor .. OK
Check bitXor score: 1/1
Comparing bits.c:tmin to tests.c:test_tmin .. OK
Check tmin score: 1/1
Comparing bits.c:isTmax to tests.c:test_isTmax .. OK
Check isTmax score: 2/2
Comparing bits.c:allOddBits to tests.c:test_allOddBits .. OK
Check allOddBits score: 2/2
Comparing bits.c:negate to tests.c:test_negate .. OK
Check negate score: 2/2
Comparing bits.c:isAsciiDigit to tests.c:test_isAsciiDigit .. OK
Check isAsciiDigit score: 3/3
Comparing bits.c:conditional to tests.c:test_conditional .. OK
Check conditional score: 3/3
Comparing bits.c:isLessOrEqual to tests.c:test_isLessOrEqual .. OK
Check isLessOrEqual score: 3/3
Comparing bits.c:logicalNeg to tests.c:test_logicalNeg .. OK
Check logicalNeg score: 4/4
Comparing bits.c:howManyBits to tests.c:test_howManyBits .. OK
Check howManyBits score: 4/4
Comparing bits.c:float_twice to tests.c:test_float_twice .. OK
Check float_twice score: 4/4
Comparing bits.c:float_i2f to tests.c:test_float_i2f .. OK
Check float_i2f score: 4/4
Comparing bits.c:float_f2i to tests.c:test_float_f2i .. OK
Check float_f2i score: 4/4
Overall correctness score: 37/37
All tests passed
-----------------------
```

可以看到我已经满足了该实验的所有的要求，成功完成所有实验内容。

## 代码讲解

### 第一个部分

1.   要求函数返回两个参数的异或操作结果：

     根据异或的真值表，发现异或等价于**二者按位或和二者按位与的非相与**，此处根据德摩根定律使用与非操作取代或操作。

2.   要求函数返回补码表示的最小的整数：

     根据补码的定义，只需要将第一位负权置一，其余位置零即可得到最小的整数。

### 第二个部分

3.   要求判断参数是否为补码表示的最大的整数，是则返回1，否则返回0：

     观察目标值`01...11`，可以知道它与`11...11`加1之后取反与原数相同。这里假设参数是目标值或-1，那么原数+1得到的是最小的整数，两者按位异或得到的是0，否则原数不符合条件。再添加条件排除-1即可。

4.   要求判断参数的奇数位是否全为1，是则返回1，否则返回0：

     容易想到使用数`0xAAAAAAAA`作为遮罩与参数按位与，得到参数的奇数位，将结果与`0xAAAAAAAA`进行异或，如果参数某个奇数位不为1，则得到的结果不为0，否则为0，否定该结果即可满足函数要求。

5.   要求返回参数的相反数：

     根据C语言中整数的解释方式，只需将其按位取反加一即可。下面讨论原数的符号情况进行验证（以下tmax表示最大的整数）

     -   负数：

         假设数值位表示的数大小为`xxx`，原数数值则为`- (tmax + 1) + xxx`

         按位取反加一后得到的数值为 `tmax - xxx + 1` 

     -   正数：

         假设原数数值为`xxx` 

         按位取反加一后得到的数值为`-(tmax + 1) + (tmax - xxx) + 1` 

### 第三部分

6.   要求判断参数是否在`[0x30,0x39]`中，如果在返回1，否则返回0：

     观察范围内的数的二进制表示`0x110000,0x110001...0x110111,0x111000,0x111001` ，可以看到，这些数的特征

     -   除了低位六位，其余均为零
     -   低位第六位和第五位均为1
     -   低四位数值小于10，因此加6之后均小于16，可以通过移位对高位进行检查

7.   要求判断第一个参数的值的情况，如果是非零则返回第二个参数，否则返回第三个参数：

     对参数使用两次否定运算符`!!`可以判断参数是否为零，如果参数为零则结果为1，否则结果为0。通过移位操作将单个位的结果转化成32位，作为掩码，选择第二个参数或者第一个参数进行返回。

8.   要求判断前两个参数的大小关系，如果是小于等于关系则返回1，否则返回0：

     当两个参数为异号时直接进行减法可能会产生溢出，因此分情况进行处理

     -   x负，y正：满足条件
     -   x正，y负：不满足条件
     -   同号相减判断符号

### 第四部分

9.   要求函数实现逻辑运算符非的功能，非零参数返回0，0参数返回1:

     如果一个数非零，那么它和它的相反数的和按位或得到的符号为1，否则为0。利用这一特点即可完成本题。

10.   要求实现函数返回能够表示参数的最小二进制位数：

      -   如果参数是0，则返回1；

      -   如果参数是正数，则只需要找到最高位的1的位次，再加一位符号位；

      -   如果参数是负数，则去除前n个连续的1之后，找到最高位的0的位次，再加一位符号位。这等价于将原数取反找到最高位1的位次，再加一位符号位。这与正数的处理方式相同。

      综上当原数为非负数时，取原数，找到最高位的1的位次。当原数为负数时，原数按位取反，找到最高位的1的位次。使用符号制作遮罩。

      使用二分法判断最高位的1的位次：检查高位或低位哪一半有1，高位有，则舍弃低位，将位次+16；否则高位全为零，不用处理，将位次+0。直到只有有一位的时候，最后加上符号位返回即可。

### 第五部分

浮点数分为三类：

-   规格化：常规值

    阶码部分在1～254之间

-   非规格化：表示非常接近0的值

    阶码部分为0

-   特殊类：表示无穷大和NaN

    阶码全为1且尾数全为0，根据符号表示正负无穷大。

    阶码全为1且尾数不全为0，表示NaN

    

11.   要求实现函数返回浮点参数的二倍：

      -   如果是非规格化类：尾数*2，保留符号位返回。

      -   如果是特殊类：直接返回

      -   如果是规格化类：阶码+1，判断是否变为特殊类，如果是则保留符号返回无穷大，否则保留其他位直接返回。

12.   要求实现函数返回整型参数的浮点规则解释时的数值：

      要转化成浮点数需要获取其符号位、阶码、尾码依次获取他们的位模式：

      -   符号位：取高位第一位即可。

      -   阶码：取得参数的绝对值，参数的数值位一共有 31 ，因此阶码最大为 e = 127 + 31。顺次检查参数的数值位，如果为0则e减去1，并将参数左移一位，直到检查到1为止，即可获得阶码的数值。（如果参数为0，顺次检查的操作会进入死循环，因此事先排除。）

      -   尾数：对参数继续做处理，对上一步的处理结果，去掉最高位的1，再右移八位，并按照向偶舍入原则进行舍入处理，即可得到尾数。

      将上述步骤的结果拼接即得解。

13.   要求实现函数返回浮点参数的整型规则解释时的数值：

      需要将浮点数的位模式转化成整型数，需要根据阶码和尾数对数的大小情况进行分析：

      将阶码减去偏移量得到指数E，将尾数乘以 `2^23` 存入 `frac_23` 。

      -   当E小于0时，无论尾数如何，最终数值均为小数，直接返回0。

      -   当E在 `[0,30]` 这一区间时，不会发生溢出，仅判断 E 和 23 的关系，计算移位的方向和大小即可。

      -   当E大于等于31时需要考虑，溢出或者等于溢出值。






