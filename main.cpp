/**
 *	Author : Tarek Salah
 */
#include "Compresser.cpp"
#include "DeCompresser.cpp"
#include <iostream>
using namespace std;

int main(){
    cout<<"================================================================================"<<endl;
    cout<<"**********************************HUFFMAN CODING********************************"<<endl;
    cout<<"================================================================================"<<endl;
    cout<<"1==>Compress file"<<endl;
    cout<<"2==>Decompress file"<<endl;
    cout<<"3==>Exit"<<endl;
    cout<<"================================================================================"<<endl;
    int x;
    cin>>x;
    if(x==1){
      string s;
      cout<<"Enter the name of file"<<endl;
      getwchar();
      getline(cin,s);
      Compresser *c=new Compresser();
      c->main_App(s);
    }else if(x==2){
      string s;
      cout<<"Enter the name of file"<<endl;
      getwchar();
      getline(cin,s);
      DeCompresser *d=new DeCompresser();
      d->main_App(s);
    }else{
       exit(0);
    }
    cout<<"*************************************Thank You********************************"<<endl;
    getchar();
    return 0;
}
