/**
	Author : Tarek Salah
	this application make compression for text files using huffman algorithm

*/



#include "Node.h"
#include "BinaryTree.h"
#include "Priority_Queue.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <bitset>
#include <list>
#include <math.h>
#include <time.h>
#include "stdlib.h"

using namespace std;

class Compresser{

    char * memblock;
    string *fixedMap;
    ifstream::pos_type size;
    ifstream::pos_type sizeTo;
    unsigned long total2;
    //===================================================================
    //                   DECIMAL CONVERTOR
    /**
      this method used to convert a string of binary numbers to its
      decimal value
      Parameters:string representing the string of binary number
      Return Value:the number in decimal format
      */
    int binary(string s)
    {
        int total=0;
        for(int i=s.length()-1,j=0;i>=0;i--,j++)
        {
            if(s[i]=='1')
            {
                total+=pow(2,j);
            }
        }
        return total;
    }
    //===================================================================
    //            GETTING THE MAXIMUN ELEMENT IN THE MAP
    /**
      this mathod use to get the maximum element of the map
      Parameters:map
      Return Value:the maximum element in the map
      */
    int maxSet(map<unsigned char,int>mymap)
    {
        int max=0;
        map<unsigned char,int>::iterator it;
        for ( it=mymap.begin() ; it != mymap.end(); it++ )
        {
            if((*it).second >max)
            {
                max=(*it).second;
            }
        }
        return max;
    }
    //=====================================================================
    //                       BINARY CONVERTOR
    /**
     this method used to convert integer number to binary string according to
     number of chars
     *parameters:asci number,the number of digits that the binary return
     *return value:string represnts the binary number number in length chars
     */
    string convertToBinary(int Ascii,unsigned int chars)
    {
        string binary = "";
        while (Ascii > 0)
        {
            if ((Ascii % 2) == 0)
            {
                binary = "0" + binary;
                Ascii = Ascii / 2;
            }
            else
            {
                binary = "1" + binary;
                Ascii = Ascii / 2;
            }
        }
        while (chars - binary.length() != 0 && binary.length() <= chars)
        {
            binary = "0" + binary;
        }
        return binary;
    }
    //=========================================================================
    bool theBest(string huffMap[], map<unsigned char,int>frqMap,int cells,string s)
    {
        ifstream::pos_type fillSize;
        char*file;
        ifstream fixedFile;
        if(s.substr(s.length()-4,s.length())!=".txt"){
        fixedFile.open("Compress.TAREK",ios::in|ios::binary|ios::ate);
        }else{
         fixedFile.open("CompressTxt.TAREK",ios::in|ios::binary|ios::ate);
        }
        fixedFile.seekg (0, ios::end);
        fillSize=fixedFile.tellg();
        fixedFile.seekg (0, ios::beg);
        file = (char*)malloc(fillSize);
        fixedFile.read (file, fillSize);
        fixedFile.close();
        Priority_Queue< Node <char>* >*q=new Priority_Queue<Node <char>*>();
        cout<<(int)(unsigned char)file[0]<<endl;
        unsigned int loop=4*((int)(unsigned char)file[0]+1);
        for(unsigned int i=2;i<loop+2;i=i+4){
            char ch=file[i];
            string binNum="";
            for(int l=1;l<4;l++)
            {
                char ch2=file[i+l];
                int num=(unsigned char)ch2;
                binNum+=convertToBinary(num,8);
            }
            int n=binary(binNum);
            Node<char> *e=new Node<char>();
            e->set(ch);
            q->insert(e,n);
        }
        delete []file;
        fixedFile.clear();
        BinaryTree<char>*B=new BinaryTree<char>();
        B->build(q);
        Node<char>*x=B->getRoot();
        list< Node<char>* >myl;
        map< int,string > mymap=B->traverse(x,myl);

        fixedMap = new string[256];
        map<int,string>::iterator it1;
        for ( it1=mymap.begin() ; it1 != mymap.end(); it1++ )
        {
          fixedMap[(unsigned char)(*it1).first]=(*it1).second;
        }

        map<unsigned char,int>::iterator it0;
        unsigned long total=0;
        for ( it0=frqMap.begin() ; it0 != frqMap.end(); it0++ )
        {
            char x=(*it0).first;
            int frq=(*it0).second;
            total+=frq*mymap.find((signed char)x)->second.length();
        }
        unsigned long total2=(frqMap.size()*cells)+2;
        map<unsigned char,int>::iterator it;
        int k=0;
        for(it=frqMap.begin() ; it != frqMap.end(); it++)
        {
           total2 +=(*it).second*huffMap[k].length();
           k++;
        }
        cout<<"lenght of fixed file "<<total<<endl;
        cout<<"lenght of huff  file "<<total2<<endl;
        mymap.clear();
        return true;
    }

