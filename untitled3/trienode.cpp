#include"trienode.h"
//插入
trieNode* trieNode::insert(char letter)
{
    trieNode* node = new trieNode;
    node->letter=letter;
    int num = letterToNum(letter);
    if(num!=-1){
        child[num]=node;
        return node;
    }
    return nullptr;
}
//查找
trieNode *trieNode::find(char letter)
{
    int num=letterToNum(letter);
    if(num!=-1){
        return child[num];
    }
    return nullptr;
}
//字母对数字转换
int trieNode::letterToNum(char letter)
{
    if(letter>='A'&&letter<='Z'){
        return (int)letter-65;
    }else if(letter>='a'&&letter<='z'){
        return (int)letter-97;
    }else if(letter=='-'){
        return 26;
    }
    return -1;
}
//数字对字母转换
char trieNode::numToLetter(int i)
{
    if(i>=0&&i<=25){
        return 'a'+i;
    }else if(i==26){
        return '-';
    }
    return -1;
}
