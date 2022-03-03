#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

std::string trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

int reg[32] = { 0 };
int pc;
int mem[1000];
map<string, int> reg_map;
vector<pair<string,int>>tags;

//types of instructions

string R_type[] = { "ADD","SLT","SLTU","AND","OR","XOR","SLL","SRL","SUB","SRA" };
string I_type[] = { "ADDI","SLTI","SLIU","ANDI","ORI","XORI","JALR" };
string B_type[] = { "BEQ","BNE","BLT","BLTU","BGE","BGEU" };
string J_type[] = { "JAL","LI" };
string Load_type[] = { "LW" };
string Store_type[] = { "SW" };



//instruction
class instruction {
public:
    string type;
    string opcode;
    string label;
    int rd, rs1, rs2;
    int offset;
    int imd;
};

//functions
bool inst_fetch(vector<pair<int, string>>Lines);
bool inst_decode(string Line);
bool execute(instruction inst);
bool write_back(instruction inst, int mem_wb);
bool memory(instruction inst, int ex_mem);


//fetches the instructons based on pc
bool inst_fetch(vector<pair<int, string>>Lines) {
    if (pc == -1) { return true; }
    string Line = Lines[pc].second;
    pc++;

    return inst_decode(Line);
}

//decodes fetched instruction
bool inst_decode(string Line) {

    if (Line == "exit") { pc = -1; return true; }

    instruction inst;
    bool is_set_type = false;
    string type;

    //finding the type of instruction
     int n = sizeof(I_type) / sizeof(I_type[0]);
        for (int i = 0; i < n; i++) {
            auto itr = Line.find(I_type[i]);
            if (itr != string::npos) {
                type = "I_type";
                is_set_type = true;
                break;
            }
        }


    if (!is_set_type) {
         n = sizeof(R_type) / sizeof(R_type[0]);

        for (int i = 0; i < n; i++) {
            auto itr = Line.find(R_type[i]);
            if (itr != string::npos) {
                type = "R_type";
                is_set_type = true;
                break;
            }
        }
    }

    if (!is_set_type) {
        n = sizeof(B_type) / sizeof(B_type[0]);
        for (int i = 0; i < n; i++) {
            auto itr = Line.find(B_type[i]);
            if (itr != string::npos) {
                type = "B_type";
             
                is_set_type = true;
                break;
            }
        }
    }

    if (!is_set_type) {
        n = sizeof(J_type) / sizeof(J_type[0]);
        for (int i = 0; i < n; i++) {
            auto itr = Line.find(J_type[i]);
            if (itr != string::npos) {
                type = "J_type";
                is_set_type = true;
                break;
            }
        }
    }

    if (!is_set_type) {
        n = sizeof(Load_type) / sizeof(Load_type[0]);
        for (int i = 0; i < n; i++) {
            auto itr = Line.find(Load_type[i]);
            if (itr != string::npos) {
                type = "Load_type";
                is_set_type = true;
                break;
            }
        }
    }

    if (!is_set_type) {
        n = sizeof(Store_type) / sizeof(Store_type[0]);
        for (int i = 0; i < n; i++) {
            auto itr = Line.find(Store_type[i]);
            if (itr != string::npos) {
                type = "Store_type";
                is_set_type = true;
                break;
            }
        }
    }

    cout<<type<<endl;


    //forming the instruction
    int i = 0;
    int j = i + 1;


    int count = 0;

    for (; i < Line.length();) {
        for (; j < Line.length(); j++) {
            if (Line[j] == ' ' || Line[j] == ',' || j == Line.length() - 1) {
                cout<<count<<" ";
                if (j == Line.length() - 1) { j++; }

                if (count == 0) {
                    inst.opcode = Line.substr(i, j - i);
                    
                    count++;
                }
                else if (count == 1) {

                    if (type == "R_type" || type == "I_type" || type == "J_type" || type == "Load_type") {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        cout<<"\n"<<Line.substr(i, j - i)<<"hello";
                        if (itr != reg_map.end()) {
                            inst.rd = itr->second;
                            
                        }
                        else {
                            return false;
                        }
                    }
                    else if(type=="B_type" || type=="Store_type"){
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        if (itr != reg_map.end()) {
                            inst.rs1 = itr->second;
                        }
                        else {
                            return false;
                        }
                    }

                    count++;
                }
                else if (count == 2) {

                    if (type == "R_type" || type == "I_type" ) {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        if (itr != reg_map.end()) {
                            inst.rs1 = itr->second;
                            
                        }
                        else {
                            return false;
                        }
                    }
                    else if (type == "B_type") {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        if (itr != reg_map.end()) {
                            inst.rs2 = itr->second;
                            
                        }
                        else {
                            return false;
                        }
                    }
                    else if (type == "J_type") {
                        
                        string temp=Line.substr(i, j - i);
                        try
                        {
                            inst.imd = stoi(temp);
                        }
                        catch (const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                             return false;
                        }
                    }
                    else if(type== "Load_type"){
                        string sub_string =Line.substr(i, j - i);
                        
                        auto itr= sub_string.find('(');
                        
                        if (itr != string::npos) {
                            
                            string temp1=sub_string.substr(0,itr);
                            
                            try
                            {
                                inst.offset = stoi(temp1);
                            }
                            catch (const std::exception& e)
                            {
                                std::cerr << e.what() << '\n';
                                return false;
                            }

                            
                            itr++;
                            string temp_string=sub_string.substr(itr,sub_string.length()-1-itr);
                            auto itr1 = reg_map.find(temp_string);
                            if (itr1 != reg_map.end()) {
                                inst.rs1 = itr1->second;
                            }
                            else {
                                return false;
                            }
                            
                                
                        }
                        else
                        {   
                            return false;
                        }

                    }
                    else if(type == "Store_type"){
                        string sub_string =Line.substr(i, j - i);
                        cout<<"\n"<<sub_string<<"\n";
                        auto itr= sub_string.find('(');
                        
                        if (itr != string::npos) {
                            
                            string temp1=sub_string.substr(0,itr);
                            cout<<"\n"<<temp1<<"\n";
                            try
                            {
                                inst.offset = stoi(temp1);
                            }
                            catch (const std::exception& e)
                            {
                                std::cerr << e.what() << '\n';
                                return false;
                            }

                            
                            itr++;
                            string temp_string=sub_string.substr(itr,sub_string.length()-1-itr);
                            auto itr1 = reg_map.find(temp_string);
                            if (itr1 != reg_map.end()) {
                                inst.rs2 = itr1->second;
                            }
                            else {
                                return false;
                            }
                            cout<<"\n\n"<<inst.rs2<<"\n\n";
                                
                        }
                        else
                        {   cout<<"\n"<<"hii";
                            return false;
                        }
                    }

                    count++;
                }
                else if (count == 3) {

                    if (type == "R_type") {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        cout<<Line.substr(i, j - i)<<"hello";
                        if (itr != reg_map.end()) {
                            inst.rs2 = itr->second;
                            
                        }
                        else {
                            
                            return false;
                        }
                    }
                    else if(type== "I_type"){

                        string temp = Line.substr(i, j - i);
                        cout<<'\n'<<temp;
                        try
                        {
                            inst.imd = stoi(temp);
                        }
                        catch (const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                            return false;
                        }
                            
                    }
                    else if(type=="B_type"){
                        string temp = Line.substr(i, j - i);
                        inst.label=temp;
                        
                    }

                    count++;
                }

                break;
            }
        }
        j++;
        while (Line[j] == ' ' || Line[j]==',') {
            j++;
        }
        i = j;
    }
    inst.type = type;
    cout<<inst.opcode<<inst.rd<<inst.rs1<<inst.rs2<<inst.imd<<"hello"<<"\n";
    return execute(inst);

}

