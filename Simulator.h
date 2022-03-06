#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include<exception>
using namespace std;

class regi {
public:
    int var;
    bool isAddr;

    regi() {
        var = 0;
        isAddr = false;
    }
};

class regi reg[32];
int pc;
int mem[1000];
map<string, int> reg_map;
vector<pair<string, int>>tags;
vector<string>errors;
int k = 0;

//types of instructions

string R_type[] = { "add","slt","sltu","and","or","xor","sll","srl","sub","sra" };
string I_type[] = { "addi","slti","sliu","andi","ori","xori","jalr" };
string B_type[] = { "beq","bne","blt","bltu","bge","bgeu","j","ble" };
string J_type[] = { "jal","li" };
string Load_type[] = { "lw" };
string Store_type[] = { "sw" };



//instruction
class instruction {
public:
    string type;
    string opcode;
    string label;
    int rd, rs1, rs2;
    int offset;
    int imd;

    instruction() {
        label = " ";
    }
};

std::string trim(const std::string& s);
void dataseg_handler(string dataLine);
void parser(string input);
void create_map(map<string, int>& reg_map);
void stimulator(string input);
//functions
bool inst_fetch(vector<pair<int, string>>Lines);
bool inst_decode(string Line);
bool execute(instruction inst);
bool write_back(instruction inst, int mem_wb);
bool memory(instruction inst, int ex_mem);