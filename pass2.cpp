#include "pass1.cpp"
#include<bits/stdc++.h>
using namespace std;
string writestring;
ifstream interfi;
ofstream objectfile,listingfile;
ofstream printtable;
string writeData;
vector<string>mod;
string modRecord = "";
string header = "H^";
string Define = "D";
string Refer = "R";
string test ;
string End = "E^";
ll cou = 0;
ll Textst = startingaddress;
long long pc;
long long basevalue;
bool base;
ll countcontrol = 0;
bool checkhexaloc(string str){

  bool flag = 1;
    

    for (int i=0; i<str.length(); i++)
    {
        if (!isxdigit(str[i]))
        {
            flag = 0;
            break;
        }
    }
    return flag;
}


void printmodification(){
for(auto c:CSECTAB[currentsection].mod){
  objectfile<<c<<endl;
}
}
string findval(string operand,string opcode,ll LOCCTR){
vector<string>label;
vector<char>operators;
string z;
string reallabel;
ll val;
for(ll i = 0;i<operand.size();i++){

    if(operand[i]!='+'&&operand[i]!='-'&&operand[i]!='*'&&operand[i]!='/'){
     z+=operand[i];
    }
  else{
    label.push_back(z);
    operators.push_back(operand[i]);
    z = "";
  }
}
label.push_back(z);
ll fg =0;
if(flag==true){
    


if(!if_all_num(label[0])){
    val = stringhextoint(CSECTAB[currentsection].SYMTAB[label[0]].value);
    reallabel = label[0];
   
    fg++;
      if(CSECTAB[currentsection].extref_tab[label[0]].exist=='y'){
     if(opcode=="WORD"){
       modRecord += "M^" + intToStringHex(LOCCTR , 6) + '^';
        modRecord+= "06+";
        modRecord += CSECTAB[currentsection].extref_tab[label[0]].name;
        CSECTAB[currentsection].mod.push_back(modRecord);
        
        modRecord = "";
     }
     else{
       modRecord += "M^" + intToStringHex(LOCCTR , 6) + '^';
        modRecord+= "05+";
        modRecord += CSECTAB[currentsection].extref_tab[label[0]].name;
         CSECTAB[currentsection].mod.push_back(modRecord);
        modRecord = "";
     }
    }
}
else{
    val = stoi(label[0]);
  reallabel = label[0];
}
if(label.size()>1){
for(ll i = 0;i<label.size()-1;i++){

    if(!if_all_num(label[i+1])&&operators.size()!=0){
      if(CSECTAB[currentsection].extref_tab[label[i+1]].exist=='y'){
     if(opcode=="WORD"){
       modRecord += "M^" + intToStringHex(LOCCTR , 6) + '^';
        modRecord+= "06";
        modRecord+=operators[i];
        modRecord += CSECTAB[currentsection].extref_tab[label[i+1]].name;
       
         CSECTAB[currentsection].mod.push_back(modRecord);
        
        modRecord = "";
     }
     else{
       modRecord += "M^" + intToStringHex(LOCCTR , 6) + '^';
        modRecord+= "05";
        modRecord+=operators[i];
        modRecord += CSECTAB[currentsection].extref_tab[label[i+1]].name;
         CSECTAB[currentsection].mod.push_back(modRecord);
        
        modRecord = "";
     }
    }
    if(operators[i]=='+'){
    fg++;
    val += stringhextoint(CSECTAB[currentsection].SYMTAB[label[i+1]].value);
    }
    else if(operators[i]=='-'){
        fg--;
        val -= stringhextoint(CSECTAB[currentsection].SYMTAB[label[i+1]].value);
    }
  
}
else if(operators.size()!=0){
    
    if(operators[i]=='+'){
    fg++;
    val += stoi(label[i+1]);
    }
    else if(operators[i]=='-'){
        fg--;
        val -= stoi(label[i+1]);
    }
}
}
}
}
if(opcode=="WORD"){
  
return intToStringHex(val,6);
}
else {
   
  return reallabel;
 
}
}

