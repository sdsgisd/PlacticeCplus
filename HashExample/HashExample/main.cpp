//https://ameblo.jp/nana-2007-july/entry-10091225141.html

#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <vector>


using namespace std;

double Add(double a, double b){ return a + b; }
double Sub(double a, double b){ return a - b; }
double Mul(double a, double b){ return a * b; }
double Div(double a, double b){ return a / b; }

double (*  afpOps[])(double, double) = {
    Add, Sub, Mul, Div,
};




const unsigned int hashElementNum = 51;

/**
 stringハッシュ関数。他の型についても作成してみましょう。
 また、同じstringに関するものでも、キー文字列の傾向が分かっているなら、
 いろいろ試してみると面白いと思います。
 階乗、累乗を使ってみるとか。
 */
const unsigned int sampleHashFunc(const string& str)
{
    unsigned int h = 0;
    string::const_iterator i = str.begin();
    
    for (; i != str.end(); ++i) {
        h += h * 137 + *i;
    }
    
    return h % hashElementNum;
};


/**
 連想配列クラス。
 */
template <typename TKey, typename TValue>
class Hash{
public:
    //型宣言
    typedef const unsigned int (*HashFunc) (const TKey&);//関数ポインター
    //using HashFunc= std::function<const unsigned int (const TKey&)>;
    
    
    typedef pair<const TKey, TValue> Pair;
protected:
    //クラス内用の型宣言
    using List=list<Pair>;
    typedef typename List::iterator Iterator;
    typedef vector<List> Vector;
    
    ///Vector要素の１つのListの検索結果と終了をセットにした構造体
    struct BeginEnd{
        //Vectorの要素位置(下のtypenameはsize_typeが型であることをコンパイラに示します)
        typename Vector::size_type hval;
        //検索結果
        Iterator found;
        //Listの終了
        Iterator end;
    };
    
public:
    ///コンストラクタ
    //Hash(HashFunc func = &sampleHashFuc)
    Hash(HashFunc func )
    : m_vec(hashElementNum), m_func(func)
    {};
    
    ///値の取り出し
    TValue& operator [](const TKey& key){
        BeginEnd result = _find(key);
        Iterator i = result.found;
        
        //キーが見つかったとき
        if(i != result.end) return i->second;
        
        //キーが見つからないとき、新規追加する
        i = addPair(key);
        return i->second;
    };
    
    ///キーの削除
    void remove(const TKey& key){
        BeginEnd result = _find(key);
        Iterator i = result.found;
        if(i == result.end) return;
        //vectorのどこの要素に入っているかを取得
        m_vec[result.hval].erase(i);
    };
    
    ///検索
    Pair* find(const TKey& key){
        BeginEnd result = _find(key);
        if(result.found != result.end){
            return &*result.found;
        }else{
            return NULL;
        }
    };
    
    
protected:
    ///マッピング値の検索
    BeginEnd _find(const TKey& key){
        
        //vectorのどこの要素に入っているかを取得
        const unsigned int hval = m_func(key);
        
        //要素の中を1つずつ検索していきます
        Iterator i;
        Iterator begin = m_vec[hval].begin();
        Iterator end = m_vec[hval].end();
        for(i=begin; i!=end; ++i){
            if(i->first == key) break;
        }
        
        //結果の返却
        BeginEnd k = {hval, i, end};
        return k;
    };
    
    ///新規にキーと値のセットを追加します
    Iterator addPair(const TKey& key)
    {
        const unsigned int hval = m_func(key);
        m_vec[hval].push_front(Pair(key, TValue()));
        return m_vec[hval].begin();
    };
    
private:
    Vector m_vec;
    HashFunc m_func;
};


int main(int argc, char *argv[])
{
    Hash<string, string> ss_hash(&sampleHashFunc);
    
    ss_hash["abc"] = "ABC";
    ss_hash["bcd"] = "BCD";
    cout << ss_hash["abc"] << ":" << ss_hash["bcd"] << ":" << ss_hash["kkk"] << endl;
    
    
    //削除してみます
    ss_hash.remove("bcd");
    cout << ss_hash["abc"] << ":" << ss_hash["bcd"] << ":" << ss_hash["kkk"] << endl;
    
    system("PAUSE");
    
    
    class TestKeyClass{
    public:
        string str;
        bool operator==(const TestKeyClass &tk)const{ return str==tk.str;}
        TestKeyClass(const string& str):str(str){};
        
    };
    class TestValueClass{
    public:
        string str;
        bool operator==(const TestValueClass &tv)const{ return str==tv.str;}
        TestValueClass(const string& str=""):str(str){};

    };
    
    auto TestHashFunc=[](const TestKeyClass& tk)->const unsigned int
    {
        std::string str=tk.str;
        unsigned int h = 0;
        string::const_iterator i = str.begin();
        
        for (; i != str.end(); ++i) {
            h += h * 137 + *i;
        }
        
        return h % hashElementNum;
    };
    
    Hash<TestKeyClass, TestValueClass> test_hash(TestHashFunc);
    test_hash[TestKeyClass("tk1")]=TestValueClass("tv1");
    test_hash[TestKeyClass("tk2")]=TestValueClass("tv2");
    
    
    cout << test_hash[TestKeyClass("tk1")].str<<":" << test_hash[TestKeyClass("tk2")].str << ":" << test_hash[TestKeyClass("tk3")].str<< endl; ;
    
    //削除してみます
    test_hash.remove(TestKeyClass("tk2"));
    cout << test_hash[TestKeyClass("tk1")].str<<":" << test_hash[TestKeyClass("tk2")].str << ":" << test_hash[TestKeyClass("tk3")].str<< endl; ;//
    system("PAUSE");
//
    return EXIT_SUCCESS;
}