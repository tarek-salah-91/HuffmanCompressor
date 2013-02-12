/**
 *	Author : Tarek Salah
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

using namespace std;

class DeCompresser{

    ifstream::pos_type size;
    ifstream::pos_type sizeTo;
    char * fileBuffer;

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
    BinaryTree<char>* readFixedCode(string s)
    {
        ifstream::pos_type fillSize;
        char*file;
        ifstream fixedFile;
        if(s.substr(s.length()-4,s.length())!=".txt"){
        fixedFile.open("Compress.TAREK",ios::in|ios::binary|ios::ate);
        }
        else
        {
        fixedFile.open("CompressTxt.TAREK",ios::in|ios::binary|ios::ate);
        }
        fixedFile.seekg (0, ios::end);
        fillSize=fixedFile.tellg();
        fixedFile.seekg (0, ios::beg);
        file = new char [fillSize];
        fixedFile.read (file, fillSize);
        fixedFile.close();
        Priority_Queue< Node <char>* >*q=new Priority_Queue<Node <char>*>();
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
        BinaryTree<char>*B=new BinaryTree<char>();
        B->build(q);
        return B;
    }

    //=========================================================================
    /**
      read header used to read the header of the file on the form
      1. the first char represents the number of characters in file
      2. the second char represents the number that every frequency take
      3. read until first*second char
      then build huffman tree using the frquencies
      Parameters:
      -----------
      1. array containg the chars of file
      2. dummy integer represnts the index that the loop stopped on

      return value
      -------------
      pointer to the root of the tree
      */
    BinaryTree<char>* readHeader(char file[],int &index)
    {
        BinaryTree<char>*B=new BinaryTree<char>();
        if(file[0]==0){
        Priority_Queue< Node <char>* >*q=new Priority_Queue<Node <char>*>();
        int charNum=(unsigned char)file[1]+1;
        int charCell=(unsigned char)file[2]+1;
        int loop=charNum*charCell;
        for(int k=3;k<loop+3;k=k+charCell)
        {
            char ch=file[k];
            string binNum="";
            for(int l=1;l<charCell;l++)
            {
                char ch2=file[k+l];
                int num=(unsigned char)ch2;
                binNum+=convertToBinary(num,8);
            }
            int n=binary(binNum);
            Node<char> *e=new Node<char>();
            e->set(ch);
            q->insert(e,n);
        }
        B->build(q);
        index=loop+1;
        }else{
            index=2;
        }
        return B;
    }
    //=========================================================================
    /**
      writting used to read the compressed file and write it in the decompressed file
      first it translate the file using the tree as following:
      it traverse every bit====>if it is 0 go left
                                else go right
                                untill reaching leaf node
      then read the last two chars.....the char[size-2] represnt the number of bits that programm
      will take it in the char[size-1]
      */
    void writting(int index,char file[],Node<char>*root,BinaryTree<char>* huffmanTree,string str)
    {
        str=str.substr(0,str.length()-4);
        char*fileName;
        fileName=new char[str.size()];
        strcpy(fileName,str.c_str());
        ofstream outfile (fileName,ios::out|ios::binary|ios::ate);
        for(int i=index+2;i<size-2;i++)
        {
           int chNum =(unsigned char) file[i];
           int count=7;
           while(count>=0)
           {
               int x = chNum & (1 << count);
               if(x>>count == 0)
               {
                   root=root->getLeftChild();
                   if(huffmanTree->isLeaf(root))
                   {
                       outfile.put(root->get());
                       root=huffmanTree->getRoot();
                   }
               }
               else
               {
                   root=root->getRightChild();
                   if(huffmanTree->isLeaf(root))
                   {
                       outfile.put(root->get());
                       root=huffmanTree->getRoot();
                   }
               }
               count--;
           }
        }
        int count =(unsigned char) file[sizeTo-2];
        int lastCh =(unsigned char) file[sizeTo-1];
        string s=convertToBinary(lastCh,8);
        for(int j=0;j<count;j++)
        {
            if(s[j]=='0')
            {
                root=root->getLeftChild();
                if(huffmanTree->isLeaf(root))
                {
                    outfile.put(root->get());
                    root=huffmanTree->getRoot();
                }
            }
            else
            {
                root=root->getRightChild();
                if(huffmanTree->isLeaf(root))
                {
                    outfile.put(root->get());
                    root=huffmanTree->getRoot();
                }
            }
        }
    }

    //=========================================================================
    /**
      the main method in the decompress program that call functions on the following way
      1. read compressed file
      2. build the tree
      3. translate the file using huffman tree
      4. write it in new file
      */
public:
    void main_App( string s)
    {
        if(s.substr(s.length()-4,s.length())==".TRK")
        {
        char*file;
        file=new char[s.size()];
        strcpy(file,s.c_str());
        cout<<"BIGEN DECOMPRESSING"<<endl;
        time_t t1 = time(NULL);
        ifstream infile (file, ios::in|ios::binary|ios::ate);
        if (infile.is_open())
        {
            infile.seekg (0, ios::end);
            size = infile.tellg();
            sizeTo=size;
            fileBuffer = new char [size];
            infile.seekg (0, ios::beg);
            infile.read (fileBuffer, size);
            infile.close();
        }
        time_t t2 = time(NULL);
        cout<<"reading operation takes "<<t2-t1<<" seconds"<<endl;
        if(sizeTo>0){
            int point=0;
            Node<char>*root;
            BinaryTree<char>* huffmanTree=readHeader(fileBuffer,point);
            if(point!=2){
                root=huffmanTree->getRoot();
            }else{
                huffmanTree=readFixedCode(s);
                root=huffmanTree->getRoot();
            }
            time_t t3 = time(NULL);
            cout<<"building tree takes "<<t3-t2<<" seconds"<<endl;
            cout<<"================================"<<endl;
            writting(point,fileBuffer,root,huffmanTree,s);
            time_t t4 = time(NULL);
            cout<<"writting operation takes "<<t4-t3<<" seconds"<<endl;
            cout<<"================================"<<endl;
            cout<<"total operation takes "<<t4-t1<<" seconds"<<endl;
        }
        cout<<"DONE DECOMPRESSING"<<endl;
        cout<<"================================"<<endl;
        }else{
            cout<<"It is not valid file";
        }
    }
    //=========================================================================

};

