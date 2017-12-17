//http://www7b.biglobe.ne.jp/~robe/cpphtml/html03/cpp03035.html

// BinTree1.cpp
#include <iostream>
#include <iomanip>
#include <string>
//#include <malloc.h>

using namespace std;

// 入力バッファの最大サイズ
const int BUFSIZE = 1024;

// ノード
struct SNode
{
    char* id;
    int   num;
    
    SNode* pChild[2];
};

// 値の入力
bool InputValue(SNode*& pRoot);
// 値を探す
bool FindValue(SNode* pRoot);

// 二分探索木の操作

// ノードの初期化
bool InitNode(SNode* pNode, const char* id, int num);
// ノードの追加（再帰）
bool AddNode(SNode*& pRoot, const char* id, int num);
// ノードを探す（再帰）
SNode*& FindNode(SNode*& pRoot, const char* id);

// 木を表示する
void DispTree(SNode* pRoot);
// 木を表示する（再帰サブルーチン）
void Rec_DispTree(SNode* pRoot, int nDepth);

// 木を解放（再帰）
void FreeTree(SNode* pRoot);
// ノードを解放
void FreeNode(SNode* pNode);



// 値の入力
bool InputValue(SNode*& pRoot)
{
    char id[BUFSIZE];
    int  num;
    
    cout << "文字列と値を入力して下さい > " << flush;
    cin >> id >> num;
    if(strcmp(id, "q") == 0 || num == -1)
        return false;
    
    return AddNode(pRoot, id, num);
}

// 値を探す
bool FindValue(SNode* pRoot)
{
    char id[BUFSIZE];
    cout << "ＩＤ文字列を入力して下さい > " << flush;
    cin >> id;
    if(strcmp(id, "q") == 0)
        return false;
    
    SNode*& pFind = FindNode(pRoot, id);
    if(pFind == NULL)
        cout << "見つかりません。" << endl;
    else
        cout << "値は " << pFind->num << " です。" << endl;
    
    return true;
}

// 二分探索木の操作

// ノードの初期化
bool InitNode(SNode* pNode, const char* id, int num)
{
    // strdup は文字列を複製する関数です
    // このとき、メモリを確保します
    // このメモリの解放は free という関数で行います
    pNode->id  = strdup(id);
    if(pNode->id == NULL)
        return false;
    
    pNode->num = num;
    for(int i = 0; i < 2; i++)
        pNode->pChild[i] = NULL;
    return true;
}

// ノードの追加（再帰）
bool AddNode(SNode*& pRoot, const char* id, int num)
{
    SNode*& pAdd = FindNode(pRoot, id);  // 追加位置を探します
    
    // 既にノードがある場合は上書きします
    if(pAdd != NULL)
    {
        pAdd->num = num;
        return true;
    }
    
    // ノードを確保します
    pAdd = new SNode;
    if(pAdd == NULL)
        return false;
    
    // ノードを初期化します
    if(!InitNode(pAdd, id, num))
    {
        // 失敗したら解放します
        FreeNode(pAdd);
        pAdd = NULL;
        return false;
    }
    
    return true;
}

// ノードを探す（再帰）
SNode*& FindNode(SNode*& pRoot, const char* id)
{
    // 見つからなかったらそのまま返す
    if(pRoot == NULL)
        return pRoot;
    
    // 比較
    //pRoot->id > id なら 正の値、pRoot->id < idなら負の値、同じなら0を返す。
    int fComp = strcmp(pRoot->id, id);
    
    // 見つかったらそのノードを返す
    if(fComp == 0)
        return pRoot;
    
    // 次のノードに進む
    //子のどちらかのノードにしか進まない。
    return FindNode(pRoot->pChild[fComp < 0], id);
}

// 木を表示する
void DispTree(SNode* pRoot)
{
    Rec_DispTree(pRoot, 0);
}

// 木を表示する（再帰サブルーチン）
void Rec_DispTree(SNode* pRoot, int nDepth)
{
    if(pRoot == NULL)
        return;
    
    Rec_DispTree(pRoot->pChild[0], nDepth + 1);
    
    cout << setw(nDepth * 2) << "" << pRoot->id
    << " : " << pRoot-> num << endl;
    
    Rec_DispTree(pRoot->pChild[1], nDepth + 1);
}

// 木を解放（再帰）
void FreeTree(SNode* pRoot)
{
    if(pRoot == NULL)
        return;
    
    // 子ノードを解放してから
    for(int i = 0; i < 2; i++)
        FreeTree(pRoot->pChild[i]);
    // 自分を解放する
    FreeNode(pRoot);
}

// ノードを解放
void FreeNode(SNode* pNode)
{
    // strdup で確保した領域は free で解放します
    // free は malloc という関数で確保したメモリを解放するための関数です
    // Ｃ言語には new はなく、malloc 関数を使ってメモリを確保します
    // strdup はＣ言語の時代の関数なので、内部で malloc を使っています
    free(pNode->id);
    
    // free と delete が混在するのは
    // ちょっと気持ちが悪いですね（汗）
    delete pNode;
}


int main()
{
    SNode* pRoot = NULL;
    
    while(InputValue(pRoot));
    while(FindValue(pRoot));
    DispTree(pRoot);
    FreeTree(pRoot);
    
    return 0;
}