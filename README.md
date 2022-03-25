# README



下面介绍各个实验文件目录布局、验证方式和相关文档。

## Documents

```txt
Doc/
├── Bomb-Lab.md
├── Data-Lab.md
└── Performance-Lab.md
```

-   实验一文档 `Data-Lab.md` 
-   实验二文档 `Bomb-Lab.md` 
-   实验四文档 `Performance-Lab.md` 

## Data Lab

```txt
Lab1-data/
└── datalab-handout
    ├── bddcheck
    │   ├── all-functions.txt
    │   ├── cbit
    │   │   ├── cbit
    │   │   └── README
    │   ├── check.pl
    │   ├── checkprogs.pl
    │   ├── README
    │   └── satparse.pl
    ├── bits.c
    ├── bits.h
    ├── btest
    ├── btest.c
    ├── btest.h
    ├── decl.c
    ├── dlc
    ├── Driverhdrs.pm
    ├── Driverlib.pm
    ├── driver.pl
    ├── fshow
    ├── fshow.c
    ├── ishow
    ├── ishow.c
    ├── Makefile
    ├── README
    ├── run.sh
    └── tests.c
```

题解文件为 `Lab1-data/bits.c` 

验证脚本为 `Lab1-data/run.sh` 

## Bomb Lab

```txt
Lab2-bomb/
└── bomb
    ├── bomb
    ├── bomb.c
    ├── func4
    ├── func4.c
    ├── README
    ├── run.sh
    ├── solution.txt
    └── tsol.txt
```

题解文件为 `Lab2-bomb/bomb/solution.txt` 

验证脚本为 `Lab2-bomb/bomb/run.sh`

## Performance Lab

```txt
Lab4-performance/
├── handin
│   └── YQ-1-kernels.c
└── perflab-handout
    ├── clock.c
    ├── clock.h
    ├── clock.o
    ├── config.h
    ├── defs.h
    ├── driver
    ├── driver.c
    ├── driver.o
    ├── fcyc.c
    ├── fcyc.h
    ├── fcyc.o
    ├── kernels.c
    ├── kernels.o
    ├── Makefile
    ├── README
    └── run.sh
```

题解文件为 `Lab4-performance/perflab-handout/kernels.c` 

验证脚本 `Lab4-performance/perflab-handout/run.sh` 
