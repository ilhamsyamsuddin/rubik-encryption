#include<iostream>
#include<string>
#include<fstream>
using namespace std;

char mat[6][3][3]={0},temp[3]={0},rubik[6][3][3]={0};

void getKey()
{
  ifstream ifile("letterlist.txt");
  for (int x = 0 ; x <6; ++x)
      {
           for (int y = 0 ; y <3; ++y)
           {
               for (int z = 0 ; z <3; ++z)
               {
                   ifile >> noskipws >>mat[x][y][z];
                   rubik[x][y][z]=mat[x][y][z];
               }
           }
      }
    ifile.close();
} 

int main(){
    string input;
}