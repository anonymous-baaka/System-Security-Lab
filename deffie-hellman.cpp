#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<random>
#include<math.h>
using namespace std;

class user {
private:
	long long int publicKey1;
	long long int publicKey2;
	long long int generatedKey;		//result
	long long int recievedKey;
	long long int secretKey;
	long long int privateKey;		//secret number

	static vector<int>primeList; 
public:
	user(long long int _pubKey1, long long int _pubKey2) :publicKey1(_pubKey1), publicKey2(_pubKey2) 
	{
		privateKey= generatePrivateKey();
		generatedKey = generateKey();
	}
	user(long long int _pubKey1, long long int _pubKey2,long long int _priKey) :publicKey1(_pubKey1), publicKey2(_pubKey2),privateKey(_priKey)
	{
		generatedKey = generateKey();
	}

	long long int getGeneratedKey()
	{
		return generatedKey;
	}

	void exchangeKey(user& otherUser)
	{
		this->recievedKey = otherUser.getGeneratedKey();
		secretKey=generateSecretKey();
	}
	long long int getSecretKey()
	{
		return secretKey;
	}
	long long int getPrivateKey()
	{
		return privateKey;
	}
	long long int getRecievedKey()
	{
		return recievedKey;
	}

private:
	long long int generatePrivateKey() 
	{
		srand((unsigned int)time(NULL));
		return primeList[rand()%primeList.size()];
	}
	long long int generateKey()
	{
		return (long long int)((long long int)pow(publicKey1, privateKey) % publicKey2);
	}
	long long int generateSecretKey()
	{
		return (long long int)((long long int)pow(recievedKey, privateKey) % publicKey2);
	}
	
};

vector<int> user::primeList = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

//privage key or secret number
 int main()
{
	srand(time(0));
	int primeNo;
	int generator;

	cout << "Enter first prime: " ;
	cin >> primeNo;

	do
	{
		cout << "\nEnter second prime lesser than " << primeNo << ": ";
		cin >> generator;
		cout << endl;
	} while (generator>=primeNo);
	

	cout << "First prime= " << primeNo << endl;
	cout << "second prime= " << generator << endl;

	int secA, secB;
	cout << "\nuser1: enter secret key: ";
	cin >> secA;
	cout << "\nuser2: enter secret key: ";
	cin >> secB;

	user u1(generator, primeNo,5);
	user u2(generator, primeNo,12);
	u1.exchangeKey(u2);
	u2.exchangeKey(u1);

	cout << "\n----------------------------------";
	cout << "\n\nuser1 sends "<<u1.getGeneratedKey()<<" to user2";
	cout << "\n\nuser2 sends " << u2.getGeneratedKey() << " to user1";

	cout << "\n\nUser1 takes " << u1.getRecievedKey() << " raises it to the power " << u1.getPrivateKey() << " mod " << primeNo;
	cout << "\nkey calculated by user1: " << u1.getSecretKey();

	cout << "\n\nUser2 takes " << u2.getRecievedKey() << " raises it to the power " << u2.getPrivateKey() << " mod " << primeNo;
	cout << "\nkey calculated by user2: " << u2.getSecretKey();
	return 0;
}
