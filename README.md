# CO-Project

## Computer Organisation Project Semester 4 

> Teamates : 
1) Ganesh 
2) Nishanth 

# commands supported
1) "ADD","SLT","SLTU","AND","OR","XOR","SLL","SRL","SUB","SRA"
2) "ADDI","SLTI","SLIU","ANDI","ORI","XORI","JALR" 
3) "BEQ","BNE","BLT","BLTU","BGE","BGEU"
4) "JAL","LI"
5) "LW"
6) "SW"

# sample code

```
main :
li x4,4
li x5,5
li x2,3
li x1,2
sw x1,0(x2)
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
