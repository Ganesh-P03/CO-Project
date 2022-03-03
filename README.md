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
LI x4,4
LI x5,5
LI x2,3
LI x1,2
SW x1,0(x2)
ADD x1 , x1, x2
JAL x9 , 3
ADDI x5 , x5, 10
BGE x6,x2,CUSTOM

ADD x3 ,x4,x5
ADDI x3, x3, 1
ADDI x4 , x4, 10
LI x6,100
JALR x10, x9, 0
CUSTOM:
exit
```
