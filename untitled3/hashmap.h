#ifndef HASHMAP_H
#define HASHMAP_H
#include<iostream>
#include<QString>
#include<QDebug>
#include<vector>
#include<map>
using namespace std;

//哈希表节点
template<class Key, class Value>
class HashNode
{
public:
    Key    _key;
    Value  _value;
    HashNode *next;

    HashNode(Key key, Value value)
    {
        _key = key;
        _value = value;
        next = NULL;
    }
    ~HashNode()
    {

    }
    HashNode& operator=(const HashNode& node)
    {
        _key = node.key;
        _value = node.key;
        next = node.next;
        return *this;
    }
};
//哈希表
template <class Key, class Value>
class HashMap
{
public:
    HashMap();
    ~HashMap();
    //插入操作
    bool insert(const Key& key, const Value& value);
    //删除操作
    bool del(const Key& key);
    //得到Key集合
    vector<Key> getKeySet();
    //哈希表到数组转换
    map<Key,Value> toMap();
    //查找操作
    Value& find(const Key& key);
    //哈希表[]重载
    Value& operator [](const Key& key);
    //哈希表内含元素个数
    int size;
private:
    //取得哈希值
    int hash(const string & key);
    bool equal(const string & A, const string & B);
    //哈希表头
    HashNode<Key, Value> **table;
    //哈希表头个数
    unsigned int _size;
    Value ValueNULL;
    vector<Key> keys;
};

template <class Key, class Value>
HashMap<Key, Value>::HashMap()
{
    //默认表头数量为10000个
    _size=10000;
    //申请空间
    table = new HashNode<Key, Value>*[_size];
    //每个表头初始化为空
    for (unsigned i = 0; i < _size; i++)
        table[i] = NULL;
    //表大小初始化为0
    size = 0;
}
template <class Key, class Value>
HashMap<Key, Value>::~HashMap()
{
    for (unsigned i = 0; i < _size; i++)
    {
        HashNode<Key, Value> *currentNode = table[i];
        while (currentNode)
        {
            HashNode<Key, Value> *temp = currentNode;
            currentNode = currentNode->next;
            delete temp;
        }
    }
    delete table;
}

//哈希表插入操作
template <class Key, class Value>
bool HashMap<Key, Value>::insert(const Key& key, const Value& value)
{
    //根据取得的哈希值放入表内
    int index = hash(key)%_size;
    HashNode<Key, Value> * node = new HashNode<Key, Value>(key,value);
    node->next = table[index];
    table[index] = node;
    keys.push_back(key);
    size++;
    return true;
}

//删除操作（链表删除）
template <class Key, class Value>
bool HashMap<Key, Value>::del(const Key& key)
{
    unsigned index = hash(key) % _size;
    HashNode<Key, Value> * node = table[index];
    HashNode<Key, Value> * prev = NULL;
    while (node)
    {
        if (node->_key == key)
        {
            if (prev == NULL)
            {
                table[index] = node->next;
            }
            else
            {
                prev->next = node->next;
            }
            delete node;
            size--;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

template<class Key, class Value>
vector<Key> HashMap<Key,Value>::getKeySet()
{
    return keys;
}
//哈希表与图的转换
template<class Key, class Value>
map<Key, Value> HashMap<Key,Value>::toMap()
{
    map<Key,Value> map;
    for (int i = 0;i<keys.size();i++) {
        map.insert(pair<Key,Value>(keys.at(i),this->find(keys.at(i))));
    }
    return map;
}


//哈希表查找操作（链表查找）
template <class Key, class Value>
Value& HashMap<Key, Value>::find(const Key& key)
{
    //获得哈希值
    int  index = hash(key) % _size;
    if (table[index] == NULL)
        return ValueNULL;
    else
    {
        HashNode<Key, Value> * node = table[index];
        while (node)
        {
            if (node->_key == key)
                return node->_value;
            node = node->next;
        }
    }
    return ValueNULL;
}

//重构[]运算符
template <class Key, class Value>
Value& HashMap<Key, Value>::operator [](const Key& key)
{
    return find(key);
}
//取得哈希值(移位的标准旋转Hash）
template<class Key, class Value>
int HashMap<Key,Value>::hash(const string &key)
{
    int hash = 0;
    for(int i = 0, hash = key.length(); i < key.length(); ++i)
    {
        hash = (hash<<4)^(hash>>28)^key[i];
    }
    //去除hash的符号（保证为正整数）
    return (hash & 0x7FFFFFFF);
}

template<class Key, class Value>
bool HashMap<Key,Value>::equal(const string &A, const string &B)
{
    if (A.compare(B) == 0)
        return true;
    else
        return false;
}
#endif // HASHMAP_H
