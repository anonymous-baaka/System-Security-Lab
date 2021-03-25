#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

string encrypt(string plaintext, int key)
{
	string encText="";
	for (int i = 0; i < plaintext.size(); i++)
	{
		char ch = plaintext[i]-'a';
		ch = (ch + key)%26;
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
		char ch = ciphertext[i]-'a';
		ch = (ch - key) % 26;
		ch += 'a';
		plainText += ch;
	}
	return plainText;
}

void factorise(int n,vector<int>& vec)
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
void createMatrices(vector<pair<int, int>>pairs, string ciphertext)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		//form matrix for pair	(col,row)
		char arr[100][100];
		int index = 0;
		for (int j = 0; j < pairs[i].first; j++)
		{
			for (int k = 0; k < pairs[i].second; k++)
			{
				if(index<ciphertext.size())
					arr[k][j] = ciphertext[index++];
				else 
					arr[k][j] ='\\';
			}
		}
		//display matrix
		for (int j = 0; j < pairs[i].second; j++)
		{
			for (int k = 0; k < pairs[i].first; k++)
			{
				cout << arr[j][k];
			}
			cout << endl;
		}
		cout << endl;

		cout << "final ciphered text: ";
		for (int j = 0; j < pairs[i].second; j++)
		{
			for (int k = 0; k < pairs[i].first; k++)
			{
				cout << arr[j][k];
			}
		}
		cout << endl;
		cout << "------------------\n";

		cout << "------------------\n";
	}
}
void createPair(vector<vector<int>>& set, vector<pair<int, int>>& pair,int product)
{
	for (int i = 0; i < set.size(); i++)
	{
		int subProduct = 1;
		for (int j = 0; j < set[i].size(); j++)
			subProduct *= set[i][j];
		if (!count(pair.begin(), pair.end(), make_pair(subProduct, product / subProduct)) && subProduct!=1 && product/subProduct!=1)
		{
			pair.push_back(make_pair(subProduct, product / subProduct));
			pair.push_back(make_pair(product / subProduct, subProduct));
		}
	}
	return;
}
void transposition(string ciphertext)
{
	int cipherLength = ciphertext.size();
	vector<int>factors;
	vector<pair<int, int>> pairs;
	vector<vector<int>>sets;
	factorise(cipherLength, factors);
	
	if (factors.size() == 1)
		factors.push_back(1);

	int product = 1;
	for (auto i : factors)
		product *= i;

	sets=subsets(factors);	//matrix dimensions
	createPair(sets,pairs,product);
	createMatrices(pairs, ciphertext);
}
string generateRandomPlaintext(int size)
{
	string str = "";
	for (int i = 0; i < size; i++)
	{
		char ch= rand() % 26+'a';
		str += ch;
	}
	return str;
}

string dTranspose(string& encryptedText,int nrow,int ncolumn) //detranspose deciphered text
{
	string plaintext = "";
	if (nrow == 0)
		nrow = encryptedText.size() / ncolumn;
	else if (ncolumn == 0)
		ncolumn = encryptedText.size() / nrow;
	int index = 0;
	vector<vector<char>> vec;
	for (int i = 0; i < nrow; i++)
	{
		vector<char>temp;
		for (int j = 0; j < ncolumn; j++)
		{
		temp.push_back(encryptedText[index++]);
		}
		vec.push_back(temp);
	}
	for (int i = 0; i < ncolumn; i++)
	{
		for (int j = 0; j < nrow; j++)
		{
		plaintext += vec[j][i];
		}
	}
	return plaintext;
}

int main()
{
	string plaintext;
	string ciphertext;
	int key;
	bool flag = true;
	int row,column;
	while (flag)
	{
		char ch;
		printf("\npress 'e' to  encrypt");
		printf("\npress 'd' to  decrypt");
		printf("\npress 'q' to  quit\n");
		cin >> ch;
		switch (ch)
		{
		case 'e':
			cout << "enter the text to encrypt: ";
			cin >> plaintext;
			//plaintext = generateRandomPlaintext(60);
			cout << "generated pt= " << plaintext << endl;
			do
			{
				cout << "Enter key (between 1 to 25)";
				cin >> key;
			} while (key < 1 || key>25);
			ciphertext=encrypt(plaintext,key);
			cout << "ciphered text: " << ciphertext << endl;
			transposition(ciphertext);
			break;
		case 'd':
			cout << "\nEnter cipher: ";
			cin >> ciphertext;
			cout << "\nenter key: ";
			cin >> key;
			plaintext = decrypt(ciphertext, key);
			cout << "\substituted key is: "<<plaintext<<endl;
			cout << "\nEnter row,column (0 if not known): ";
			cin >> row >> column;
			plaintext = dTranspose(plaintext, row,column);

			cout << "\nplaintext is: "<<plaintext<<endl;
			break;
		case 'q':
			flag = false;
			break;
		default:
			cout << "\ninvalid command. try again:";
		}
	}
}
