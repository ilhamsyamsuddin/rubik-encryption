#include<iostream>
#include<fstream>
#include<string>
#define N 4
using namespace std;

char cube[4][4][4]; //dimensinya [rows][columns][layers],
char temp_matrix[4][4];

void transpose(char arr[N][N])
{
 for (int i = 0; i < N; i++)
    for (int j = i; j < N; j++)
        swap(arr[i][j], arr[j][i]);
}

void rotate(char arr[N][N], char clockwise){
    transpose(temp_matrix);
    switch (clockwise)
    {
        case '1':
            int k;
            for (int i = 0; i < N; i++){
                k = N-1;
                for (int j = 0; j < k; j++){
                    swap(arr[j][i], arr[k][i]);
                    k--;
                }
            }
            break;

        case '0':
            int l;
            for (int i = 0; i < N; i++){
                l = N-1;
                for (int j = 0; j < l; j++){
                    swap(arr[i][j], arr[i][l]);
                    l--;
                }
            }
            break;
    }
}

int main(){
    string key;
    string plainText;
    int operated; //row/column/layer

    ifstream getKey;//input key
    getKey.open("shift_key.txt");
    getKey >> key;
    getKey.close();
    
    ifstream getPlainText("plaintext.txt");//input plaintext
    for (int x = 0 ; x <4; ++x){
        for (int y = 0 ; y <4; ++y){
            for (int z = 0 ; z <4; ++z){
                getPlainText >> noskipws >>cube[x][y][z];
            }
        }       
    }
    getPlainText.close();

    cout <<"The Key is "<<key<<endl;
    cout<<"the Plainetext is"<<endl;
    for (int x = 0 ; x <4; ++x)
    {
        for (int y = 0 ; y <4; ++y)
        {
            for (int z = 0 ; z <4; ++z)
            {
               cout <<cube[x][y][z];
            }
        }
        //cout<<endl;
    }
    cout<<endl;
    
    for (int index = 0; index < key.length(); index+=3){

        switch(key[index]) {
        case 'R':
            for (int i = 0; i < N; i++){
                operated = key[index+1]-48;
                for (int j = 0; j < N; j++){
                     temp_matrix[i][j]= cube[operated][i][j];
                }
            }
            rotate(temp_matrix, key[index+2]);
            for (int i = 0; i < N; i++){
                operated = key[index+1]-48;
                for (int j = 0; j < N; j++){
                    cube[operated][i][j] = temp_matrix[i][j];
                }
            }
            break;
        case 'C':
            operated = key[index+1]-48;
            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    temp_matrix[i][j] = cube[i][operated][j];
                }                
            }
            rotate(temp_matrix, key[index+2]);
            for (int i = 0; i < N; i++){
                operated = key[index+1]-48;
                for (int j = 0; j < N; j++){
                    cube[i][operated][j] = temp_matrix[i][j];
                }
            }
            break;
        case 'L':
            operated = key[index+1]-48;
            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    temp_matrix[i][j] = cube[i][j][operated];
                }                
            }
            rotate(temp_matrix, key[index+2]);
            for (int i = 0; i < N; i++){
                operated = key[index+1]-48;
                for (int j = 0; j < N; j++){
                    cube[i][j][operated] = temp_matrix[i][j];
                }
            }
            break;
        }
    }
    
    /*for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout<< temp_matrix[i][j];
        }
        cout<<endl;                
    }
    cout<<endl; 
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout<< cube[1][i][j];
        }
        cout<<endl;                
    }*/

    cout<<"the Cyphertext is"<<endl;
    for (int x = 0 ; x <4; ++x)
    {
        for (int y = 0 ; y <4; ++y)
        {
            for (int z = 0 ; z <4; ++z)
            {
               cout <<cube[x][y][z];
            }
        }
        //cout<<endl;
    }
    cout<<endl; 
}
