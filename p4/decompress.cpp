#include "binaryTree.h"
#include "huffmanTree.h"
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

bool detect_0(char detected){
    if(detected=='0'){
        return true;
    }
    return false;
}

bool detect_1(char detected){
    if(detected=='1'){
        return true;
    }
    return false;
}
int main(int argc, char *argv[]) {
    if(argc!=3){
        return 0;}
    string filename(argv[1]);
    HuffmanTree tree(filename);
    ifstream ifile;
    ifile.open(argv[2]);
    if(!ifile){
        return 0;}
    string temp;
    while(ifile>>temp){
        Node*p=tree.root;
        for(int i=0;i<temp.length();i++){
            if(detect_0(temp[i])){
                p=p->leftSubtree();
            }
            if(detect_1(temp[i])){
                p=p->rightSubtree();
            }
            cout<<p->getstr();
        }
    }
   return 0;
}
