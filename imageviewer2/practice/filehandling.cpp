#include <iostream>
#include<fstream>
// #include <bits/stdc++.h>

int main(){
    std::ifstream file("../data/default.ppm");
    std::string s;
    getline(file, s);  
    file>>s;
    if(s[0]=='#'){
    getline(file, s);
    file>>s;
    }
    int width = std::stoi(s);
    file>>s;
    int height = std::stoi(s);
    file.close();
    std::cout<<"width"<<width<<"height"<<height; 
}