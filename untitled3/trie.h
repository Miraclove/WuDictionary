#ifndef TRIE_H
#define TRIE_H


#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
#include"trienode.h"

//字典树
class Trie
{
public:
    Trie() { root = new trieNode(); }
    //树中插入单词
    void insertString(const string& str);
    //对树前序遍历得到开头元素相同集合
    vector<string> getPreString(const string& str);
private:
    //辅助函数
    //得到后续所有单词
    void addString(trieNode* preNode, string str, vector<string>& ret);
    //找到单词尾节点
    trieNode* searchPreString(const string& str);
//树根节点
    trieNode* root;
};

#endif // TRIE_H
