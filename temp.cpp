#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int reg[32]={1,0};
int pc;
int mem[1000];
map<string,int> reg_map;


//types of instructions
string load_type[] = { "ld","sw" };
string ari_type[] = { "add","sub" };

//type:
//1-load_type
//2-ari_type

class instruction {
public:
    string opcode;
    int rd, rs1, rs2;
    int offset;
};

bool execute(int type,instruction inst);
bool write_back(int type,instruction inst,int mem_wb);
bool memory(int type,instruction inst,int ex_mem);

bool inst_decode(string Line) {

    instruction inst;

    int type = 0;

    //finding the type of instruction

    for (int i = 0; i < 2; i++) {
        auto itr = Line.find(ari_type[i]);
        if (itr != string::npos) {
            type = 2;
            break;
        }
    }
   

    if (type == 0) {

        for (int i = 0; i < 2; i++) {
            auto itr = Line.find(load_type[i]);
            if (itr != string::npos) {
                type = 1;
                break;
            }
        }
    }

    //forming the instruction
    int i = 0;
    int j = i + 1;

    if (type == 1) {

    }
    else if (type == 2) {
        int count = 0;

        for (; i < Line.length();) {
            for (; j < Line.length(); j++) {
                if (Line[j] == ' ' || j==Line.length()-1) {
                    if(j==Line.length()-1){j++;}
                    
                    if (count == 0) {
                        
                        inst.opcode = Line.substr(i, j - i);
                        count++;
                    }
                    else if (count == 1) {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        if (itr != reg_map.end()) {
                            inst.rd = itr->second;
                        }
                        else {
                            return false;
                        }
                        count++;
                    }
                    else if (count == 2) {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        if (itr != reg_map.end()) {
                            inst.rs1 = itr->second;
                        }
                        else {
                            return false;
                        }
                        count++;
                    }
                    else if (count == 3) {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        if (itr != reg_map.end()) {
                            inst.rs2 = itr->second;
                        }
                        else {
                            return false;
                        }
                        count++;
                    }
                    break;
                }
            }
            while (Line[j] == ' ') {
                j++;
            }
            i = j;
        }
    }
    else {

    }
    
    return execute(type,inst);

}

bool execute(int type,instruction inst) {
   int temp;
   if(type==1){

   }
   else if(type==2){
       if(inst.opcode=="add"){
           temp=reg[inst.rs1]+reg[inst.rs2];
           
       }
       else if(inst.opcode=="sub"){
           temp=reg[inst.rs1]-reg[inst.rs2];
       }
   }

   return memory(type,inst,temp);
}

bool memory(int type,instruction inst,int ex_mem){
    if(type==1){

    }else if(type==2){
       int mem_wb=ex_mem;
       return write_back(type,inst,mem_wb);
    }
    return false;
}

bool write_back(int type,instruction inst,int mem_wb){
   if(type==1){

   }
   else if(type==2){
       cout<<reg[inst.rd]<<" ";
     reg[inst.rd]=mem_wb;
     cout<<reg[inst.rd]<<'\n';
     return true;
   }
   return false;
}


bool perform(string Line) {
    return inst_decode(Line);
}

void parser(){
    std::ifstream file("input.txt");
    std::string str; 
    vector<pair<int,string>>Lines;
    int inst_number=0;

    while (std::getline(file, str))
    {   
        if(!str.empty()){
           Lines.push_back(pair<int,string>(inst_number,str));
        }
        inst_number++;
    }

    file.close();
    
    for(auto itr=Lines.begin();itr!=Lines.end();){
        string Line=itr->second;
        cout<<Line<<endl;
        if(perform(Line)){
            itr++;
        }else{
            cout<<"Error in Line number "<<itr->first;
            break;
        }
    }
}


void create_map(map<string,int> &reg_map){

    for(int i=0;i<32;i++){
        string str="x";
        str+=(char)(i+'0');
        reg_map.insert(pair<string,int>(str, i));
    }

}

void display( ){
    cout<<'\n';
    cout<<"registers.............."<<endl;

    for(int i=0;i<32;i++){
        cout<<"reg["<<i<<"]"<<'\t'<<reg[i]<<'\n';
    }

    cout<<endl;

    cout<<"memory..................";
    
}

int main(){
    
    create_map(reg_map);
    parser();

    display();

    
}
