#include <stimulator.h>

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
   
        int n = sizeof(J_type) / sizeof(J_type[0]);
        for (int i = 0; i < n; i++) {
            auto itr = Line.find(J_type[i]);
            if (itr != string::npos) {
                type = "J_type";
                is_set_type = true;
                break;
            }
        }
        
     if (!is_set_type) {
      n = sizeof(I_type) / sizeof(I_type[0]);
        for (int i = 0; i < n; i++) {
            auto itr = Line.find(I_type[i]);
            if (itr != string::npos) {
                type = "I_type";
                is_set_type = true;
                break;
            }
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

   

 
    //forming the instruction
    int i = 0;
    int j = i + 1;


    int count = 0;

    for (; i < Line.length();) {
        for (; j < Line.length(); j++) {
            if (Line[j] == ' ' || Line[j] == ',' || j == Line.length() - 1) {
                
                if (j == Line.length() - 1) { j++; }

                if (count == 0) {
                    inst.opcode = trim(Line.substr(i, j - i));
                    
                    count++;
                }
                else if (count == 1) {

                    if (type == "R_type" || type == "I_type" || type == "J_type" || type == "Load_type") {

                        
                            auto itr = reg_map.find(Line.substr(i, j - i));
                        
                            if (itr != reg_map.end()) {
                                inst.rd = itr->second;
                                
                            }
                            else {
                                return false;
                            }
                        
                        
                    }
                    else if(type=="B_type" || type=="Store_type"){

                        if(inst.opcode=="j"){
                            string temp = trim(Line.substr(i, j - i));
                            inst.label=temp;
                            
                        }
                        else{
                            auto itr = reg_map.find(Line.substr(i, j - i));
                            if (itr != reg_map.end()) {
                                inst.rs1 = itr->second;
                            }
                            else {
                                return false;
                            }
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
                        if(inst.opcode != "j"){
                            auto itr = reg_map.find(Line.substr(i, j - i));
                            if (itr != reg_map.end()) {
                                inst.rs2 = itr->second;
                                
                            }
                            else {
                                return false;
                            }
                        }
                    }
                    else if (type == "J_type") {
                        
                        string temp=Line.substr(i, j - i);
                        
                        try
                        {   if( inst.opcode=="li" && temp.find('x')!=string::npos){
                                inst.imd = stoi(temp,0,16);
                                inst.imd=inst.imd-268500992;
                                reg[inst.rd].isAddr=true;
                               
                                if(inst.imd<0){return false;}
                            }
                            else{
                                inst.imd = stoi(temp);
                            }
                        }
                        catch (const std::exception& e)
                        {   
                            if(inst.opcode=="jal"){
                                inst.label=trim(temp);
                            }
                            else{
                                 errors.push_back(e.what()); 
                                 return false;
                            }
                           
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
                                errors.push_back(e.what());
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
                        
                        auto itr= sub_string.find('(');
                        
                        if (itr != string::npos) {
                            
                            string temp1=sub_string.substr(0,itr);
                            
                            try
                            {
                                inst.offset = stoi(temp1);
                            }
                            catch (const std::exception& e)
                            {
                                errors.push_back(e.what());
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
                            
                                
                        }
                        else
                        {   
                            return false;
                        }
                    }

                    count++;
                }
                else if (count == 3) {

                    if (type == "R_type") {
                        auto itr = reg_map.find(Line.substr(i, j - i));
                        
                        if (itr != reg_map.end()) {
                            inst.rs2 = itr->second;
                            
                        }
                        else {
                            
                            return false;
                        }
                    }
                    else if(type== "I_type"){

                        string temp = Line.substr(i, j - i);
                       
                        try
                        {
                            inst.imd = stoi(temp);
                        }
                        catch (const std::exception& e)
                        {
                            errors.push_back(e.what());
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
   
    return execute(inst);

}

//execution
bool execute( instruction inst) {
    int temp;
    
    if(inst.type=="R_type"){
        if (inst.opcode == "add") {
            temp = reg[inst.rs1].var + reg[inst.rs2].var;
        }
        else if(inst.opcode=="slt"){
            if(reg[inst.rs1].var < reg[inst.rs2].var){
                temp=1;
            }
            else{
                temp=0;
            }
        }
        else if(inst.opcode=="and"){
            temp = reg[inst.rs1].var & reg[inst.rs2].var;
        }
        else if(inst.opcode=="or"){
            temp = reg[inst.rs1].var | reg[inst.rs2].var;
        }
        else if(inst.opcode=="xor"){
            temp = reg[inst.rs1].var ^ reg[inst.rs2].var;
        }
        else if(inst.opcode=="sll"){
            temp = reg[inst.rs1].var << reg[inst.rs2].var;
        }
        else if(inst.opcode=="srl"){
            temp = reg[inst.rs1].var >> reg[inst.rs2].var;
        }
        else if(inst.opcode=="sub"){
            temp = reg[inst.rs1].var - reg[inst.rs2].var;
        }
    }
    else if (inst.type == "I_type") {
        if (inst.opcode == "addi") {
            temp = reg[inst.rs1].var + inst.imd;
        }
        else if (inst.opcode == "slti") {
            if(reg[inst.rs1].var < inst.imd){
                temp=1;
            }
            else{
                temp=0;
            }
        }
        else if (inst.opcode == "andi") {
            temp = reg[inst.rs1].var & inst.imd;
        }
        else if (inst.opcode == "ori") {
            temp = reg[inst.rs1].var | inst.imd;
        }
        else if (inst.opcode == "xori") {
            temp = reg[inst.rs1].var ^ inst.imd;
        }
        else if (inst.opcode == "jalr") {  
            temp=pc;
            pc = reg[inst.rs1].var+inst.imd;
        }
    }
    else if (inst.type == "B_type") {
        if (inst.opcode == "beq") {
            
            
            if(reg[inst.rs1].var == reg[inst.rs2].var){
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                
                
                pc=itr->second;
                
                
            }

        }
        else if (inst.opcode == "bne") {
            

            if(reg[inst.rs1].var != reg[inst.rs2].var){
                
                auto itr = tags.begin();
                
                for(;itr!=tags.end();itr++){
                    
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                
                
                pc=itr->second;
                
                
            }
        }
        else if (inst.opcode == "blt") {
            

            if(reg[inst.rs1].var < reg[inst.rs2].var){
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                
                
                pc=itr->second;
                
                
            }
        }
        else if (inst.opcode == "bge") {
            

            if(reg[inst.rs1].var >= reg[inst.rs2].var){
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                
                
                pc=itr->second;
               
                
            }
        }
        else if (inst.opcode == "ble") {
            

            if(reg[inst.rs1].var <= reg[inst.rs2].var){
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                
                
                pc=itr->second;
               
                
            }
        }
        else if (inst.opcode == "j") {          
           
                auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                
                
                pc=itr->second;
                           
        }
        
    }
    else if(inst.type=="J_type"){
         if(inst.opcode=="jal"){
             if(inst.label==" "){
                 temp=pc;
                 pc--;
                 pc=pc+inst.imd;
             }
             else{
                 temp=pc;
                 auto itr = tags.begin();

                for(;itr!=tags.end();itr++){
                    if(itr->first==inst.label){
                        break;
                    }
                }
                
                if(itr==tags.end()){return false;}
                
                
                pc=itr->second;
             }   
         }
         else if(inst.opcode=="li"){
             temp=inst.imd;
         }
    }
    else if(inst.type=="Load_type"){
        temp=inst.offset+reg[inst.rs1].var;
    }
    else if(inst.type=="Store_type"){
        temp=inst.offset+reg[inst.rs2].var;
        
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
        if(inst.rd!=0){
            
            reg[inst.rd].var = mem_wb;
            
        }
        return true;
    }
    else if(inst.type == "B_type") {
        return true;
    }
    else if(inst.type == "Store_type"){
        
        mem[mem_wb]=reg[inst.rs1].var;
        return true;
    }
    return false;
}


void dataseg_handler(string dataLine){
   
   auto itr = dataLine.find(':');

   if(trim(dataLine.substr(0,itr))==".word"){
       string temp = trim(dataLine.substr(itr+1,dataLine.length()));
       
       
        int i=0;
       for(int j=0;j<temp.length();j++){
           
           if(temp[j]==','|| j==temp.length()-1 || temp[j]==' '){
               if(j==temp.length()-1){j++;}
              
               mem[k]=stoi(trim(temp.substr(i,j)));
               i=j+1;
               k++;
               
           }
        
       }
   }
}



//string input
void parser(string input) {

    input=trim(input);
    stringstream ss(input);
    
    std::string str;
    vector<pair<int, string>>Lines;
    int inst_number = 1;
    bool isTag=false;
    bool isDataseg=false;
    int i=0;
   // std::getline(ss,str,'\n')

   
    
    while (std::getline(ss,str,'\n'))
    {   str=trim(str);
        if(str.find('#')!=std::string::npos){
            str= trim(str.substr(0,str.find('#')));
            
        }

        if(str==".data"){
            
            isDataseg=true;
            inst_number++;
            continue;
        }

        if(str==".text"){
            isDataseg=false;
            inst_number++;
            continue;
        }

        if(isDataseg){
            dataseg_handler(str);
            inst_number++;
            continue;
        }
        

        if (!str.empty() && (str != " ") && (str.find_first_not_of(' ') != std::string::npos)) {
            if(str.find(':') != string::npos){
               str=trim(str);
               string tag_str=trim(str.substr(0,str.find(':')));
               
               
               isTag=true;
               
               tags.push_back(pair<string,int>(tag_str,0));

               string Line_str=trim(str.substr(str.find(':')+1,str.length()));

               if (!Line_str.empty() && (Line_str != " ") && (Line_str.find_first_not_of(' ') != std::string::npos)){
                    tags.rbegin()->second=i;
                     
                     isTag=false;
                     Lines.push_back(pair<int, string>(inst_number, Line_str));
                     i++;
               }

            }
            else{
                if(isTag==true){
                     tags.rbegin()->second=i;
                     
                     isTag=false;
                }
                string trimmed_str = trim(str);
                Lines.push_back(pair<int, string>(inst_number, trimmed_str));
                i++;
            }
            
        }
        inst_number++;
    }

    



    while (pc != -1) {
        if (inst_fetch(Lines)) {

        }
        else {
            
            string error="Error in Line number " + to_string(Lines[--pc].first);
            errors.push_back(error);
            break;
        }
    }

    
}

void create_map(map<string, int>& reg_map) {

    for (int i = 0; i < 32; i++) {
        string str = "x";
        str += to_string(i);
       
        reg_map.insert(pair<string, int>(str, i));
    }

}

void stimulator(string input) {
    pc = 0;
    create_map(reg_map);
    //input
    parser(input);
    
}