    //=========================================================================
    //                        BULID PRIORITY QUEUE
    /**
      repetion method used to bulidthe priority queue according to the repetion
      of every character in the the file
      *Parameters:array of chars in the file,set contain all chars without repetion,
      map used to contain a copy of repetion number of every char to help in bulding
      header file
      *Return value:the priority queue that contains the neccessary nodes to bulid
      huffman tree
      */
    Priority_Queue< Node <char>* > repetion(char blocks[],map<unsigned char,int>&freqMap)
    {
        int ASCI[256];
        for(int i=0;i<256;i++)
        {
            ASCI[i]=0;
        }
        Priority_Queue< Node <char>* >*q=new Priority_Queue< Node<char>* >();
        for (unsigned long i = 0; i<sizeTo; i++)
        {
            if(blocks[i]>=0){
                int num= blocks[i];
                ASCI[num]++;
            }else{
                 int num= blocks[i]+256;
                 ASCI[num]++;
            }
        }
        for(unsigned int i=0;i<256;i++){
            if(ASCI[i]>0){
                Node<char> *e=new Node<char>();
                if(i>127){
                e->set(i);
            }else{
              e->set((signed char)i);
            }
                freqMap[i]=ASCI[i];
                q->insert(e,ASCI[i]);
            }
        }
         return *q;
    }
    //===================================================================
    //                    BUILDING HUFFMAN TREE
    /**
      build method used to build huffman tree using priority queue.
      *Parameters:priority queue contiaing chars with repetion.
      *Return value:reference to the tree.
      */
    BinaryTree<char> build(Priority_Queue< Node <char>* > q)
    {
        BinaryTree<char> *B=new BinaryTree<char>();
        B->build(&q);
        return *B;
    }
    //====================================================================
    //               GETTING HUFFMAN CODE USING TRAVERSE
    /**
      mapping method used to gaet the huffman code from the tree during
      traversing it.
      Parameters:refernce to huffman tree
      Return Value:map containing every char and its huffman code
      */
    map<int,string>mapping(BinaryTree<char> B)
    {
        ofstream testFile;
        testFile.open("view.txt",ios::out|ios::binary|ios::ate);
        Node<char>*x=B.getRoot();
        list< Node<char>* >myl;
        map< int,string > mymap=B.traverse(x,myl);
        map<int,string>::iterator it;
        for ( it=mymap.begin() ; it != mymap.end(); it++ )
        {
            testFile<<(*it).first<<"             "<<(*it).second<<"             "<<bitset<8>((unsigned char) (*it).first)<<endl;
        }
        testFile.close();
        testFile.clear();
        return mymap;
    }
    //===================================================================
    //                   WRITTING HEADER
    /**
      writeHeader is void method used to write the header of the file
      Parameters: map that represent the frequncies of chars,the stream of file
      */
    bool writeHeader(string huffMap[], map<unsigned char,int>frqMap, ofstream &outfile,string s)
    {
        int big=maxSet(frqMap);
        int cells=0;
        if(big > 0 && big < 256)
        {
            cells++;
        }
        else if(big >= 256 && big < 65536)
        {
            cells=2;
        }
        else if(big >= 65536 && big < 16777216)
        {
            cells=3;
        }
        else if(big >= 16777216)
        {
            cells=4;
        }
        bool flag=theBest(huffMap,frqMap,cells,s);
        if(flag==true){
            outfile.put(0);
            int mapsize=frqMap.size()-1;
            outfile.put((unsigned char)mapsize);
            outfile.put(cells);
            map<unsigned char,int>::iterator it;
            for ( it=frqMap.begin() ; it != frqMap.end(); it++ )
            {
                outfile.put((unsigned char)(*it).first);
                int repet=(*it).second;
                string bin=convertToBinary(repet,cells*8);
                int x0=0,x1=8;
                for(int j=0;j<cells;j++)
                {
                    string part=bin.substr(x0,x1);
                    bitset<8>mypart(part);
                    outfile.put((unsigned char)mypart.to_ulong());
                    x0=x1;
                    x1+=8;
                }
            }
        }
        else
        {
             outfile.put(1);
        }
        return flag;
    }
    //===================================================================
    //                   WRITTING THE CONTENT OF FILE
    /**
      writeContent method is void method used to writte the content of file
      Parameters:charcter map,array containg file,output file stream
      */
    void writeContent(string huffMap[], char blocks[], ofstream &outfile,bool x)
    {
        if(x==false)
        {
            huffMap=fixedMap;
        }
        else
        {
            delete [] fixedMap;
        }
        unsigned long i = 0;
        int ch = 0;
        int count = 7;
        string bin=huffMap[(unsigned char)blocks[0]];
        while (i < sizeTo)
        {
            int temp = 0;
            unsigned int j;
            for (j = 0; j < bin.length(); j++)
            {
                if (bin[j] == '1')
                {
                    temp = 1 << count;
                     ch = temp | ch;
                }
                if (count == 0)
                    break;
                count--;
            }
            if (j == bin.length() && count == 0)
            {
                i++;
                if(i!=sizeTo)
                {
                    bin=huffMap[(unsigned char)blocks[i]];
                    if (bin[0] == '1')
                    {
                        temp = 1 << count;
                        ch = temp | ch;
                    }
                    outfile.put(ch);
                    bin = bin.substr(1);
                    count = 7;
                    ch = 0;
                }
                else
                {
                    outfile.put(8-count-1);
                    outfile.put(ch);
                    break;
                }
            }
            else if (j == bin.length())
            {
                i++;
                if (i == sizeTo)
                {
                    outfile.put(8-count-1);
                    outfile.put(ch);
                    break;
                }
                bin=huffMap[(unsigned char)blocks[i]];
            } else if (count == 0)
            {
                outfile.put(ch);
                bin = bin.substr(j + 1);
                count = 7;
                ch = 0;
            }
        }
    }

