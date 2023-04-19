#include<bits/stdc++.h>
using namespace std;
#define ll long long 

struct extref{
    string name;
    string address;
    char exist;
    extref(){
        name = "undefined";
        exist = 'n';
        address = "0";

    }

};

struct extdef{
    
  string name;
    string address;
    char exist;
    extdef(){
        name = "undefined";
        exist = 'n';
        address = "0";

    }

};
struct literal{
  char exist;
  string name;
  string address;
  string  value;
  int length;
  int validbit;
  literal(){
    exist = 'n';
    name = "undefined";
    address = "0";
    value = "0";
    length = 0;
    validbit = 0;  //for LTORG

  }
};
struct label{
    char exist;
    string value;
    char type;
    string name;
    string sectionname;
    label(){
        name = "undefined";
        value = "0";
        type = 'r';
        exist = 'n';
        sectionname = "DEFAULT";
    }
};
struct cont_sect{

string LOCCTR;
string name;
ll LENGTH;
ll sect_num;

map<string,extref> extref_tab;
map<string,extdef> extdef_tab;
map<string,label> SYMTAB;
map<string,literal>LITTAB;
vector<string>mod;
cont_sect(){
    LOCCTR = "0";
    name = "undefined";
    LENGTH  = 0;
    sect_num = 0;
}
};
struct s_opcode
{
  string opcode;
  int format;
  char exist;
  s_opcode()
  {
    opcode = "undefined";
    format = 0;
    exist = 'n';
  }
};
struct s_reg{
char exist;
char num;
s_reg(){
    exist = 'n';
    num = 'F';
}
};




