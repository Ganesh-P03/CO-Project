# CO-Project

## Computer Organisation Project Semester 4 

### wxBits app

> Teamates : 
1) Ganesh 
2) Nishanth 

# commands supported
1) "add","slt","sltu","and","or","xor","sll","srl","sub","sra"
2) "addi","slti","sliu","andi","ori","xori","jalr"
3) "beq","bne","blt","bltu","bge","bgeu","j","ble"
4) "jal","li"
5) "lw"
6) "sw"

 


# Implementation
1) the code should end with **exit** 
2) Memory is 4byte addressable



# sample code

```
main :
li x4,4
li x5,5
li x2,3
li x1,2
add x1 , x1, x2
jal x9 , 3
addi x5 , x5, 10
bge x6,x2,CUSTOM

add x3 ,x4,x5
addi x3, x3, 1
addi x4 , x4, 10
li x6,100
jalr x10, x9, 0
CUSTOM:
exit
```

# bubble sort

```
# procedure:    bubbleSort
# Objective:    sort an array of integer elements in nondecreasing order
# Input:        an address of an array of integers
# Output:       an array sorted in nondecreasing order


.data
array:
.word 90 , 67 ,30 ,10 ,75 , 500  ,   100,  33,  68   , 19  , 2
.text
.globl main

main:
bubbleSort:
	li     x1,0x10010000
	li      x2, 0     # i = 0;
	li      x3, 0      # j = 0;
	li      x10, 10      # array length
loop:
	beq     x2, x10, exit       # exit if i == length of array -1
	li     x1,0x10010000
	li      x3, 0      # j = 0;
	forLoop:
		beq     x3,x10,exitForLoop   # exit loop if j==length of array -1
		lw      x20, 0(x1)         # a0 = array[j]
		lw      x21, 1(x1)         # a1 = array[j+1]
		ble     x20, x21, update        # if array[j]<=array[j+1] skip
		sw      x21, 0(x1)         # a[j+1] = a[j]
		sw      x20, 1(x1)         # a[j] = a[j+1]
	update:
		addi   x3, x3, 1         # j++
		addi    x1, x1, 1        # point to next element -->
		j       forLoop
	exitForLoop:
		addi   x2, x2, 1  # i++;
		j   loop
exit:
	exit
  
```
