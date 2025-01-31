//
// Created by aviku on 30/12/2021.
//

#define X 31.81428051893798
#define Y 35.18577781093502
#include <vector>
#include <cstddef>
#include <unordered_set>
#include <string>
#include <chrono>
#include <iostream>
#include <ostream>
#include <fstream>
#include "Apartment.h"
#include "Apartment.cpp"
#include "Find.h"
#include "AVL.h"
#include "AVL.cpp"
#include "Stack.h"
#include "Stack.cpp"
#include <sstream>
#include "Find.h"
#include "MesureTimeHelper.h"
#include <iostream>
#include <unordered_set>
int check1()
{
    std::pair<double, double> temp;
    temp = std::make_pair(X, Y);
    Apartment x(temp);
    std::vector <std::pair<double, double>> vector;
    std::string filepath = "C:\\Users\\aviku\\CLionProjects\\ex6\\apartments100.txt";
    vector = xy_from_file(filepath);
    auto t1 = std::chrono::high_resolution_clock::now();
    Stack stack(vector);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count()<<std::endl;
    auto t3 = std::chrono::high_resolution_clock::now();
    find(stack.begin(),stack.end(),x);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count()<<std::endl;
    auto t5 = std::chrono::high_resolution_clock::now();
    AVL avl(vector);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t6-t5).count()<<std::endl;
    auto t7 = std::chrono::high_resolution_clock::now();
    avl.find(x);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t8-t7).count()<<std::endl;
    auto t9 = std::chrono::high_resolution_clock::now();
    find(avl.begin(),avl.end(),x);
    auto t10 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t10-t9).count()<<std::endl;
    auto t11 = std::chrono::high_resolution_clock::now();
    std::unordered_set<Apartment, MyHashFunction> a;
    auto t12 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t12-t11).count()<<std::endl;
    auto t13 = std::chrono::high_resolution_clock::now();
    a.find(x);
    auto t14 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t14-t13).count()<<std::endl;
    auto t15 = std::chrono::high_resolution_clock::now();
    find(a.begin(),a.end(),x);
    auto t16 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t14-t13).count()<<std::endl;
    return 0;
};

int check2()
{
    std::pair<double, double> temp;
    temp = std::make_pair(X, Y);
    Apartment x(temp);
    std::vector <std::pair<double, double>> vector;
    std::string filepath = "C:\\Users\\aviku\\CLionProjects\\ex6\\apartments1000.txt";
    vector = xy_from_file(filepath);
    auto t1 = std::chrono::high_resolution_clock::now();
    Stack stack(vector);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count()<<std::endl;
    auto t3 = std::chrono::high_resolution_clock::now();
    find(stack.begin(),stack.end(),x);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count()<<std::endl;
    auto t5 = std::chrono::high_resolution_clock::now();
    AVL avl(vector);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t6-t5).count()<<std::endl;
    auto t7 = std::chrono::high_resolution_clock::now();
    avl.find(x);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t8-t7).count()<<std::endl;
    auto t9 = std::chrono::high_resolution_clock::now();
    find(avl.begin(),avl.end(),x);
    auto t10 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t10-t9).count()<<std::endl;
    auto t11 = std::chrono::high_resolution_clock::now();
    std::unordered_set<Apartment, MyHashFunction> a;
    auto t12 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t12-t11).count()<<std::endl;
    auto t13 = std::chrono::high_resolution_clock::now();
    a.find(x);
    auto t14 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t14-t13).count()<<std::endl;
    auto t15 = std::chrono::high_resolution_clock::now();
    find(a.begin(),a.end(),x);
    auto t16 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t14-t13).count()<<std::endl;
    return 0;
};



int check3()
{
    std::pair<double, double> temp;
    temp = std::make_pair(X,Y);
    Apartment x(temp);
    std::vector <std::pair<double, double>> vector;
    std::string filepath = "C:\\Users\\aviku\\CLionProjects\\ex6\\apartments10000.txt";
    vector = xy_from_file(filepath);
    auto t1 = std::chrono::high_resolution_clock::now();
    Stack stack(vector);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count()<<std::endl;
    auto t3 = std::chrono::high_resolution_clock::now();
    find(stack.begin(),stack.end(),x);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count()<<std::endl;
    auto t5 = std::chrono::high_resolution_clock::now();
    AVL avl(vector);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t6-t5).count()<<std::endl;
    auto t7 = std::chrono::high_resolution_clock::now();
    avl.find(x);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t8-t7).count()<<std::endl;
    auto t9 = std::chrono::high_resolution_clock::now();
    find(avl.begin(),avl.end(),x);
    auto t10 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t10-t9).count()<<std::endl;
    auto t11 = std::chrono::high_resolution_clock::now();
    std::unordered_set<Apartment, MyHashFunction> a;
    auto t12 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t12-t11).count()<<std::endl;
    auto t13 = std::chrono::high_resolution_clock::now();
    a.find(x);
    auto t14 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t14-t13).count()<<std::endl;
    auto t15 = std::chrono::high_resolution_clock::now();
    find(a.begin(),a.end(),x);
    auto t16 = std::chrono::high_resolution_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(t14-t13).count()<<std::endl;
    return 0;
};

