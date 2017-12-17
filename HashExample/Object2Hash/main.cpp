//任意のオブジェクトをハッシュ化する。
//http://ja.cppreference.com/w/cpp/utility/hash

#include <iostream>
#include <functional>
#include <string>

#include <unordered_map>

struct S {
    std::string first_name;
    std::string last_name;
};

template<class T> class MyHash;

template<>
class MyHash<S> {
public:
    size_t operator()(const S &s) const
    {
        size_t h1 = std::hash<std::string>()(s.first_name);
        size_t h2 = std::hash<std::string>()(s.last_name);
        return h1 ^ (h2 << 1);
    }
    
    static float* create() {
        return NULL;
    }
};

struct Test{
    Test(){};
};

template<class T> class TestHash;


//template<>
//class TestHash<Test>{
//public:
//    size_t operator()(const Test &s) const
//    {
//        
//        size_t h1 = std::hash<Test>()();
//        size_t h2 = std::hash<std::string>()(s.last_name);
//        return h1 ^ (h2 << 1);
//    }
//};

int main()
{
    std::string s1 = "Hubert";
    std::string s2 = "Farnsworth";
    std::hash<std::string> h1;
    

    
    S n1;
    n1.first_name = s1;
    n1.last_name =  s2;
    
    std::cout << "hash(s1) = " << h1(s1) << "\n"
    << "hash(s2) = " << std::hash<std::string>()(s2) << "\n"
    << "hash(n1) = " << MyHash<S>()(n1) << "\n";
    
    int x=1;
    std::cout<<std::hash<int*>()(&x) ;
    
    Test test;
    //std::hash<Test>()(test);
    
    std::unordered_map<std::string, Test> ump_test;
    
    
}