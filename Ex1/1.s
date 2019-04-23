#pragma execution_character_set("utf-8")
#int main(){ 
#    int K, Y ;
#    int Z[50] ;
#    Y = 56;
#    for(K=0;K<50;K++)
#    Z[K] = Y - 16 * ( K / 4 + 210) ;
#}
.data#预先分配空间
    array: .space 200   #array of 200 bytes
    strn: .asciiz "\n"
    str1: .asciiz "Z["
    str2: .asciiz "]"
    str3: .asciiz "="
.text
main:
    la $t5, array       #取出数组首地�?
    li $a1, 0
    la $t4, array
    li $t6, 0
    li $s1, 56          #s1为Y
loop:    
    slti $s3, $a1, 50   #循环判断条件
    beq $s3, $0, loop1  #当K=50时说明数组赋值已完成
    add $t0, $0, $a1 
    srl $t1, $t0, 2     #$t0=K/4,右移2位即除以4
    addi $t1, $t1, 210  #   K/4+210
    sll $t2, $t1, 4     #   16 * ( K / 4 + 210)
    sub $t3, $s1, $t2   #   Y - 16 * ( K / 4 + 210)
    sw $t3, 0($t5)      #将寄存器中的值存入内�?
    addi $t5, $t5, 4    #array现在指向下一个整数地�?
    addi $a1, $a1, 1    #循环计数
    j loop
loop1:                  #loop1主要是用来输出数组形式的输出
    slti $s4, $t6, 50
     beq $s4, $0, exit
    lw $t7, 0($t4)      #取出上一个循环中存入的数
    li $v0, 4           
	la $a0, str1        
    syscall             #功能调用，输出Z[
    li $v0, 1
    add $a0,$0,$t6
    syscall             #数组索引
    li $v0, 4
	la $a0, str2
    syscall             #功能调用，输出]
    li $v0, 4
	la $a0, str3
    syscall             #功能调用，输�?=
    li $v0, 1
    add $a0, $0, $t7
    syscall             #输出数组的�??
    li $v0, 4
	la $a0, strn
    syscall             #功能调用，输出换行符
    addi $t4, $t4, 4
    addi $t6, $t6, 1
    j loop1
exit:
    li $v0, 10
    syscall