//execution
bool execute( instruction inst) {
    int temp;
    
    if(inst.type=="R_type"){
        if (inst.opcode == "ADD") {
            temp = reg[inst.rs1] + reg[inst.rs2];
        }
        else if(inst.opcode=="SLT"){
            if(reg[inst.rs1] < reg[inst.rs2]){
                temp=1;
            }
            else{
                temp=0;
            }
        }
        else if(inst.opcode=="AND"){
            temp = reg[inst.rs1] & reg[inst.rs2];
        }
        else if(inst.opcode=="OR"){
            temp = reg[inst.rs1] | reg[inst.rs2];
        }
        else if(inst.opcode=="XOR"){
            temp = reg[inst.rs1] ^ reg[inst.rs2];
        }
        else if(inst.opcode=="SLL"){
            temp = reg[inst.rs1] << reg[inst.rs2];
        }
        else if(inst.opcode=="SRL"){
            temp = reg[inst.rs1] >> reg[inst.rs2];
        }
        else if(inst.opcode=="SUB"){
            temp = reg[inst.rs1] - reg[inst.rs2];
        }
    }
    else if (inst.type == "I_type") {
        if (inst.opcode == "ADDI") {
            temp = reg[inst.rs1] + inst.imd;
        }
        else if (inst.opcode == "SLTI") {
            if(reg[inst.rs1] < inst.imd){
                temp=1;
            }
            else{
                temp=0;
            }
        }
        else if (inst.opcode == "ANDI") {
            temp = reg[inst.rs1] & inst.imd;
        }
        else if (inst.opcode == "ORI") {
            temp = reg[inst.rs1] | inst.imd;
        }
        else if (inst.opcode == "XORI") {
            temp = reg[inst.rs1] ^ inst.imd;
        }
        else if (inst.opcode == "JALR") {  
            temp=pc;
            pc = reg[inst.rs1]+inst.imd;
        }
    }
    else if (inst.type == "B_type") {
        if (inst.opcode == "BEQ") {
            
            
            if(reg[inst.rs1] == reg[inst.rs2]){
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                cout<<pc<<" ";
                
                pc=itr->second;
                cout<<pc<<"\n";
                
            }

        }
        else if (inst.opcode == "BNE") {
            

            if(reg[inst.rs1] != reg[inst.rs2]){
                cout<<"myself"<<"    "<<"hello"<<inst.label<<"hello";
                auto itr = tags.begin();
                
                for(;itr!=tags.end();itr++){
                    cout<<"\n"<<itr->first<<"hello"<<"\n";
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                cout<<pc<<" ";
                
                pc=itr->second;
                cout<<pc<<"\n";
                
            }
        }
        else if (inst.opcode == "BLT") {
            

            if(reg[inst.rs1] < reg[inst.rs2]){
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                cout<<pc<<" ";
                
                pc=itr->second;
                cout<<pc<<"\n";
                
            }
        }
        else if (inst.opcode == "BGE") {
            

            if(reg[inst.rs1] >= reg[inst.rs2]){
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                cout<<pc<<" ";
                
                pc=itr->second;
                cout<<pc<<"\n";
                
            }
        }
        
    }
    else if(inst.type=="J_type"){
         if(inst.opcode=="JAL"){
             temp=pc;
             pc--;
             pc=pc+inst.imd;
         }
         else if(inst.opcode=="LI"){
             temp=inst.imd;
         }
    }
    else if(inst.type=="Load_type"){
        temp=inst.offset+reg[inst.rs1];
    }
    else if(inst.type=="Store_type"){
        temp=inst.offset+reg[inst.rs2];
        cout<<"hel"<<temp<<"\n";
    }

    return memory(inst, temp);
    
}

bool memory(instruction inst, int ex_mem) {
    if (inst.type == "R_type" ||inst.type == "I_type" ||  inst.type == "B_type" || inst.type == "J_type" || inst.type=="Store_type"){
        int mem_wb = ex_mem;
        return write_back(inst, mem_wb);
    }
    else if(inst.type== "Load_type"){
        int mem_wb= mem[ex_mem];
        return write_back(inst, mem_wb);
    }
    return false;
}

bool write_back(instruction inst, int mem_wb) {
    if(inst.type == "R_type" || inst.type == "I_type" || inst.type == "J_type" || inst.type=="Load_type") {
        reg[inst.rd] = mem_wb;
        return true;
    }
    else if(inst.type == "B_type") {
        return true;
    }
    else if(inst.type == "Store_type"){
        
        mem[mem_wb]=reg[inst.rs1];
        return true;
    }
    return false;
}



void parser() {
    std::ifstream file("input.txt");
    std::string str;
    vector<pair<int, string>>Lines;
    int inst_number = 1;
    bool isTag=false;
    int i=0;
    while (std::getline(file, str))
    {
        if (!str.empty() && (str != " ") && (str.find_first_not_of(' ') != std::string::npos)) {
            if(str.find(':') != string::npos){
               str=trim(str);
               string sub_str=trim(str.substr(0,str.length()-1));
               isTag=true;
               
               tags.push_back(pair<string,int>(sub_str,0));
            }
            else{
                if(isTag==true){
                     tags.rbegin()->second=i;
                     cout<<tags.rbegin()->first<<" "<<tags.rbegin()->second<<'\n';
                     isTag=false;
                }
                string trimmed_str = trim(str);
                Lines.push_back(pair<int, string>(inst_number, trimmed_str));
                i++;
            }
            
        }
        inst_number++;
    }

    file.close();



    while (pc != -1) {
        if (inst_fetch(Lines)) {

        }
        else {
            cout << pc << '\n';
            cout << "Error in Line number " << Lines[--pc].first;
            break;
        }
    }

    
}


void create_map(map<string, int>& reg_map) {

    for (int i = 0; i < 32; i++) {
        string str = "x";
        str += to_string(i);
        cout<<str<<"hello"<<endl;
        reg_map.insert(pair<string, int>(str, i));
    }

}

void display() {
    ofstream fout;
    fout.open("output1.txt");
    fout << '\n';
    fout << "registers.............." << endl;

    for (int i = 0; i < 32; i++) {
        fout << "reg[" << i << "]" << '\t' << reg[i] << '\n';
    }

    fout << endl;

    fout << "memory.................."<<endl;

    for (int i = 0; i < 32; i++) {
        fout << "mem[" << i << "]" << '\t' << mem[i] << '\n';
    }

}

int main() {
    pc = 0;
    create_map(reg_map);
    parser();

    display();


}