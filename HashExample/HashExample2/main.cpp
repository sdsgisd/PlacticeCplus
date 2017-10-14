//http://www7b.biglobe.ne.jp/~robe/cpphtml/html03/cp030361.html

// 上のHash2.cppをmain.cppにした。
#include <iostream>
#include <string.h>
#include "Hash1.h"

// 基本操作
static bool AddData(SHash& hash);   // データの追加
static bool FindData(SHash& hash);  // データの検索

using namespace std;

int main()
{
    SHash hash;
    
    InitHash(hash);
    while(AddData(hash));
    while(FindData(hash));
    HashDisp(hash);
    
    return 0;
}

static bool AddData(SHash& hash)
{
    char key[1024];
    int  value;
    
    cout << "文字列と値を入力して下さい > " << flush;
    cin >> key >> value;
    
    if(strcmp(key, "q") == 0 || value == HASH_UNUSED)
        return false;
    
    return HashAdd(hash, key, value);
}

static bool FindData(SHash& hash)
{
    char key[1024];
    
    cout << "検索する文字列を入力して下さい > " << flush;
    cin >> key;
    
    if(strcmp(key, "q") == 0)
        return false;
    
    int value = HashFind(hash, key);
    if(value == HASH_UNUSED)
        cout << "見つかりません" << endl;
    else
        cout << "値は " << value << " です。" << endl;
    return true;
}