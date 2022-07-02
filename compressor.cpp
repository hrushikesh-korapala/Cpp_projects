#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <unordered_map>

using namespace std;

class Node
{
public:
    char letter;
    int rep;
    Node *left;
    Node *right;
    Node(char a, int r)
    {
        letter = a;
        rep = r;
        left = NULL;
        right = NULL;
    }
    Node(Node *A, Node *B)
    {
        rep = A->rep + B->rep;
        left = A;
        right = B;
    }
};

bool cmp(pair<char, int> &a, pair<char, int> &b)
{
    return a.second < b.second;
}

vector<Node *> reduce(vector<Node *> ter)
{
    vector<Node *> terr;
    vector<Node *>::iterator it = ter.begin();
    int num = 0, index = 0;
    Node *B, *temp1;
    while (it != ter.end())
    {
        if (num == 0)
        {

            B = new Node(*it, *(it + 1));

            terr.push_back(B);
            it++;
            it++;
            index = 0;
            num++;
        }
        else if (num == 1)
        {

            if (terr[index]->rep <= (*it)->rep)
            {

                temp1 = ter[index];
                index++;
            }
            else
            {

                temp1 = *it;
                if (it == ter.end() - 1)
                {
                    B = new Node(temp1, ter[index]);

                    terr.push_back(B);
                    index++;
                }

                it++;
            }
            num++;
        }
        else if (num == 2)
        {

            if (terr[index]->rep <= (*it)->rep && num < ter.size())
            {
                B = new Node(temp1, ter[index]);
                terr.push_back(B);
                index++;
            }
            else
            {

                B = new Node(temp1, *it);
                terr.push_back(B);
                it++;
            }
            num = 1;
        }
        else
        {
            cout << "ERROR" << endl;
        }
    }

    return terr;
}

Node *Create_huffman_tree(vector<pair<char, int>> freq)
{
    vector<pair<char, int>>::iterator it = freq.begin();

    vector<Node *> ter, terr;
    Node *temp1, *B;
    int reps = 0;
    int num = 0;
    int index = 0;
    while (it != freq.end())
    {
        if (num == 0)
        {

            B = new Node(new Node(it->first, it->second), new Node((it + 1)->first, (it + 1)->second));
            ter.push_back(B);
            it++;
            it++;
            index = 0;
            num++;
        }
        else if (num == 1)
        {

            if (ter[index]->rep <= it->second)
            {

                temp1 = ter[index];
                index++;
            }
            else
            {

                temp1 = new Node(it->first, it->second);
                if (it == freq.end() - 1)
                {
                    B = new Node(temp1, ter[index]);
                    ter.push_back(B);
                    index++;
                }

                it++;
            }
            num++;
        }
        else if (num == 2)
        {

            if (ter[index]->rep <= it->second && num < ter.size())
            {
                B = new Node(temp1, ter[index]);
                ter.push_back(B);
                index++;
            }
            else
            {

                B = new Node(temp1, new Node(it->first, it->second));
                ter.push_back(B);
                it++;
            }
            num = 1;
        }
        else
        {
            cout << "ERROR" << endl;
            return 0;
        }
    }

    for (int i = index; i < ter.size(); i++)
    {
        terr.push_back(ter[i]);
    }
    while (terr.size() != 1)
    {
        terr = reduce(terr);
    }
    return terr[0];
}

void Create_hufftable(Node *head, string str, unordered_map<char, string> &ans)
{
    if (head->left == NULL && head->right == NULL)
    {
        ans[head->letter] = str;
        return;
    }
    Create_hufftable(head->right, str + '0', ans);
    Create_hufftable(head->left, str + '1', ans);
}

char dump(char a)
{
    char b=0;
    for (int i = 0; i < 8; i++)
    {
        b <<= 1;
        b += abs(a % 2);
        a >>= 1;
    }
    // cout<<(int)b<<endl;
    char k=b;
    for (int i = 0; i < 8; i++)
    {
        // cout << abs(k % 2);
        k >>= 1;
    }

    
    return b;
}

int main()
{

    ifstream myfile("huffman.txt");
    string str;
    vector<string> data;
    unordered_map<char, int> fre;

    while (getline(myfile, str))
    {
        data.push_back(str);
    }

    for (string a : data)
    {
        for (char b : a)
        {
            fre[b]++;
        }
    }

    vector<pair<char, int>> freq;
    for (pair<char, int> a : fre)
    {
        freq.push_back(a);
    }
    sort(freq.begin(), freq.end(), cmp);
    myfile.close();

    Node *head = Create_huffman_tree(freq);
    string st;
    unordered_map<char, string> table;
    Create_hufftable(head, st, table);

    ofstream hehe("table.txt");
    for (pair<char, string> H : table)
    {
        hehe << H.first << ' ' << H.second << endl;
    }
    hehe.close();
    ifstream myfile2("huffman.txt");
    ofstream coderfile("encoded.bin", ios::binary);
    char storage = 0, inter = 0;
    int eight = 0;
    while (getline(myfile2, str))
    {
        for (char F : str)
        {
            string con = table[F];
            // cout<<table[F]<<endl;
            int sil = con.size();
            for (int i = 0; i < sil; i++)
            {
                // cout<<(int)a<<endl;

                inter <<= 1;
                inter += (con[i] - 48);
                eight++;
                if (eight == 8)
                {
                    storage = dump(inter);
                    //cout << storage << endl;
                    // cout<<(int)inter<<endl;
                    coderfile << storage;
                    inter = 0;
                    storage = 0;
                    eight = 0;
                }
            }
        }
        if (eight != 0)
        {
            while (eight != 8)
            {
                inter <<= 1;
                eight++;
            }
            storage = dump(inter);
            coderfile << storage;
        }
    }
    myfile2.close();
    coderfile.close();
    return 0;
}