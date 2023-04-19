#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void preprocess() {
ifstream remove;
ofstream update;
update.open("updatespaces.txt");
remove.open("srcfile.txt");
string line;
string spaceline = "";
while(getline(remove,line)){
    string spaceline = "";
    for(int i = 0;i<line.length();i++){
if(line[i]=='\t'){
spaceline+="     ";
}
else{
    spaceline +=line[i];
}

    }
    update<<spaceline<<endl;
}
}