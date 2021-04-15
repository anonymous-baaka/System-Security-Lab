#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string>
#define CEASKEY 3

int Mycount = 0;
using namespace std;

vector<string> permute(string a, int l, int r)
{
    if (l == r)
    {
        vector<string> vec;
        vec.push_back(a);
        return vec;
    }

    else
    {
        vector<string>output;
        for (int i = l; i <= r; i++)
        {
            swap(a[l], a[i]);
            vector<string>temp=permute(a, l + 1, r);
            for (auto a : temp)
            {
                output.push_back(a);
            }
            swap(a[l], a[i]);
        }
        return output;
    }
}

void generateCombinations(vector<vector<char>>& inputmatrix, vector<vector<vector<char>>>& outputMatrix, vector<string>& toPermuteOver, int ncol)
{
    int nrow = (inputmatrix.size() * inputmatrix[0].size()) / ncol;
    for (int i = 0; i < toPermuteOver.size(); i++)
    {
        vector<vector<char>> twoD;
        for (int row = 0; row < nrow; row++)
        {
            vector<char>oneD;
            for (int col = 0; col < ncol; col++)
            {
                int myCol = (int)toPermuteOver[i][col] - 48;
                //twoD[row][col] = inputmatrix[row][(int)toPermuteOver[i][col] - 48];
                oneD.push_back(inputmatrix[row][(int)toPermuteOver[i][col] - 48]);
            }
            twoD.push_back(oneD);
        }
        outputMatrix.push_back(twoD);
    }
    return;
}
vector<vector<vector<char>>> generateMatrixOfMatrices(vector<vector<char>>& inputmatrix, int key)
{
	vector<vector<vector<char>>>outputMatrix;
    string temp = "";
    for (int i = 0; i < key; i++)
        temp += char(i+48);
    vector<string>toPermuteOver = permute(temp, 0, temp.size()-1);
    
    generateCombinations(inputmatrix,outputMatrix, toPermuteOver, key);
    return outputMatrix;
}

string encrypt(string plaintext, int key)
{
    string encText = "";
    for (int i = 0; i < plaintext.size(); i++)
    {
        char ch = plaintext[i] - 'a';
        ch = (ch + key) % 26;
        ch += 'a';
        encText += ch;
    }
    return encText;
}

string decrypt(string ciphertext, int key)
{
    string plainText = "";
    for (int i = 0; i < ciphertext.size(); i++)
    {
        char ch = ciphertext[i] - 'a';
        ch = (ch - key) % 26;
        ch += 'a';
        plainText += ch;
    }
    return plainText;
}
void display3d(vector<vector<vector<char>>> output)
{
    //cout << "\ndAll matrix combinations: \n "<< endl;
    for (int i = 0; i < output.size(); i++)
    {
        string myText = "";
        for (int j = 0; j < output[i].size(); j++)
        {
            for (int k = 0; k < output[i][j].size(); k++)
            {
                cout << output[i][j][k]<<" ";
                myText += output[i][j][k];
            }
            cout << endl;
        }
        Mycount++;
        cout << "\n" << decrypt(myText, CEASKEY)<<endl<<endl;
        //cout << "\n--------------------\n";

    }
    return;
}


vector<vector<char>> makeTranspoMatrix(string subtext, int col)
{
    vector<vector<char>> op;
    vector<char>one1;
    int row = subtext.size() / col;
    int index = 0;
    for (int i = 0; i < subtext.size(); i++)
    {
        one1.push_back(subtext[i]);
        index++;
        if (index >= col)
        {
            op.push_back(one1);
            one1 = {};
            index = 0;
        }
    }
    return op;
}
void factorise(int n, vector<int>& vec)
{
    if (n == 1)
        return;
    if (n == 2)
    {
        vec.push_back(2);
        return;
    }
    int flag = true;
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            flag = false;
            vec.push_back(i);
            n = n / i;
            factorise(n, vec);
            break;
        }
    }
    if (flag)
    {
        vec.push_back(n);
    }
    return;
}
void subsetsUtil(vector<int>& A, vector<vector<int> >& res,
    vector<int>& subset, int index)
{
    res.push_back(subset);
    for (int i = index; i < A.size(); i++)
    {
        subset.push_back(A[i]);
        subsetsUtil(A, res, subset, i + 1);
        subset.pop_back();
    }
    return;
}

vector<vector<int> > subsets(vector<int>& A)
{
    vector<int> subset;
    vector<vector<int> > res;
    int index = 0;
    subsetsUtil(A, res, subset, index);
    return res;
}

void createPair(vector<vector<int>>& set, vector<pair<int, int>>& pair, int product)
{
    for (int i = 0; i < set.size(); i++)
    {
        int subProduct = 1;
        for (int j = 0; j < set[i].size(); j++)
            subProduct *= set[i][j];
        if (!count(pair.begin(), pair.end(), make_pair(subProduct, product / subProduct)) && subProduct != 1 && product / subProduct != 1)
        {
            pair.push_back(make_pair(subProduct, product / subProduct));
            pair.push_back(make_pair(product / subProduct, subProduct));
        }
    }
    return;
}

string generateRandomPlaintext(int size)
{
    string str = "";
    for (int i = 0; i < size; i++)
    {
        char ch = rand() % 26 + 'a';
        str += ch;
    }
    return str;
}

int main()
{
    string plaintext = "";
    string subText = "";
	int key;
    //cout << "\nEnter plaintext: ";
    //cin >> plaintext;
    //cout << "\nEnter key: ";
    //cin >> key;
    plaintext = generateRandomPlaintext(16);
    cout << "\nplaintext= " << plaintext<<endl;
    subText = encrypt(plaintext, CEASKEY);
    cout << "\nsubstituted text= " << subText<<endl;

    int cipherLength = plaintext.size();
    vector<int>factors;
    vector<pair<int, int>> pairs;
    vector<vector<int>>sets;
    factorise(cipherLength, factors);

    //cout << "\n length of substituted text = " << cipherLength;
    //cout << "\n factors of " << cipherLength << " = ";
    /*for (int i = 1; i <= cipherLength; i++)
    {
        if (cipherLength % i == 0)
            cout << i << ", ";
    }*/
    cout << endl;

    if (factors.size() == 1)
        factors.push_back(1);

    int product = 1;
    for (auto i : factors)
        product *= i;

    sets = subsets(factors);	//matrix dimensions

    createPair(sets, pairs, product);

    for (int i = 0; i < pairs.size(); i++)
    {
        key = pairs[i].first;
        vector<vector<char>> matrix = makeTranspoMatrix(subText, key);//{ {'n','x','q'},{'d','o',' '},{'f','k','d'},{'x','g','k'},{'d','u','b'} };

        vector<vector<vector<char>>> output = generateMatrixOfMatrices(matrix, key);

        cout << "\n\n----------------------------\n\n";
        cout << "\nfor " << pairs[i].first << " " << pairs[i].second<<endl;
        cout << "\n\n----------------------------\n\n";
        display3d(output);
        
    }

    cout << "\n\nTotal = " << Mycount << endl;
}
