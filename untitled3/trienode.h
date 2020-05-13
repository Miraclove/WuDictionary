#ifndef TRIENODE_H
#define TRIENODE_H
#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
//字典树节点
class trieNode
{
public:
    trieNode() :count(0) {
        for (int i = 0;i<=26;i++) {
            child[i]=nullptr;
        }
    }
    //以当前节点结尾的字符串的个数
    int count;
    char letter;
    trieNode* child[27];
    trieNode* insert(char letter);
    trieNode* find(char letter);
    int letterToNum(char letter);
    char numToLetter(int i);
    //map<char, trieNode*> child;
};
#endif // TRIENODE_H
