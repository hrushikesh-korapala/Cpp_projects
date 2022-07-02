#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ios>
#include <list>
#include <fstream>
#include <unordered_map>

using namespace std;

int main()
{
    ifstream tablet("table.txt");
    string str;
    unordered_map<string, int> table;
    int temp;
    int t = 0;
    while (tablet >> str)
    {
        if (t == 0)
        {
            temp = str[0];
            t++;
        }
        else
        {
            table[str] = temp;
            t = 0;
        }
    }
    // for(pair<string,int> a:table)
    // {
    //     cout<<(char)a.second<<' '<<a.first<<endl;
    // }
    tablet.close();

    ifstream encoded("encoded.bin");
    ofstream decoded("decoded.txt");
    string data;
    getline(encoded, data);
    int b;
    string msg="";
    for (char a : data)
    {
        // cout << (int)a << endl;
        char l=a;
        int c=8;
        while (c--)
        {
            
            b=abs(l%2);
            
            if (b==1)
            {
                msg=msg+"1";
            }
            else
            {
                msg=msg+"0";
            }
            l>>=1;
            // cout<<b<<' ';
            // cout<<msg<<endl;
            if (table[msg] != 0)
            {
                //cout<<msg<<endl;
                decoded << (char)table[msg];
                msg.clear();
                b = 0;
            }
        }
        // cout<<endl;
    }
    
    return 0;
}