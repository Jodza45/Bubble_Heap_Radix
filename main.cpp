#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace chrono;

//int* kreirajNiz(int n)
//{
//	int* niz = new int[n];
//
//	srand(time(nullptr));
//	for (int i = 0; i < n; i++)
//	{
//		niz[i] = rand() % 10000;
//	}
//
//	return niz;
//}

int nadjiMaksCifre(int niz[], int n)
{
	int max = niz[0];
	for (int i = 0; i < n; i++)
	{
		if (niz[i] > max)
			max = niz[i];
	}

	int count = 0;
	do
	{
		++count;
		max = max / 10;
	} while (max > 0);

	return count;
}

void printaj(int niz[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << niz[i] << " ";
		//cout << "\n";
	}

	return;
}

void bablSort(int niz[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (niz[j] > niz[j + 1])
				swap(niz[j], niz[j + 1]);
		}
	}

	//printaj(niz, n);
	return;
}

//void heapSort(int niz[], int n)  //neki moj pokusaj heap sorta
//{                                //mozda ne izgleda kao klasicni heap sort
//	//printaj(niz, n);             //ali koristi elemente rada heap-a i sortira
//
//	for (int i = n - 1; i >= 0; i--)
//	{
//		int poz = i;
//		int j = i;
//
//		while (j != 0)
//		{
//			if (niz[j] > niz[(j - 1) / 2])
//			{
//				swap(niz[j], niz[(j - 1) / 2]);
//			}
//			--j;
//		}
//
//		swap(niz[j], niz[poz]);
//	}
//}


void hipifaj(int niz[], int i, int n)
{
	int najveci;
	int levo = i * 2 + 1;
	int desno = i * 2 + 2;

	if (levo < n && niz[levo] > niz[i])
		najveci = levo;
	else
		najveci = i;

	if (desno < n && niz[desno] > niz[najveci])
		najveci = desno;

	if (najveci != i)
	{
		swap(niz[i], niz[najveci]);
		hipifaj(niz, najveci, n);
	}
}

void bildhip(int niz[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		hipifaj(niz, i, n);
	}
}

void hipsort(int niz[], int n)
{
	bildhip(niz, n);

	for (int i = n - 1; i >= 1; i--)
	{
		swap(niz[0], niz[i]);
		hipifaj(niz, 0, i);
	}
}

void kauntSort(int niz[], int poz, const int n)
{
	const int baza = 10;
	int C[baza] = { 0,0,0,0,0,0,0,0,0,0 };
	int* B = new int[n];

	for (int i = 0; i < n; i++)
	{
		C[(niz[i] / poz) % 10] += 1;
	}

	for (int i = 1; i < baza; i++)
	{
		C[i] = C[i] + C[i - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		int cifra = (niz[i] / poz) % 10;
		B[C[cifra] - 1] = niz[i];       //jer krecem od indexa 0 (-1)
		C[cifra] = C[cifra] - 1;
	}

	for (int i = 0; i < n; i++)
	{
		niz[i] = B[i];
	}

	delete[] B;

	return;
}

void radiksSort(int niz[], int n)
{
	int maksBrCifri = nadjiMaksCifre(niz, n);
	int pozicija = 1;

	for (int i = 0; i < maksBrCifri; i++)
	{
		kauntSort(niz, pozicija, n);
		pozicija = pozicija * 10;
	}
}


int main()
{
	int* niz100 = new int[100];
	int* niz1000 = new int[1000];
	int* niz10k = new int[10000];
	int* niz100k = new int[100000];
	int* niz1m = new int[1000000];
	int* niz10m = new int[10000000];

	srand(time(nullptr));
	for (int i = 0; i < 100; i++)
	{
		niz100[i] = rand() % 10000;
	}
	for (int i = 0; i < 1000; i++)
	{
		niz1000[i] = rand() % 10000;
	}
	for (int i = 0; i < 10000; i++)
	{
		niz10k[i] = rand() % 10000;
	}
	for (int i = 0; i < 100000; i++)
	{
		niz100k[i] = rand() % 10000;
	}
	for (int i = 0; i < 1000000; i++)
	{
		niz1m[i] = rand() % 10000;
	}
	for (int i = 0; i < 10000000; i++)
	{
		niz10m[i] = rand() % 10000;
	}

	int cena = 0;

	////////////////////////////////////////////////////////////////////
	auto pocetak = high_resolution_clock::now();

	bablSort(niz100, 100);
	for (int i = 0; i < 5; i++)
	{
		cena += niz100[i];
	}

	auto kraj = high_resolution_clock::now();
	duration<double, milli> trajanje = kraj - pocetak;
	cout << "Vreme izvrsenja (100): " << trajanje.count() << " ms" << endl;

	////////////////////////////////////////////////////////////////////

	auto pocetak1 = high_resolution_clock::now();

	bablSort(niz1000, 1000);
	for (int i = 0; i < 5; i++)
	{
		cena += niz1000[i];
	}

	auto kraj1 = high_resolution_clock::now();
	duration<double, milli> trajanje1 = kraj1 - pocetak1;
	cout << "Vreme izvrsenja (1000): " << trajanje1.count() << " ms" << endl;

	//////////////////////////////////////////////////////////////////////

	auto pocetak2 = high_resolution_clock::now();

	bablSort(niz10k, 10000);
	for (int i = 0; i < 5; i++)
	{
		cena += niz10k[i];
	}

	auto kraj2 = high_resolution_clock::now();
	duration<double, milli> trajanje2 = kraj2 - pocetak2;
	cout << "Vreme izvrsenja (10k): " << trajanje2.count() << " ms" << endl;

	//////////////////////////////////////////////////////////////////////

	auto pocetak3 = high_resolution_clock::now();

	bablSort(niz100k, 100000);
	for (int i = 0; i < 5; i++)
	{
		cena += niz100k[i];
	}

	auto kraj3 = high_resolution_clock::now();
	duration<double, milli> trajanje3 = kraj3 - pocetak3;
	cout << "Vreme izvrsenja (100k): " << trajanje3.count() << " ms" << endl;

	//////////////////////////////////////////////////////////////////////
	
	auto pocetak4 = high_resolution_clock::now();

	bablSort(niz1m, 1000000);
	for (int i = 0; i < 5; i++)
	{
		cena += niz1m[i];
	}

	auto kraj4 = high_resolution_clock::now();
	duration<double, milli> trajanje4 = kraj4 - pocetak4;
	cout << "Vreme izvrsenja (1m): " << trajanje4.count() << " ms" << endl;

	//////////////////////////////////////////////////////////////////////
	
	auto pocetak5 = high_resolution_clock::now();

	bablSort(niz10m, 10000000);
	for (int i = 0; i < 5; i++)
	{
		cena += niz10m[i];
	}

	auto kraj5 = high_resolution_clock::now();
	duration<double, milli> trajanje5 = kraj5 - pocetak5;
	cout << "Vreme izvrsenja (10m): " << trajanje5.count() << " ms" << endl;

	///////////////////////////////////////////////////////////////////
	
	cout << "\n";
	cout << "Cena: " << cena;

	delete[] niz100;
	delete[] niz1000;
	delete[] niz10k;
	delete[] niz100k;
	delete[] niz1m;
	delete[] niz10m;
	
	return 0;
}