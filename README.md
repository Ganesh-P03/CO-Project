# CO-Project

## Computer Organisation Project Semester 4

### wxBits app

> Teamates :

1. Ganesh
2. Nishanth

# commands supported

1. "add","slt","sltu","and","or","xor","sll","srl","sub","sra"
2. "addi","slti","sliu","andi","ori","xori","jalr"
3. "beq","bne","blt","bltu","bge","bgeu","j","ble"
4. "jal","li"
5. "lw"
6. "sw"

# Note

> We developed a desktop application using wxWidgets ( initial release -further changes are made in subsequent phases )

> While developing we had succesfully made :

1)UI (which can currently be runned on windows- for other OS , solution is given below )

2)Stimulator which can parse the RISC-V code

# Problems Faced 

- We are unable to use stimulator built upon standard library with GUI made with wxWidgets , so we are trying for another solution 
- We had problems with integration of this with Other OS ( especially Mac ) , very soon we will solve this issue , until then we can assure it works on all window version's  but on other OS  is doubt because we lack other OS to check it out 

# Getting started

Download the zip file (or) fork this repository and use `git clone` to clone it on your local desktop

> UI :

1)Go to release folder and click on wxBits.exe file ( remember only for window's )(Installer will be made for window's user on 2nd phase )
2)If there is a prompt from Windows security click on runanyway
3)Here you  go-wxBitsapp running!!

> Debugging :

1)If in anycase , .exe files is not supported in your OS, then click on (.sln) file and build solution in release mode (if wxWidgets installed in your system )

> Stimulator :

1)Open Stimulator Folder

2)Open input.txt file copy and paste any of the samplecode or bubblesort or type any Risc-V code

3)Open the stimulator.cpp file in vsCode or any editor and run it

4)You can see a new file in the same stimulator folder named output.txt will be created

5) **output**.txt files contains the result of execution

# Implementation

1) The code should end with **exit**

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

## Screenshots

<p>
    <img src="Images/Code Running-autoComp.bmp" height="600" width=auto>
    <img src="Images/File-ins.bmp" height="600" width=auto>
	<img src="Images/Front-Page.bmp" height="600" width=auto>
	<img src="Images/Log-Console.bmp" height="600" width=auto>
    <img src="Images/Menu-Items.bmp" height="600" width=auto>
</p>
