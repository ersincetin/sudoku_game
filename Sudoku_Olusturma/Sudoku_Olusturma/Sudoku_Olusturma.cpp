// Sudoku_Olusturma.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
int arr[9][9] = {0};
//aynı satır kontrol etme
bool kontrol_satır(int i,int value) {
	for (size_t j = 0; j < 9; j++)
	{
		if (arr[i][j] == value) { return false; }
	}
	return true;
}
//aynı sutunda kontrol etme
bool kontrol_sutun(int j,int value) {
	for (size_t i = 0; i < 9; i++)
	{
		if (arr[i][j] == value) { return false; } 
	}
	return true;
}
//3x3 kutu kontrol etme
bool kontrol_kucuk_kutu(int satır,int sutun,int num) {
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (arr[satır + i][sutun + j] == num) { return false;}
		}
	}
	return true;
}
//genel kontrol etme
bool genel_kontrol(int i, int j, int num) {
	return (kontrol_satır(i, num) && kontrol_sutun(j, num) && kontrol_kucuk_kutu(i - i % 3, j - j % 3, num));
}
//3x3 kutu doldurmaca
void kutu_doldur(int satır,int sutun) {
	int num;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			do {
				num = rand() % 9 + 1 ;
			} while (!kontrol_kucuk_kutu(satır,sutun,num));
			arr[satır+i][sutun+j] = num;
		}
	}
}
//dioganal doldurmaca
void dioganal_doldurmaca() {
	for (size_t i = 0; i < 9; i+=3)
	{
		kutu_doldur(i, i);
	}
}
//geri kalan yerleri doldurmaca
bool bosluk_doldurmaca(int i, int j) {
	
	if (j >= 9 && i < 9 - 1)
	{
		i = i + 1;
		j = 0;
	}
	if (i >= 9 && j >= 9) { return true; }
	if (i < 3)
	{
		if (j < 3)
			j = 3;
	}
	else if (i < 9 - 3)
	{
		if (j == (int)(i / 3)*3)
			j = j + 3;
	}
	else
	{
		if (j == 9 - 3)
		{
			i = i + 1;
			j = 0;
			if (i >= 9)
				return true;
		}
	}
	for (size_t num = 1; num <= 9; num++)
	{
		if (genel_kontrol(i, j, num))
		{
			arr[i][j] = num;
			if (bosluk_doldurmaca(i, j + 1)) {return true;}
			arr[i][j] = 0;
		}
	}
	return false;
}
//rastgele sıfırlama
void rastgele_sifirlama() {
	srand(time(NULL));
	int sayi = rand() % 10 + 25;
	int x, y;
	do {
		x = rand() % 9;
		y = rand() % 9;
		if (arr[x][y] != 0)
		{
			arr[x][y] = 0; sayi--;
		}
	} while (sayi != 0);
}

void olustur() {
	dioganal_doldurmaca();
	bosluk_doldurmaca(0,3);
	rastgele_sifirlama();
}
//ekrana yazdırma
void yazdır() {
	//olusturulan diziyi yazdırma...
	cout << "::::::::::::::::::::::::::::::::::::::::" << endl;
	for (size_t i = 0; i < 9; i++)
	{
		cout << "| ";
		for (size_t j = 0; j < 9; j++)
		{
			if (j % 3 == 2) { if (arr[i][j] != 0) { cout << arr[i][j] << " || "; } else { cout << " " << " || "; } }
			else { if (arr[i][j] != 0) { cout << arr[i][j] << " | "; } else { cout << " " << " | "; } }
		}
		if (i % 3 == 2) {
			cout << endl << "::::::::::::::::::::::::::::::::::::::::" << endl;
		}
		else {
			cout << endl << "----------------------------------------" << endl;
		}
	}
}

int main()
{
	srand(time(NULL));
	olustur(); yazdır();
	cout << endl;
	return 0;
}