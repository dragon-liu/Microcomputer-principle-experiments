# Microcomputer-principle-experiments

* 主要记录微机原理课的相关实验<br>

* 每个Ex下由相应任务要求，相应代码以及我的实验报告<br>

* 目录<br>
  * Ex1<br>
  实验任务:用汇编程序实现以下伪代码：要求采用移位指令实现乘除法运算,最后结果Z[k]（k=0~49）要在MARS中输出，查看内存映像。 <br>
  ```
  int main(){ 
    int K, Y ;
    int Z[50] ;
    Y = 56;
    for(K=0;K<50;K++)
    Z[K] = Y - 16 * ( K / 4 + 210) ;
  }
  ```
  * Ex2<br>
  实验任务：利用HDL语言，基于Xilinx FPGA nexys4实验 平台，设计一个能够执行以下MIPS指令集的 单周期类MIPS处理器，要求完成所有支持指 令的功能仿真，验证指令执行的正确性，要求 编写汇编程序将本人学号的ASCII码存入 RAM的连续内存区域: <br>
    * 支持基本的内存操作如lw，sw指令 
    * 支持基本的算术逻辑运算如add，sub，and， or，slt，andi指令 
    * 支持基本的程序控制如beq，j指令
  
