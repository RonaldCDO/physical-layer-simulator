#include <iostream>
#include "camadaFisica.hpp"

int main(){

    std::string test = "TR1";
    std::vector<std::bitset<4> > myVector;
    // std::vector<std::bitset<8> >::iterator it;

    std::cout << test <<std::endl;
    for(std::bitset<4> i : test)
    myVector.emplace_back(i);
    
    for (auto const &bits : myVector)
    std::cout <<bits <<std::endl;

    std::cout << myVector.size() <<std::endl;

    
   
    // it = myVector.begin();

    // for (it = myVector.begin(); it < myVector.end(); it++)
    // std::cout <<' ' << *it << std::endl;

    
//    std::string teste2(myVector.begin(), myVector.end()); 
//    for(int i = 0; i< myVector.size(); i++){
//     teste2 = myVector[i].to_string<char,std::string::traits_type,std::string::allocator_type>();
//     std::cout << teste2;
//    }
    
    
    

    
    
    //for(std::string i : myVector)
    
    

    // for (auto const &pos : myVector)
    // std::cout << pos <<std::endl;

    // // "it" no longer valid, get a new one:
    // it = myvector.begin();

    // std::vector<int> anothervector (2,400);
    // myvector.insert (it+2,anothervector.begin(),anothervector.end());

    // int myarray [] = { 501,502,503 };
    // myvector.insert (myvector.begin(), myarray, myarray+3);

    // std::cout << "myvector contains:";
    // for (it=myvector.begin(); it<myvector.end(); it++)
    //     std::cout << ' '<< *it;
    // std::cout << '\n'; 

    // for (it = myvector.begin(); it < myvector.end(); it++)
    // std::cout <<' ' <<*it;
   
    

    return 0;
}