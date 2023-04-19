#include<bits/stdc++.h>
#include "table.cpp"
#include "removetabs.cpp"
using namespace std;
ifstream srcfile;
ofstream interfile,errorfile;
bool flag = true;
bool org;
ll orgstrt;
string currentsection;
ll startingaddress;
ll stringhextoint(string f){
      ll h = stoul(f, nullptr, 16);

      return h;
}
string getOpcode(string opcode)
{
  if (opcode[0] == '+')
  {
    return opcode.substr(1, opcode.length() - 1);
  }
  return opcode;
}
bool if_all_num(string x)
{
  bool all_num = true;
  int i = 0;
  while (all_num && (i < x.length()))
  {
    all_num &= isdigit(x[i++]);
  }
  return all_num;
}

string intToStringHex(int x,int fill = 5){

  stringstream s;
  s << setfill('0') << setw(fill) << hex << x;
  string temp = s.str();
  temp = temp.substr(temp.length() - fill, fill);
  transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
  return temp;
}
ll Evaluate(string operand,bool &flag,string word,ofstream &errorfile,bool kar){
vector<string>label;
vector<char>operators;
string z;
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
for(auto c:label){
 
    if(CSECTAB[currentsection].SYMTAB[c].exist=='n'){
        if(!if_all_num){
            errorfile<<"this symbol doesnt exist in SYMTAB"<<c<<endl;
            flag = false;
        }
    }
}
if(flag==true){
    
ll fg =0;

if(!if_all_num(label[0])){
    val = stringhextoint(CSECTAB[currentsection].SYMTAB[label[0]].value);
    
    fg++;
}
else{
    val = stoi(label[0]);
   
}
for(ll i = 0;i<label.size()-1;i++){

    if(!if_all_num(label[i+1])&&operators.size()!=0){
    
    if(operators[i]=='+'){
    fg++;
    val += stringhextoint(CSECTAB[currentsection].SYMTAB[label[i+1]].value);
    }
    else if(operators[i]=='-'){
        fg--;
        val -= stringhextoint(CSECTAB[currentsection].SYMTAB[label[i+1]].value);
    }
    else{
          errorfile<<"invalid expression "<<label[i]<<operators[i]<<label[i+1]<<endl;
            flag = false;
            break;
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
    else{
          errorfile<<"invalid expression "<<operand<<endl;
            flag = false;
            break;
    }
}
}
if(kar){
if(fg ==0){
    CSECTAB[currentsection].SYMTAB[word].type = 'a';
}
else if(fg==1){
     CSECTAB[currentsection].SYMTAB[word].type = 'r';
}
else{
      errorfile<<"invalid expression "<<operand<<endl;
}
}
if(kar==1){
    CSECTAB[currentsection].SYMTAB[word].value = val;
}

}
 
return val;
}
void pass1(){
string opcode,label,operand;

preprocess(); //do preprocess for removing tabs in src file
srcfile.open("updatespaces.txt");
interfile.open("intermediatefile.txt");
errorfile.open("errorfile.txt");
load_optab();                                 /////////////////////////////////////
load_regtab();                                            ////////////////////////////////////////////
string line;
ll LOCCTR ;
errorfile<<"errors in the code "<<endl;
 
while(getline(srcfile,line)){
    
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
if(t.size()!=0){                                              ////////////////////////////////////
words.push_back(t);     //cout<<words[0]<<endl;
 
}
if(words[0]!="END"){
  
if(words.size()>1&&words[0]!="ORG"&&words[words.size()-1]!="RSUB"){
      
if(words[1]!="CSECT"&&words[0]!="."){

if(words.size()==3&&words[0]!="EXTDEF"&&words[0]!="EXTREF"){       
   
    label = words[0];
    opcode = words[1];
     operand = words[2];
    if(opcode=="START"){
     startingaddress = stringhextoint(words[2]);                                  
  LOCCTR = startingaddress;    //LOC = 0

   currentsection = words[0];
 interfile<< "  " + intToStringHex(LOCCTR)+"   "+ line<<endl;
    }
    else{
       if(opcode=="EQU"){
     if(operand!="*"){
   
       ll val =  Evaluate(operand,flag,label,errorfile,1);
      
       interfile<<"  "+intToStringHex(val)+"  "+line<<endl; 
        if(CSECTAB[currentsection].SYMTAB[label].exist=='n'){
             CSECTAB[currentsection].SYMTAB[label].exist = 'y';
            CSECTAB[currentsection].SYMTAB[label].value = intToStringHex(val);
            CSECTAB[currentsection].SYMTAB[label].name = label;
            CSECTAB[currentsection].SYMTAB[label].sectionname = currentsection;
            if(CSECTAB[currentsection].extdef_tab[label].exist == 'y'){
                CSECTAB[currentsection].extdef_tab[label].address = CSECTAB[currentsection].SYMTAB[label].value;  //we need to store extdef in conttab
            }
        }
      else{
         errorfile<<"Symbol already present in symbol table Duplicate symbol for label defined at  " + CSECTAB[currentsection].SYMTAB[label].value<<endl;
            flag =  false;}
      }
      else{
        interfile<<"  "+intToStringHex(LOCCTR)+"  "+line<<endl;
        
        if(CSECTAB[currentsection].SYMTAB[label].exist=='n'){
             CSECTAB[currentsection].SYMTAB[label].exist = 'y';
            CSECTAB[currentsection].SYMTAB[label].value = intToStringHex(LOCCTR);
            CSECTAB[currentsection].SYMTAB[label].sectionname = currentsection;
            CSECTAB[currentsection].SYMTAB[label].name = label;
            CSECTAB[currentsection].SYMTAB[label].type = 'r';
            if(CSECTAB[currentsection].extdef_tab[label].exist == 'y'){
                CSECTAB[currentsection].extdef_tab[label].address = CSECTAB[currentsection].SYMTAB[label].value;  //we need to store extdef in conttab
            }
             
        }
        else{
             errorfile<<"Symbol already present in symbol table Duplicate symbol for label defined at  " + CSECTAB[currentsection].SYMTAB[label].value<<endl;
            flag =  false;
        }
      }
      
      
       }
     else{
        //symtab
        if(CSECTAB[currentsection].SYMTAB[label].exist=='y'){
            errorfile<<"Symbol already present in symbol table Duplicate symbol for label defined at  " + CSECTAB[currentsection].SYMTAB[label].value<<endl;
            flag =  false;
        }
        else{
            CSECTAB[currentsection].SYMTAB[label].exist = 'y';                                 //////////////////////////////////
            CSECTAB[currentsection].SYMTAB[label].value = intToStringHex(LOCCTR);              /////////////////////////////////
            CSECTAB[currentsection].SYMTAB[label].name = label;                                 ////////////////////////////////////
            CSECTAB[currentsection].SYMTAB[label].type = 'r';                                  ////////////////////////////////////////
            CSECTAB[currentsection].SYMTAB[label].sectionname = currentsection;                 ///////////////////////////////////
            if(CSECTAB[currentsection].extdef_tab[label].exist == 'y'){                          ///////////////////////////////////////
                CSECTAB[currentsection].extdef_tab[label].address = CSECTAB[currentsection].SYMTAB[label].value;  //we need to store extdef in conttab
            
            }
             
             interfile<< "  " + intToStringHex(LOCCTR) + "  " + label + "  " + opcode + "  " + "  " + operand<<endl;
        }
        //symtabends
         //opcodebegins
     }
        if(opcode[0]=='+'){
           LOCCTR+=4;
                if(OPTAB[getOpcode(opcode)].exist=='n'&&opcode!="*"&&opcode!="EQU"&&opcode!="END") {
                    
    errorfile<<"Opcode doesnt exist  "<<opcode<<endl;
                }                                      /////////////////// what if opcode doesn't present in optab
        }
        else{
          if(OPTAB[opcode].exist=='n'){
           
            if(opcode=="WORD"){
                LOCCTR+=3;
            }
            else if(opcode=="RESW"){
                 LOCCTR += 3 * Evaluate(operand,flag,label,errorfile,0) ;
            }
            else if(opcode == "BYTE"){
                if(operand[0]=='X'){
                LOCCTR+= (operand.length()-3)/2;
            }
            else if(operand[0]=='C'){
             
                LOCCTR+= operand.length()-3;
            }
            
            }
            else if(opcode == "RESB"){
                LOCCTR+=Evaluate(operand,flag,label,errorfile,0); 
                
            }
            else if(opcode!="*"&&opcode!="EQU"&&opcode!="END"){
                errorfile<<"opcode doesnt exist  "<<opcode<<endl;
            }
          }
          else{
           if(OPTAB[opcode].format==1){
            LOCCTR+=1;
           }
           else if(OPTAB[opcode].format ==2){
            LOCCTR+=2;
           }
           else{
            LOCCTR+=3;
             
           }
          }
        }
        //opcodeends
        
        
       
    }
}

else if(words[0]=="EXTDEF"){
    string wrs = words[1];
    string k ;
     stringstream ss(wrs);              ///////////////////////////////////////////////////////

    while (getline(ss, k, ',')) {
       CSECTAB[currentsection].extdef_tab[k].name = k;
        CSECTAB[currentsection].extdef_tab[k].exist = 'y';
    }
       
     interfile<<"  "+line<<endl;    
}
else if(words[0]=="EXTREF"){
 string wrs = words[1];
    string k ;
     stringstream ss(wrs); 

    while (getline(ss, k, ',')) {
       CSECTAB[currentsection].extref_tab[k].name = k;
        CSECTAB[currentsection].extref_tab[k].exist = 'y';
    }
       
    interfile<<"  "+line<<endl; 
}
    
else if(words.size()==2&&words[0]!="ORG"){ //&&words[1][0]!='='
opcode = words[0];
operand = words[1];
     
      if(opcode=="BASE"){
            interfile<<"             " + line<<endl;
        }
        
        else{
    interfile<<"  "+intToStringHex(LOCCTR)+"  "+line<<endl; 
 if(opcode[0]=='+'){
    
           LOCCTR+=4;                                                  /////////////////// what if opcode doesn't present in optab
 if(OPTAB[getOpcode(opcode)].exist=='n'&&opcode!="*"&&opcode!="EQU"&&opcode!="END") {
    errorfile<<"Opcode doesnt exist  "<<opcode<<endl;
                }
        }
        else{
          
           if(OPTAB[getOpcode(opcode)].exist=='n'&&opcode!="*"&&opcode!="EQU"&&opcode!="END") {
    errorfile<<"Opcode doesnt exist  "<<opcode<<endl;
                }
           if(OPTAB[opcode].format==1){
            LOCCTR+=1;
           }
           else if(OPTAB[opcode].format ==2){
            LOCCTR+=2;
           }
           
           else {
            LOCCTR+=3;
             
           }
           
          }
            
}
}//elseif for size = 2 ends
if(words[words.size()-1][0]=='='){  //Literal tab                                   /////////////////////////////////////
            string litname = words[words.size()-1].substr(0,words[words.size()-1].length());
           
            string act_literal = words[words.size()-1].substr(3,words[words.size()-1].length()-4);
            
            if(CSECTAB[currentsection].LITTAB[litname].exist=='n'){
            CSECTAB[currentsection].LITTAB[litname].name = litname;
            CSECTAB[currentsection].LITTAB[litname].validbit = 1;
            CSECTAB[currentsection].LITTAB[litname].exist = 'y';
            CSECTAB[currentsection].LITTAB[litname].length = litname.size()-4; //to remove two single quotes & X or C
                    if(litname[1]=='X'){

                CSECTAB[currentsection].LITTAB[litname].value= act_literal;

                
            }
            else if(litname[1]=='C'){
                
                string realascii = "";
                for(auto c:act_literal){
                 int h = c;
                 realascii +=intToStringHex(h,2);}  
                 
                 CSECTAB[currentsection].LITTAB[litname].value = realascii;
                   
               
            }
            }
           
            
            
    
        }
}// crtical section ends here
else if(words[1]=="CSECT"){
      for(auto d: CSECTAB[currentsection].LITTAB){
        if(CSECTAB[currentsection].LITTAB[d.first].validbit==1){
            CSECTAB[currentsection].LITTAB[d.first].validbit=0;
            if(d.first[1]=='X'){
                LOCCTR+= CSECTAB[currentsection].LITTAB[d.first].length/2;
            }
            else if(d.first[1]=='C'){
                LOCCTR+= CSECTAB[currentsection].LITTAB[d.first].length;
            }
            CSECTAB[currentsection].LITTAB[d.first].address=intToStringHex(LOCCTR);
            interfile<<"  "+intToStringHex(LOCCTR)+"  "+"  *    "+CSECTAB[currentsection].LITTAB[d.first].name<<endl; 

        }


      }
    CSECTAB[currentsection].LENGTH = LOCCTR-startingaddress;
    LOCCTR = 0;
    currentsection = words[0];
    
   interfile<<"  "+intToStringHex(LOCCTR)+"  "+line<<endl;
}

}

else if(words[0]=="ORG"){
            interfile<<"             " + line<<endl;
            if(org==false){
                orgstrt = LOCCTR;
                LOCCTR = stringhextoint(words[1]);
              
                org = true;
            }
            else{
                  
                LOCCTR = orgstrt;
                org = false;
            }

        }
else if(words[words.size()-1]=="RSUB"){
      if(words.size()==2){
    CSECTAB[currentsection].SYMTAB[words[0]].value=intToStringHex(LOCCTR);
    CSECTAB[currentsection].SYMTAB[words[0]].exist = 'y';
    CSECTAB[currentsection].SYMTAB[words[0]].name = words[0];
     
   }
     interfile<<"  "+intToStringHex(LOCCTR)+"  "+line<<endl; 
     LOCCTR+=3;
  
}
else if(words.size()==1){
   
  
     if(words[0]=="LTORG"){
      interfile<<"             " + line<<endl;
      for(auto m: CSECTAB[currentsection].LITTAB){
        if(CSECTAB[currentsection].LITTAB[m.first].validbit==1){
           
            interfile<<"  "+intToStringHex(LOCCTR)+"  "+"  *    "+CSECTAB[currentsection].LITTAB[m.first].name<<endl; 
            CSECTAB[currentsection].LITTAB[m.first].validbit=0;
           CSECTAB[currentsection].LITTAB[m.first].address=intToStringHex(LOCCTR);
           
            if(m.first[1]=='X'){
                LOCCTR+= CSECTAB[currentsection].LITTAB[m.first].length/2;
            }
            else if(m.first[1]=='C'){
               // cout<<CSECTAB[currentsection].LITTAB[m.first].length<<endl;
                LOCCTR+= CSECTAB[currentsection].LITTAB[m.first].length;
            }
            
           

        }


      }
    }
}
else{
    interfile<<"             " + line<<endl;
}
}
else{
    
     interfile<<"             " + line<<endl;
     break;
}

}//getline
for(auto d: CSECTAB[currentsection].LITTAB){
    interfile<<"  "+intToStringHex(LOCCTR)+"  "+"  *    "+CSECTAB[currentsection].LITTAB[d.first].name<<endl; 
        if(CSECTAB[currentsection].LITTAB[d.first].validbit==1){
            CSECTAB[currentsection].LITTAB[d.first].validbit=0;
             CSECTAB[currentsection].LITTAB[d.first].address=intToStringHex(LOCCTR);
            if(d.first[1]=='X'){
                LOCCTR+= CSECTAB[currentsection].LITTAB[d.first].length/2;
            }
            else if(d.first[0]=='C'){
                LOCCTR+= CSECTAB[currentsection].LITTAB[d.first].length;
            }
           
           

        }


      }
    CSECTAB[currentsection].LENGTH = LOCCTR-startingaddress;

interfile.close();
srcfile.close();
//intmain

    //cout<<CSECTAB["WRREC"].LITTAB["=X'05'"].value;
        
      }