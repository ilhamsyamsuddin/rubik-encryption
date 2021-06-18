#include<iostream>
#include<fstream>
#include<string>
#define N 4
using namespace std;

char cube[4][4][4]; //dimensinya [rows][columns][layers],
char temp_matrix[4][4];

int main(){
    string key;
    string plainText;

    ifstream getKey;
    getKey.open("key.txt");
    getKey >> key;
    getKey.close();
    
    ifstream getPlainText("plaintext.txt");
    for (int x = 0 ; x <4; ++x)
    {
        for (int y = 0 ; y <4; ++y)
        {
            for (int z = 0 ; z <4; ++z)
            {
                getPlainText >> noskipws >>cube[x][y][z];
            }
        }       
    }
    getPlainText.close();
    
    
    cout <<"The Key is "<<key<<endl;
    for (int x = 0 ; x <4; ++x)
    {
        for (int y = 0 ; y <4; ++y)
        {
            for (int z = 0 ; z <4; ++z)
            {
               cout <<cube[x][y][z];
            }
        }
        cout<<endl;
    }
}
