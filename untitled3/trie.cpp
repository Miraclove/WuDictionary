#include "trie.h"

//插入字符串，构建字典树
void Trie::insertString(const string& str)
{
    //输入字符为空直接返回
    if (!root || str.empty())
        return;
    //开始从根节点向下查找
    trieNode* currentNode = root;
    for (auto& chr : str)
    {
        trieNode* Iter = currentNode->find(chr);
        if (Iter == nullptr)
        {
            //如果当前字符不在字典树中，新建一个节点插入
            currentNode = currentNode->insert(chr);
        }
        else
        {
            //如果当前字符在字典书中，则将当前节点指向它的孩子
            currentNode = currentNode->find(chr);
        }
    }
    currentNode->count++;
}
//查找以str为前缀的节点
trieNode* Trie::searchPreString(const string& str)
{
   //如果输入str为空直接返回
    if (!root || str.empty())
        return nullptr;
    //从根节点开始向下查找
    trieNode* currentNode = root;
    for (auto& chr : str)
    {
        trieNode* Iter = currentNode->find(chr);
        if (Iter != nullptr)
        {
            currentNode = Iter;
        }
        else
            return nullptr;
    }

    return currentNode;
}
//查找以str为前缀的所有字符串，保存在vector中返回
vector<string> Trie::getPreString(const string& str)
{
    vector<string> ret;
    //查找以str开头的节点
    trieNode* pre = searchPreString(str);
    if (pre)
    {
        addString(pre, str, ret);
    }
    return ret;
}
//将preNode的所有子节点中字符串加入str前缀，然后插入到vector中
void Trie::addString(trieNode* preNode, string str, vector<string>& ret)
{
    //对每个元素的每一个字母查找
    for (int i = 0;i<26;i++) {
        if(preNode->child[i]!=nullptr){
            addString(preNode->child[i],str+preNode->child[i]->letter,ret);
        }
    }
    //将找到的元素放在数组末尾
    if (preNode->count != 0)
        ret.push_back(str);
}
