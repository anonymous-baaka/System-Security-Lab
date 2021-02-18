#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<utility>
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
void permute(vector<int>factors, vector<pair<int, int>>& pairs)
{
	int product = 1;
	for (int i = 0; i < factors.size(); i++)
		product *= factors[i];
	for (int i = 0; i < factors.size(); i++)
	{
		if (!count(pairs.begin(), pairs.end(), make_pair(factors[i], product / factors[i])))
		{
			pairs.push_back(make_pair(factors[i], product / factors[i]));
			pairs.push_back(make_pair(product / factors[i], factors[i]));
		}
	}
	return;
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
		cout << "------------------\n";
	}
}
void transposition(string ciphertext)
{
	int cipherLength = ciphertext.size();
	vector<int>factors;
	vector<pair<int, int>> pairs;
	factorise(cipherLength, factors);
	if (factors.size() == 1)
		factors.push_back(1);
	permute(factors,pairs);		//matrix dimensions
	createMatrices(pairs, ciphertext);
}
int main()
{
	string plaintext;
	string ciphertext;
	int key;
	bool flag = true;
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
			cout << "\ndecrypted key is: "<<plaintext<<endl;
			break;
		case 'q':
			flag = false;
			break;
		default:
			cout << "\ninvalid command. try again:";
		}
	}
}
