// Hash1.cpp
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Hash1.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// static 関数のプロトタイプ宣言

// ハッシュ法のルーチン
// ハッシュ関数
static int HashFunc(const char* key);
// データを検索（ノードを返す）
static SNode*& HashFindNode(SHash& hash, const char* key);

// 二分探索木操作関数
// 初期化
static bool InitNode(SNode* pNode, const char* key, int value);
// ノードを探す
static SNode*& TreeFindNode(SNode*& pNode, const char* key);
// 全削除
static void TreeFree(SNode*& pNode);
// 二分探索木全体の表示
static int TreeDisp(SNode* pNode, int nDepth);


////////////////////////////////////////////////////////////////////////////////
// ハッシュ法のルーチン

// 初期化
void InitHash(SHash& hash)
{
    for(int i = 0; i < HASH_SIZE; i++)
        hash.pNode[i] = NULL;
}

// ハッシュ関数
// 先頭と最後と中央の文字コードの合計を HASH_SIZE で割った余りを返します
static int HashFunc(const char* key)
{
    int nLen = strlen(key);
    
    if(nLen == 0)
        return 0;
    nLen--;
    return ((unsigned)key[0] + key[nLen / 2] + key[nLen]) % HASH_SIZE;
}

// データを検索（ノードを返す）
static SNode*& HashFindNode(SHash& hash, const char* key)
{
    return TreeFindNode(hash.pNode[HashFunc(key)], key);
}

// データを検索
int HashFind(SHash& hash, const char* key)
{
    SNode* pNode = HashFindNode(hash, key);
    return pNode == NULL ? HASH_UNUSED : pNode->value;
}

// データを追加
bool HashAdd(SHash& hash, const char* key, int value)
{
    SNode*& pNode = HashFindNode(hash, key);
    if(pNode != NULL)
        pNode->value = value;
    else
    {
        pNode = new SNode;
        if(pNode == NULL)
            return false;
        if(!InitNode(pNode, key, value))
        {
            delete pNode;
            pNode = NULL;
            return false;
        }
    }
    return true;
}

// 全削除
void HashFree(SHash& hash)
{
    for(int i = 0; i < HASH_SIZE; i++)
    {
        TreeFree(hash.pNode[i]);
        hash.pNode[i] = NULL;
    }
}

// データ全体を表示
void HashDisp(SHash& hash)
{
    int nData = 0;  // データの総数
    
    for(int i = 0; i < HASH_SIZE; i++)
    {
        cout << "ハッシュ値 " << i << endl;
        int nDataNode = TreeDisp(hash.pNode[i], 0);
        cout << "データ数 " << nDataNode << endl;
        nData += nDataNode;
        
        char letter;
        cin >> letter;
    }
    cout << "総データ数 " << nData << endl;
}

////////////////////////////////////////////////////////////////////////////////
// 二分探索木操作関数

// 初期化
static bool InitNode(SNode* pNode, const char* key, int value)
{
    pNode->key = strdup(key);
    if(key == NULL)
        return false;
    pNode->value = value;
    pNode->pNext[0] = NULL;
    pNode->pNext[1] = NULL;
    return true;
}

// ノードを探す
static SNode*& TreeFindNode(SNode*& pNode, const char* key)
{
    if(pNode == NULL)
        return pNode;
    
    int fComp = strcmp(pNode->key, key);
    if(fComp == 0)
        return pNode;
    
    return TreeFindNode(pNode->pNext[fComp < 0], key);
}

// 全削除
static void TreeFree(SNode*& pNode)
{
    if(pNode == NULL)
        return;
    
    TreeFree(pNode->pNext[0]);
    TreeFree(pNode->pNext[1]);
    delete pNode;
    pNode = NULL;
}

// 二分探索木全体の表示
static int TreeDisp(SNode* pNode, int nDepth)
{
    if(pNode == NULL)
        return 0;
    
    int nData = 1;
    nData += TreeDisp(pNode->pNext[0], nDepth + 1);
    cout << setw(nDepth * 2) << "" << pNode->key << " : " << pNode->value << endl;
    nData += TreeDisp(pNode->pNext[1], nDepth + 1);
    
    return nData;
}