string evalobjcode(string opcode,string operand,string line,ll LOCCTR){

string objcode;
  int halfBytes;
  
  halfBytes = (opcode[0] == '+') ? 5 : 3;

  if (operand[0] == '#'){
    if(operand.size()>2){
    if (operand.substr(operand.length() - 2, 2) == ",X")
    {
      writeData =  line + " error: Index based addressing not supported with Indirect addressing";
      
      objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
      objcode += (halfBytes == 5) ? "100000" : "0000";
      return objcode;
    }
    }
    string tempOperand = operand.substr(1, operand.length() - 1);

      tempOperand = findval(tempOperand,opcode,LOCCTR);
     
    //  cout<<tempOperand<<endl;
     if(getOpcode(opcode)=="LDB"){
        base = true;
      

        if(checkhexaloc(tempOperand)){
          basevalue = stringhextoint(tempOperand);
        }
        else{
          basevalue = stringhextoint(CSECTAB[currentsection].SYMTAB[tempOperand].value);
        }
    }
     
    if (((checkhexaloc(tempOperand))&&CSECTAB[currentsection].SYMTAB[tempOperand].exist=='n') || ((CSECTAB[currentsection].SYMTAB[tempOperand].exist == 'y') && (CSECTAB[currentsection].SYMTAB[tempOperand].type == 'a') && (CSECTAB[currentsection].extref_tab[tempOperand].exist == 'n')))
    {
      int immediateValue;    //this if case is for either operand is number or absolute
       
      if (checkhexaloc(tempOperand))            
      { 
        immediateValue = stringhextoint(tempOperand);
        
      }
      else
      {
        immediateValue = stringhextoint(CSECTAB[currentsection].SYMTAB[tempOperand].value);
      }
      if (immediateValue >= (1 << 4 * halfBytes))
      {
        writeData = line + "  error: Immediate value exceeds format limit";
        errorfile<<writeData<<endl;;
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
        objcode += (halfBytes == 5) ? "100000" : "0000";
      }
      else
      {
       
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
        
        objcode += (halfBytes == 5) ? '1' : '0';
        
        objcode += intToStringHex(immediateValue, halfBytes);
      
      }
      return objcode;
    }
    else if (CSECTAB[currentsection].SYMTAB[tempOperand].exist == 'n' || CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
    { //this is for extref
     
      if (CSECTAB[currentsection].extref_tab[tempOperand].exist != 'y' || halfBytes == 3)
      {
        writeData = line;
        if (halfBytes == 3 && CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
        {
          writeData += " : Invalid format for external reference " + tempOperand;
        }
        else
        {
          writeData += " : Symbol doesn't exists. Found " + tempOperand;
        }
        errorfile<<writeData<<endl;;
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
        objcode += (halfBytes == 5) ? "100000" : "0000";
        return objcode;
      }

      if ( CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
      {
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
        objcode += "100000";

        modRecord += "M^" + intToStringHex(LOCCTR + 1, 6) + '^';
        modRecord+= "05+";
        modRecord += CSECTAB[currentsection].extref_tab[tempOperand].name;
        
        CSECTAB[currentsection].mod.push_back(modRecord);
        modRecord = "";
        return objcode;
      }
    }
    else
    {  //this is for labels which is relative.

      int operandAddress = stringhextoint(CSECTAB[currentsection].SYMTAB[tempOperand].value);
    
      if (halfBytes == 5)
      {
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
        objcode += '1';
        objcode += intToStringHex(operandAddress, halfBytes);

        modRecord += "M^" + intToStringHex(LOCCTR + 1, 6) + '^';
        modRecord += (halfBytes == 5) ? "05" : "03";
        modRecord += "+"+currentsection;
       
         CSECTAB[currentsection].mod.push_back(modRecord);
         modRecord="";
        return objcode;
      }

      pc = LOCCTR ;
      pc += (halfBytes == 5) ? 4 : 3;
      int relativeAddress = operandAddress - pc;

      if (relativeAddress >= (-2048) && relativeAddress <= 2047)
      {
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
        objcode += '2';
        objcode += intToStringHex(relativeAddress, halfBytes);
        return objcode;
      }

     else if (base)
      {
        relativeAddress = operandAddress - basevalue;
        if (relativeAddress >= 0 && relativeAddress <= 4095)
        {
          objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
          objcode += '4';
          objcode += intToStringHex(relativeAddress, halfBytes);
          return objcode;
        }
      }

      if (operandAddress <= 4095)
      {
      writeData = line ;
      writeData += "   Can't fit into program counter based or base register based addressing.";
      errorfile<<writeData<<endl;
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
        objcode += '0';
        objcode += intToStringHex(operandAddress, halfBytes);
        modRecord += "M^" + intToStringHex(LOCCTR + 1, 6) + '^';
        modRecord += (halfBytes == 5) ? "05" : "03";             /////why???
        modRecord += "+"+currentsection;
         CSECTAB[currentsection].mod.push_back(modRecord);

        return objcode;
      }
    writeData = line;
    writeData += "   Can't fit into program counter based or base register based addressing.";
    errorfile<<writeData<<endl;;
    objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 1, 2);
    objcode += (halfBytes == 5) ? "100000" : "0000";

    return objcode;
    }
  }
  else if (operand[0] == '@')
  {
    string tempOperand = operand.substr(1, operand.length() - 1);
    if (tempOperand.substr(tempOperand.length() - 2, 2) == ",X" || CSECTAB[currentsection].SYMTAB[tempOperand].exist == 'n' || CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y' )
    { // Error handling for Indirect with index based

      if (CSECTAB[currentsection].extref_tab[tempOperand].exist != 'y' || halfBytes == 3)
      {
        writeData = line ;
        if (halfBytes == 3 && CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
        {
          writeData += "  : Invalid format for external reference " + tempOperand;
        }
        else
        {
          writeData += " : Symbol doesn't exists.Index based addressing not supported with Indirect addressing ";
        }
        errorfile<<writeData<<endl;;
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 2, 2);
        objcode += (halfBytes == 5) ? "100000" : "0000";
        return objcode;
      }
      if (CSECTAB[currentsection].SYMTAB[tempOperand].exist == 'y' && CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
      {
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 2, 2);
        objcode += "100000";

        modRecord += "M^" + intToStringHex(LOCCTR + 1, 6) + '^';
        modRecord += "05+";
        modRecord += CSECTAB[currentsection].extref_tab[tempOperand].name;
         CSECTAB[currentsection].mod.push_back(modRecord);
         modRecord="";

        return objcode;
      }
    }
    int operandAddress = stringhextoint(CSECTAB[currentsection].SYMTAB[tempOperand].value);
    pc = LOCCTR;
    pc += (halfBytes == 5) ? 4 : 3;

    if (halfBytes == 3)
    {
      int relativeAddress = operandAddress - pc;
      if (relativeAddress >= (-2048) && relativeAddress <= 2047)
      {
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 2, 2);
        objcode += '2';
        objcode += intToStringHex(relativeAddress, halfBytes);
        return objcode;
      }

      if (base)
      {
        relativeAddress = operandAddress - basevalue;
        if (relativeAddress >= 0 && relativeAddress <= 4095)
        {
          objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 2, 2);
          objcode += '4';
          objcode += intToStringHex(relativeAddress, halfBytes);
          return objcode;
        }
      }

      if (operandAddress <= 4095)
      {
          writeData = line ;
      writeData += "   Can't fit into program counter based or base register based addressing.";
      errorfile<<writeData<<endl;
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 2, 2);
        objcode += '0';
        objcode += intToStringHex(operandAddress, halfBytes);
        modRecord += "M^" + intToStringHex(LOCCTR + 1, 6)+ '^';
        modRecord += (halfBytes == 5) ? "05" : "03";
        modRecord += "+"+currentsection;
         CSECTAB[currentsection].mod.push_back(modRecord);
         modRecord="";

        return objcode;
      }
    }
    else
    {
      objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 2, 2);
      objcode += '1';
      objcode += intToStringHex(operandAddress, halfBytes);
      modRecord += "M^" + intToStringHex(LOCCTR + 1, 6) + '^';
      modRecord += (halfBytes == 5) ? "05" : "03";
      modRecord += "+"+currentsection;
        CSECTAB[currentsection].mod.push_back(modRecord);
        modRecord="";

      return objcode;
    }

    writeData = line;
    writeData += "   Can't fit into program counter based or base register based addressing.";
    errorfile<<writeData<<endl;;
    objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 2, 2);
    objcode += (halfBytes == 5) ? "100000" : "0000";

    return objcode;
  }
  else if (operand[0] == '=')
  {
    
    string tempOperand = operand;
     
    if (tempOperand == "*")
    {
      tempOperand = "X'" + intToStringHex(LOCCTR, 6) + "'";
      modRecord += "M^" + intToStringHex(stringhextoint(CSECTAB[currentsection].LITTAB[tempOperand].address) , 6) + '^';
      modRecord += intToStringHex(6, 2);
      modRecord += "+"+currentsection;
      CSECTAB[currentsection].mod.push_back(modRecord);
      modRecord="";
    }

    if (CSECTAB[currentsection].LITTAB[tempOperand].exist == 'n')
    {
      writeData = line  + "  : Symbol doesn't exists. Found " + tempOperand;
      errorfile<<writeData<<endl;;

      objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
      objcode += (halfBytes == 5) ? "000" : "0";
      objcode += "000";
      return objcode;
    }

    int operandAddress = stringhextoint(CSECTAB[currentsection].LITTAB[tempOperand].address) ;
   
    pc = LOCCTR;
    pc += (halfBytes == 5) ? 4 : 3;

    if (halfBytes == 3)
    {
      int relativeAddress = operandAddress - pc;
      if (relativeAddress >= (-2048) && relativeAddress <= 2047)
      {
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
        objcode += '2';
        objcode += intToStringHex(relativeAddress, halfBytes);
        return objcode;
      }

      if (base)
      {
        relativeAddress = operandAddress - basevalue;
        if (relativeAddress >= 0 && relativeAddress <= 4095)
        {
          objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
          objcode += '4';
          objcode += intToStringHex(relativeAddress, halfBytes);
          return objcode;
        }
      }

      if (operandAddress <= 4095)
      {
         writeData = line ;
      writeData += "   Can't fit into program counter based or base register based addressing.";
      errorfile<<writeData<<endl;
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
        objcode += '0';
        objcode += intToStringHex(operandAddress, halfBytes);
        modRecord += "M^" + intToStringHex( LOCCTR+ 1, 6) + '^';
        modRecord += (halfBytes == 5) ? "05" : "03";
        modRecord += "+"+currentsection;
      CSECTAB[currentsection].mod.push_back(modRecord);
      modRecord="";

        return objcode;
      }
    }
    else
    {
      objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
      objcode += '1';
      objcode += intToStringHex(operandAddress, halfBytes);
      modRecord += "M^" + intToStringHex( LOCCTR+ 1, 6) + '^';
      modRecord += (halfBytes == 5) ? "05" : "03";
       modRecord += "+"+currentsection;
      CSECTAB[currentsection].mod.push_back(modRecord);
      modRecord="";

      return objcode;
    }

    writeData = line;
    writeData += "   Can't fit into program counter based or base register based addressing.";
    errorfile<<writeData<<endl;
    objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
    objcode += (halfBytes == 5) ? "100" : "0";
    objcode += "000";

    return objcode;
  }
  else
  {
    if(OPTAB[opcode].format==1){
      return opcode;
    }
    else if(OPTAB[opcode].format==2){
      vector<string>reg;
      string ks;
      stringstream sq(operand);
      while(getline(sq,ks,',')){
          reg.push_back(ks);
          if(REGTAB[ks].exist=='n'){
            flag = false;
            writeData = line+ " register name doesnt exist";
          }
      }

       objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) , 2);
      if(reg.size()==1){
        objcode+=REGTAB[reg[0]].num;
        objcode+='0';
      }
      else{
        objcode+=REGTAB[reg[0]].num;
        objcode+=REGTAB[reg[1]].num;
      }
      return objcode;
    }
    int xbpe = 0;
    string tempOperand = operand;
    if (operand.substr(operand.length() - 2, 2) == ",X")
    {
      tempOperand = operand.substr(0, operand.length() - 2);
      
      xbpe = 8;
    }

    if (CSECTAB[currentsection].SYMTAB[tempOperand].exist == 'n' || CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
    {
      if (CSECTAB[currentsection].extref_tab[tempOperand].exist != 'y' || halfBytes == 3)
      {

        writeData = line;
        if (halfBytes == 3 && CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
        {
          writeData += " : Invalid format for external reference " + tempOperand;
        }
        else
        {
          writeData += " : Symbol doesn't exists. Found " + tempOperand;
        }
        errorfile<<writeData<<endl;;
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
        objcode += (halfBytes == 5) ? (intToStringHex(xbpe + 1, 1) + "00") : intToStringHex(xbpe, 1);
        objcode += "000";
        return objcode;
      }

      if ( CSECTAB[currentsection].extref_tab[tempOperand].exist == 'y')
      {

        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
        if(xbpe==8){
        objcode += "900000";
        }
        else{
          objcode+="100000";
        }
        modRecord += "M^" + intToStringHex(LOCCTR + 1, 6) + '^';
        modRecord += "05+";
        modRecord += CSECTAB[currentsection].extref_tab[tempOperand].name;
        CSECTAB[currentsection].mod.push_back(modRecord);
         modRecord="";
        return objcode;
      }
    }
    else
    {

    int operandAddress = stringhextoint(CSECTAB[currentsection].SYMTAB[tempOperand].value) ;
    
    pc = LOCCTR;
    pc += (halfBytes == 5) ? 4 : 3;

      if (halfBytes == 3)
      {
        int relativeAddress = operandAddress - pc;
        if (relativeAddress >= (-2048) && relativeAddress <= 2047)
        {
          objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
          objcode += intToStringHex(xbpe + 2, 1);
          objcode += intToStringHex(relativeAddress, halfBytes);
          return objcode;
        }

        else if (base)
        {
          relativeAddress = operandAddress - basevalue;
          if (relativeAddress >= 0 && relativeAddress <= 4095)
          {
          
            objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
            objcode += intToStringHex(xbpe + 4, 1);
            objcode += intToStringHex(relativeAddress, halfBytes);
            return objcode;
          }
        }
      
        if (operandAddress <= 4095)
        {
      writeData = line ;
      writeData += "   Can't fit into program counter based or base register based addressing.";
      errorfile<<writeData<<endl;
          objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
          objcode += intToStringHex(xbpe, 1);
          objcode += intToStringHex(operandAddress, halfBytes);
          modRecord += "M^" + intToStringHex(LOCCTR + 1 , 6) + '^';
          modRecord += (halfBytes == 5) ? "05" : "03";
           modRecord += "+"+currentsection;
      
           CSECTAB[currentsection].mod.push_back(modRecord);
           modRecord="";

          return objcode;
        }
      }
      else
      {
        objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
        objcode += intToStringHex(xbpe + 1, 1);
        objcode += intToStringHex(operandAddress, halfBytes);
        modRecord += "M^" + intToStringHex(LOCCTR + 1, 6) + '^';
        modRecord += (halfBytes == 5) ? "05" : "03";
        modRecord += "+"+currentsection;
        CSECTAB[currentsection].mod.push_back(modRecord);
         modRecord="";


        return objcode;
      }

      writeData = line ;
      writeData += "   Can't fit into program counter based or base register based addressing.";
      errorfile<<writeData<<endl;
      objcode = intToStringHex(stringhextoint(OPTAB[getOpcode(opcode)].opcode) + 3, 2);
      objcode += (halfBytes == 5) ? (intToStringHex(xbpe + 1, 1) + "00") : intToStringHex(xbpe, 1);
      objcode += "000";

      return objcode;
    }
  }

}
int main(){
  cout<<"pass1 is started "<<endl;
   cout<<"................ "<<endl;
   cout<<"intermediate file is generated "<<endl;
    cout<<"................ "<<endl;
    pass1();
    
cout<<"pass1 is completed"<<endl;
  cout<<"pass2 is started "<<endl;
   cout<<"................ "<<endl;
currentsection = "DEFAULT";
string line;
interfi.open("intermediatefile.txt");
objectfile.open("objectfile.txt");
listingfile.open("listingfile.txt");
while(getline(interfi,line)){
  
vector<string>words;
string t = "";
bool form4 = false;
for(ll i = 0;i<line.length();i++){
    if(line[i]==' '){
        if(t.size()!=0){
         words.push_back(t);
      
        }
        t = "";
    }
    else{
        t = t+line[i];      ///parsing the string

    }
}

if(t.size()!=0){
words.push_back(t);   

}
 string eval;
if(words.size()>2&&words[0]!="EXTREF"&&words[0]!="EXTDEF"){
   
  if(words[2]=="RESW"||words[2]=="RESB"){
    if(cou>0){
  ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
   
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
    test = "^"+eval;
    cou = 0;
  
    }
      
  }
if(words[2]=="WORD"){
  
      if(if_all_num(words[3])){
      eval = intToStringHex(stoi(words[3]), 6);
      }
      else{
        eval = findval(words[3],words[2],stringhextoint(words[0]));
      }
      listingfile<<line<<"                 "<<eval<<endl;
     
   if(cou+eval.length()>60){
    ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "^"+eval;
    cou = eval.length();
    Textst = stringhextoint(words[0]);

     }
     else{
      if(cou==0){
        Textst = stringhextoint(words[0]);
      }
      test+="^"+eval;
      cou+=eval.length();}}
    if(words[2]=="BYTE"){
      if(words[3][0]=='X'){
      eval = words[3].substr(2,words[3].length()-3);
      }
      else{
        string act_literal = words[3].substr(2,words[3].size()-3);
         string realascii = "";
                for(auto c:act_literal){
                 int h = c;
                 realascii +=intToStringHex(h,2);} 
                 eval = realascii;
      }
 listingfile<<line<<"                 "<<eval<<endl;
     
   if(cou+eval.length()>60){
    ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "^"+eval;
    cou = eval.length();
    Textst = stringhextoint(words[0]);

     }
     else{
      if(cou==0){
        Textst = stringhextoint(words[0]);
      }
      test+="^"+eval;
      cou+=eval.length();}
    }
    if(checkhexaloc(words[0])&&(OPTAB[getOpcode(words[words.size()-2])].exist=='y')){
      
      
      string eval = evalobjcode(words[words.size()-2],words[words.size()-1],line,stringhextoint(words[0]));
      listingfile<<line<<"                 "<<eval<<endl;
     if(cou+eval.length()>60){
    ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "^"+eval;
    cou = eval.length();
    Textst = stringhextoint(words[0]);

     }
     else{
       if(cou==0){
        Textst = stringhextoint(words[0]);;
      }
      test+="^"+eval;
      cou+=eval.length();
     }
    }
   
 
    if(words[1]=="*"){
  eval = CSECTAB[currentsection].LITTAB[words[2]].value;
  CSECTAB[currentsection].LITTAB[words[2]].validbit==1;
  listingfile<<line<<"                 "<<eval<<endl;
   if(cou+eval.length()>60){
    ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "^"+eval;
    cou = eval.length();
    Textst = stringhextoint(words[0]);

     }
     else{
      if(cou==0){
        Textst = stringhextoint(words[0]);;
      }
      test+="^"+eval;
      cou+=eval.length();
     }
}
   else if(words[2]=="CSECT"||words[2]=="START"){
    if(words[2]=="CSECT"){
      if(cou>0){
ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "";
    cou = 0;
    Textst = stringhextoint(words[0]);
      }
      printmodification();
      countcontrol++;
    }
    else{
      countcontrol++;
      
    }
    if(words[2]=="CSECT"&&countcontrol==2){
    
objectfile<<"E^"<<intToStringHex(startingaddress,6)<<endl;
    }
    else if(words[2]=="CSECT"){
      objectfile<<"E"<<endl;
      
    }
    listingfile<<line<<endl;
      currentsection = words[1];
    
      string dupcurr = currentsection;
      Textst = startingaddress;

      objectfile<<endl;
      if(currentsection.length()>6){
        errorfile<<"sectionname length should not exceed more than 6  "<<words[1]<<endl;
      }
      else{
        while(dupcurr.length()<6){
          dupcurr+=" ";
        }
      }
     
      header = header+dupcurr+"^"+ intToStringHex(startingaddress,6)+"^"+ intToStringHex(CSECTAB[currentsection].LENGTH,6);
      objectfile<<header<<endl;

      header = "H^";
    }
    
}
else if(words[0]=="EXTDEF"){
listingfile<<line<<endl;
writeData = Define;

for(auto c:CSECTAB[currentsection].extdef_tab){
//cout<<c.first<<endl;
if(CSECTAB[currentsection].extdef_tab[c.first].exist=='y'){
  string dupcurr = c.first;
     
      if(dupcurr.length()>6){
        errorfile<<"label length should not exceed more than 6  "<<words[1]<<endl;
      }
      else{
        while(dupcurr.length()<6){
          dupcurr+=" ";
        }
      }
  writeData +="^"+dupcurr+"^"+intToStringHex(stringhextoint(CSECTAB[currentsection].extdef_tab[c.first].address),6);
 // cout<<writeData<<endl;
}
}
objectfile<<writeData<<endl;
}
else if(words[0]=="EXTREF"){
  listingfile<<line<<endl;
writeData = Refer;

for(auto c:CSECTAB[currentsection].extref_tab){
//cout<<c.first<<endl;
if(CSECTAB[currentsection].extref_tab[c.first].exist=='y'){
  string dupcurr = c.first;
     
      if(dupcurr.length()>6){
        errorfile<<"label length should not exceed more than 6  "<<words[1]<<endl;
      }
      else{
        while(dupcurr.length()<6){
          dupcurr+=" ";
        }
      }
  writeData +="^"+dupcurr;
 // cout<<writeData<<endl;
}
}
objectfile<<writeData<<endl;
}

else if(words.size()>1&&words[1]=="RSUB"){
  eval = "4F0000";
listingfile<<line<<"                 "<<eval<<endl;
   if(cou+eval.length()>60){
    ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "^"+eval;
    cou = eval.length();
    Textst = stringhextoint(words[0]);

     }
     else{
      if(cou==0){
        Textst = stringhextoint(words[0]);
      }
      test+="^"+eval;
      cou+=eval.length();
     }
}
else if(words[0]=="END"){
 
  for(auto d: CSECTAB[currentsection].LITTAB){
        if(CSECTAB[currentsection].LITTAB[d.first].validbit==0){
           eval = CSECTAB[currentsection].LITTAB[d.first].value;
         
  listingfile<<line<<"                 "<<eval<<endl;
   if(cou+eval.length()>60){
    ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "^"+eval;
    cou = eval.length();
    Textst = stringhextoint(words[0]);

     }
     else{
      if(cou==0){
        Textst = stringhextoint(words[0]);;
      }
      test+="^"+eval;
      cou+=eval.length();
     }
        }


      }
     
  if(cou>0){
     
     ll lent = cou/2;
    string codlen = intToStringHex(lent,2);
    objectfile<< "T^"<<intToStringHex(Textst,6)<<"^"<<codlen<<test<<endl;
    //cout<<"T^"<<intToStringHex(startingaddress,6)<<"^"<<codlen<<test<<endl;
     test = "^"+eval;
    cou = eval.length();
    
    Textst = stringhextoint(words[0]);
     
  }
 printmodification();
    
      objectfile<<"E^"<<intToStringHex(startingaddress,6)<<endl;
}

}
  cout<<"listed and object file is loaded "<<endl;
    cout<<"................ "<<endl;
     cout<<"pass2 is completed "<<endl;
   
}