map<string,s_opcode> OPTAB;
map<string,s_reg>REGTAB;
map<string,cont_sect>CSECTAB;
void load_optab(){

OPTAB["ADD"].opcode = "18";
OPTAB["ADD"].format = 3;    //ADD
OPTAB["ADD"].exist = 'y';

OPTAB["ADDR"].opcode = "90";
OPTAB["ADDR"].format = 2;
OPTAB["ADDR"].exist = 'y';

OPTAB["ADDF"].opcode = "58";
OPTAB["ADDF"].format = 3;
OPTAB["ADDF"].exist = 'y';

OPTAB["AND"].opcode = "40";
OPTAB["AND"].format = 3;
OPTAB["AND"].exist = 'y';

OPTAB["CLEAR"].opcode = "B4";
OPTAB["CLEAR"].format = 2;
OPTAB["CLEAR"].exist = 'y';

OPTAB["COMPF"].opcode = "88";
OPTAB["COMPF"].format = 3;
OPTAB["COMPF"].exist = 'y';

OPTAB["COMPR"].opcode = "A0";
OPTAB["COMPR"].format = 2;
OPTAB["COMPR"].exist = 'y';

OPTAB["COMP"].opcode = "28";
OPTAB["COMP"].format = 3;
OPTAB["COMP"].exist = 'y';

OPTAB["DIV"].opcode = "24";
OPTAB["DIV"].format = 3;
OPTAB["DIV"].exist = 'y';

OPTAB["DIVF"].opcode = "64";
OPTAB["DIVF"].format = 3;
OPTAB["DIVF"].exist = 'y';

OPTAB["DIVR"].opcode = "9C";
OPTAB["DIVR"].format = 2;
OPTAB["DIVR"].exist = 'y';

OPTAB["FLOAT"].opcode = "C0";
OPTAB["FLOAT"].format = 1;
OPTAB["FLOAT"].exist = 'y';

OPTAB["HIO"].opcode = "F4";
OPTAB["HIO"].format = 1;
OPTAB["HIO"].exist = 'y';

OPTAB["FIX"].opcode = "C4";
OPTAB["FIX"].format = 1;
OPTAB["FIX"].exist = 'y';

OPTAB["J"].opcode = "3C";
OPTAB["J"].format = 3;
OPTAB["J"].exist = 'y';

OPTAB["JEQ"].opcode = "30";
OPTAB["JEQ"].format = 3;
OPTAB["JEQ"].exist = 'y';

OPTAB["JGT"].opcode = "34";
OPTAB["JGT"].format = 3;
OPTAB["JGT"].exist = 'y';

OPTAB["JLT"].opcode = "38";
OPTAB["JLT"].format = 3;
OPTAB["JLT"].exist = 'y';

  OPTAB["JSUB"].opcode = "48";
  OPTAB["JSUB"].format = 3;
  OPTAB["JSUB"].exist = 'y';

  OPTAB["LDA"].opcode = "00";
  OPTAB["LDA"].format = 3;
  OPTAB["LDA"].exist = 'y';

  OPTAB["LDB"].opcode = "68";
  OPTAB["LDB"].format = 3;
  OPTAB["LDB"].exist = 'y';

  OPTAB["LDCH"].opcode = "50";
  OPTAB["LDCH"].format = 3;
  OPTAB["LDCH"].exist = 'y';

  OPTAB["LDF"].opcode = "70";
  OPTAB["LDF"].format = 3;
  OPTAB["LDF"].exist = 'y';

  OPTAB["LDT"].opcode = "74";
  OPTAB["LDT"].format = 3;
  OPTAB["LDT"].exist = 'y';


  OPTAB["LDL"].opcode = "08";
  OPTAB["LDL"].format = 3;
  OPTAB["LDL"].exist = 'y';


  OPTAB["LPS"].opcode = "D0";
  OPTAB["LPS"].format = 3;
  OPTAB["LPS"].exist = 'y';

  OPTAB["LDS"].opcode = "6C";
  OPTAB["LDS"].format = 3;
  OPTAB["LDS"].exist = 'y';


  OPTAB["LDX"].opcode = "04";
  OPTAB["LDX"].format = 3;
  OPTAB["LDX"].exist = 'y';


  OPTAB["MULR"].opcode = "98";
  OPTAB["MULR"].format = 2;
  OPTAB["MULR"].exist = 'y';

  OPTAB["MUL"].opcode = "20";
  OPTAB["MUL"].format = 3;
  OPTAB["MUL"].exist = 'y';

  OPTAB["MULF"].opcode = "60";
  OPTAB["MULF"].format = 3;
  OPTAB["MULF"].exist = 'y';


  OPTAB["NORM"].opcode = "C8";
  OPTAB["NORM"].format = 1;
  OPTAB["NORM"].exist = 'y';

  OPTAB["OR"].opcode = "44";
  OPTAB["OR"].format = 3;
  OPTAB["OR"].exist = 'y';

  OPTAB["RD"].opcode = "D8";
  OPTAB["RD"].format = 3;
  OPTAB["RD"].exist = 'y';

  OPTAB["RMO"].opcode = "AC";
  OPTAB["RMO"].format = 2;
  OPTAB["RMO"].exist = 'y';

  OPTAB["RSUB"].opcode = "4F";
  OPTAB["RSUB"].format = 3;
  OPTAB["RSUB"].exist = 'y';

  OPTAB["SHIFTL"].opcode = "A4";
  OPTAB["SHIFTL"].format = 2;
  OPTAB["SHIFTL"].exist = 'y';

  OPTAB["SHIFTR"].opcode = "A8";
  OPTAB["SHIFTR"].format = 2;
  OPTAB["SHIFTR"].exist = 'y';

  OPTAB["SIO"].opcode = "F0";
  OPTAB["SIO"].format = 1;
  OPTAB["SIO"].exist = 'y';

  OPTAB["SSK"].opcode = "EC";
  OPTAB["SSK"].format = 3;
  OPTAB["SSK"].exist = 'y';

  OPTAB["STA"].opcode = "0C";
  OPTAB["STA"].format = 3;
  OPTAB["STA"].exist = 'y';

  OPTAB["STB"].opcode = "78";
  OPTAB["STB"].format = 3;
  OPTAB["STB"].exist = 'y';

  OPTAB["STI"].opcode = "D4";
  OPTAB["STI"].format = 3;
  OPTAB["STI"].exist = 'y';

  OPTAB["STCH"].opcode = "54";
  OPTAB["STCH"].format = 3;
  OPTAB["STCH"].exist = 'y';

  OPTAB["STF"].opcode = "80";
  OPTAB["STF"].format = 3;
  OPTAB["STF"].exist = 'y';


  OPTAB["STL"].opcode = "14";
  OPTAB["STL"].format = 3;
  OPTAB["STL"].exist = 'y';


  OPTAB["STSW"].opcode = "E8";
  OPTAB["STSW"].format = 3;
  OPTAB["STSW"].exist = 'y';


  OPTAB["STS"].opcode = "7C";
  OPTAB["STS"].format = 3;
  OPTAB["STS"].exist = 'y';

  OPTAB["STX"].opcode = "10";
  OPTAB["STX"].format = 3;
  OPTAB["STX"].exist = 'y';

  OPTAB["STT"].opcode = "84";
  OPTAB["STT"].format = 3;
  OPTAB["STT"].exist = 'y';


  OPTAB["SUBR"].opcode = "94";
  OPTAB["SUBR"].format = 2;
  OPTAB["SUBR"].exist = 'y';

  OPTAB["SUB"].opcode = "1C";
  OPTAB["SUB"].format = 3;
  OPTAB["SUB"].exist = 'y';

  OPTAB["SUBF"].opcode = "5C";
  OPTAB["SUBF"].format = 3;
  OPTAB["SUBF"].exist = 'y';



OPTAB["SVC"].opcode = "B0";
OPTAB["SVC"].format = 2;
OPTAB["SVC"].exist = 'y';

OPTAB["TD"].opcode = "E0";
OPTAB["TD"].format = 3;
OPTAB["TD"].exist = 'y';

OPTAB["TIO"].opcode = "F8";
OPTAB["TIO"].format = 1;
OPTAB["TIO"].exist = 'y';

OPTAB["TIX"].opcode = "2C";
OPTAB["TIX"].format = 3;
OPTAB["TIX"].exist = 'y';

OPTAB["TIXR"].opcode = "B8";
OPTAB["TIXR"].format = 2;
OPTAB["TIXR"].exist = 'y';

OPTAB["WD"].opcode = "DC";
OPTAB["WD"].format = 3;
OPTAB["WD"].exist = 'y';


}

void load_regtab()
{
  REGTAB["A"].num = '0';
  REGTAB["A"].exist = 'y';


  REGTAB["X"].num = '1';
  REGTAB["X"].exist = 'y';


  REGTAB["L"].num = '2';
  REGTAB["L"].exist = 'y';


  REGTAB["B"].num = '3';
  REGTAB["B"].exist = 'y';


  REGTAB["S"].num = '4';
  REGTAB["S"].exist = 'y';


  REGTAB["T"].num = '5';
  REGTAB["T"].exist = 'y';


  REGTAB["F"].num = '6';
  REGTAB["F"].exist = 'y';


  REGTAB["PC"].num = '8';
  REGTAB["PC"].exist = 'y';


  REGTAB["SW"].num = '9';
  REGTAB["SW"].exist = 'y';

}