    //===================================================================
    //                   WRIITING TO FILE
    /**
      writting method used to write the compressed file during two steps:
      1. write the header of file
      2. write the content of file
      Prameters:charcter map,array containg file,frequency of charcter map
      */
    void writting(map<int,string>mymap,char blocks[],map<unsigned char,int>frqMap,string s)
    {
        ofstream outfile;
        s+=".TRK";
        char*file;
        file=new char[s.size()];
        strcpy(file,s.c_str());
        outfile.open(file,ios::out|ios::binary|ios::ate);
        string *huffMap;
        huffMap = new string[256];
        map<int,string>::iterator it;
        for ( it=mymap.begin() ; it != mymap.end(); it++ )
        {
          huffMap[(unsigned char)(*it).first]=(*it).second;
        }
        bool x=writeHeader(huffMap,frqMap,outfile,s);
        writeContent(huffMap,blocks,outfile,x);
        outfile.close();
    }
    //===================================================================
    //                 READING THE FILE
    /**
      reading method used to read the content of the file and store it in char array
      and return the chars of the array in set without repetion
      Parameters:void
      Return value:set conating all chars without repetion
      */
    void reading(string s)
    {
        char*file;
        file=new char[s.size()];
        strcpy(file,s.c_str());
        ifstream infile;
        infile.open (file,ios::in|ios::binary|ios::ate);
        infile.seekg (0, ios::end);
        size=infile.tellg();
        infile.seekg (0, ios::beg);
        sizeTo=size;
        memblock = (char*)malloc(size);
        infile.seekg (0, ios::beg);
        infile.read (memblock, size);
        infile.close();
    }
    //======================================================================
    //                      COMPRESSING THE FILE
    /**
      mainApp is the main method in the compresser
      it preform the operation as following:
      1. read the file in the array and return set containg all chars wihtout repetion
      2. make the priority queue
      3. build huffman tree
      4. writte the compressing code in the file
      */
public:
    void main_App(string s)
    {
        cout<<"BEGIN COMPRESSING"<<endl;
        time_t t1 = time(NULL);
        map<unsigned char,int>freqMap;
        reading(s);
        time_t t2 = time(NULL);
        cout<<"reading operation takes "<<t2-t1<<" seconds"<<endl;
        if(sizeTo>0){
            Priority_Queue< Node <char>* >q=repetion(memblock,freqMap);
            BinaryTree<char> B=build(q);
            map<int,string> mymap=mapping(B);
            time_t t3 = time(NULL);
            cout<<"building tree takes "<<t3-t2<<" seconds"<<endl;
            cout<<"================================"<<endl;
            writting(mymap,memblock,freqMap,s);
            time_t t4 = time(NULL);
            s=s+".TRK";
            char*file;
            file=new char[s.size()];
            strcpy(file,s.c_str());
            ifstream infile;
            infile.open (file,ios::in|ios::binary|ios::ate);
            infile.seekg (0, ios::end);
            total2=infile.tellg();
            double compressR=(((double)sizeTo-(double)total2)/(double)sizeTo)*100.0;
            cout<<"Compression ratio = "<<compressR<<endl;
            cout<<"writting to file takes "<<t4-t3<<" seconds"<<endl;
            cout<<"================================"<<endl;
            cout<<"total process take "<<t4-t1<<" seconds"<<endl;
            delete [] memblock;
        }
        cout<<"DONE COMPRESSING"<<endl;
        cout<<"================================"<<endl;
    }
};


