#include<iostream>
#include<fstream>
#include<string>
#define N 4
using namespace std;

char cube[4][4][4]; //dimensinya [rows][columns][layers],
char temp_matrix[4][4];

string XorAscii(string str, string key)
{
 
    // store value of first character
    string xored = "";
    char ans;
 
    for (int i = 0; i < str.length(); i++) {
 
        // Traverse string to find the XOR
        ans = int(str[i]) ^ int(key[i]);
        xored += ans;
    }
 
    // Return the XOR
    return xored;
}
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
        case '1'://clockwise
            int k;
            for (int i = 0; i < N; i++){
                k = N-1;
                for (int j = 0; j < k; j++){
                    swap(arr[j][i], arr[k][i]);
                    k--;
                }
            }
            break;

        case '0'://counterclockwise
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
    string shift_key;
    string key = "";
    string plainText;
    string keys[5];// to store scrabled key for each round
    int operated; //row/column/layer

    ifstream getShift;//input shift key, key to shift the cube
    getShift.open("shift_key.txt");
    getShift >> shift_key;
    getShift.close();

    ifstream getPlaintext;//input plaintext
    getPlaintext.open("example.txt");
    getPlaintext >>plainText;
    getPlaintext.close();
    
    ifstream getKey("key.txt");//input key to array
    for (int x = 0 ; x <4; ++x){
        for (int y = 0 ; y <4; ++y){
            for (int z = 0 ; z <4; ++z){
                getKey>> noskipws >>cube[x][y][z];
            }
        }       
    }
    getKey.close();

    cout <<"The shift_Key is "<<shift_key<<endl;
    cout<<"the key is"<<endl;
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
    cout <<"The plaintext is "<<plainText<<endl;

    //Generate Keys
    for (int round = 0; round < 5; round++)
    {
        for (int index = 0; index < shift_key.length(); index+=3){

            switch(shift_key[index]) {
            case 'R'://shift row
                for (int i = 0; i < N; i++){
                    operated = shift_key[index+1]-48;
                    for (int j = 0; j < N; j++){
                        temp_matrix[i][j]= cube[operated][i][j];
                    }
                }
                rotate(temp_matrix, shift_key[index+2]);
                for (int i = 0; i < N; i++){
                    operated = shift_key[index+1]-48;
                    for (int j = 0; j < N; j++){
                        cube[operated][i][j] = temp_matrix[i][j];
                    }
                }
                break;
            case 'C':
                operated = shift_key[index+1]-48;
                for (int i = 0; i < N; i++){
                    for (int j = 0; j < N; j++){
                        temp_matrix[i][j] = cube[i][operated][j];
                    }                
                }
                rotate(temp_matrix, shift_key[index+2]);
                for (int i = 0; i < N; i++){
                    operated = shift_key[index+1]-48;
                    for (int j = 0; j < N; j++){
                        cube[i][operated][j] = temp_matrix[i][j];
                    }
                }
                break;
            case 'L':
                operated = shift_key[index+1]-48;
                for (int i = 0; i < N; i++){
                    for (int j = 0; j < N; j++){
                        temp_matrix[i][j] = cube[i][j][operated];
                    }                
                }
                rotate(temp_matrix, shift_key[index+2]);
                for (int i = 0; i < N; i++){
                    operated = shift_key[index+1]-48;
                    for (int j = 0; j < N; j++){
                        cube[i][j][operated] = temp_matrix[i][j];
                    }
                }
                break;
            }
        }
        
        for (int x = 0 ; x <4; ++x){
            for (int y = 0 ; y <4; ++y){
                for (int z = 0 ; z <4; ++z){
                    key+=cube[x][y][z];
                }
            }
        }

        plainText = XorAscii(plainText,key);
        key = ""; 
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

    cout<<"the Cyphertext is stored in paper_ciphertext.txt"<<endl;
    ofstream myfile;
    myfile.open ("paper_ciphertext.txt");
    myfile << plainText <<shift_key;
    myfile.close();
    //cout<<plainText;
}
