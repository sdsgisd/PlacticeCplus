// Hash1.h
#ifndef __HASH1_H__INCLUDED__
#define __HASH1_H__INCLUDED__

// ハッシュ表のサイズ（素数）
const unsigned HASH_SIZE  = 11;
// ハッシュに登録しない値
const int HASH_UNUSED  = -1;

// 二分探索木のノード
struct SNode
{
    const char* key;
    int value;
    SNode* pNext[2];
};

// ハッシュ
struct SHash
{
    SNode* pNode[HASH_SIZE];
};

void InitHash(SHash& hash);  // 初期化

int HashFind(SHash& hash, const char* key);  // データを検索
bool HashAdd(SHash& hash, const char* key, int value);  // データを追加

void HashFree(SHash& hash);  // 全削除

void HashDisp(SHash& hash);  // データ全体を表示

#endif // #ifndef __HASH1_H__INCLUDED__