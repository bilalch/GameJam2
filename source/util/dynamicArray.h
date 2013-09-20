/*
 *  dynamicArray.cpp
 *  ArmyCitiesSQLite
 *
 *  Created by frt on 9/29/11.
 *  Copyright 2011 Fiverivers Technologies. All rights reserved.
 *
 */
/*************************************************************************
 ** This class implements dynamic array used for storing DB rows.
 */

#ifndef AeDynArray_cpp
#define AeDynArray_cpp

#include <iostream>

#include <cstdlib> 
#include <vector>
#include "s3e.h"

using namespace std;

template<class el>
class AeDynArray
{ 
public:
    AeDynArray(); // constructor
    ~AeDynArray(); // distructor  
	
    el& operator [] (unsigned int index); // get array item  
    el& GetIndex (unsigned int index); // get array item  
    void Add(el item); // Add item to the end of array  
	
    unsigned int GetSize(); // get size of array (elements)
    void Clear(); // clear array 
	void SafeClear(); // safe clear array (dont delete objects)
    void Delete(unsigned int pos); // delete array item  
	void release(); 
	//int AeDynArray<el>::Search(el item);
	int Search(el item);
	
private:
    vector <el> V; 
    unsigned int size; // size of array (elemets) 
};

////////////////////////////////////////////////////////////////////// 

template <class el>
AeDynArray<el>::AeDynArray() 
{ 
    size = 0;
} 

template <class el>
AeDynArray<el>::~AeDynArray() 
{ 
    for(int i = 0; i < size; i++)
		delete V[i];
	
	V.clear();
}

template <class el>
unsigned int AeDynArray<el>::GetSize() 
{
	return size; // simply return size 
} 

template <class el>
void AeDynArray<el>::Delete(unsigned int pos) 
{ 
	delete V[pos];

	V.erase(V.begin() + pos);
	size--;
} 

template <class el>
void AeDynArray<el>::release() 
{  
	for(unsigned int i=0; i<size; i++){ 
		delete V[i]; 
	}

	Clear();
} 

template <class el>
void AeDynArray<el>::Clear() // clear array memory  
{
	V.clear();
	size = 0;
} 

template <class el>
void AeDynArray<el>::SafeClear() // clear array memory  
{
	V.clear();
	size = 0;
} 

template <class el>
el& AeDynArray<el>::operator [] (unsigned int index) 
{ 
    return V[index]; // return array element  
}

template <class el>
el& AeDynArray<el>::GetIndex (unsigned int index) 
{ 
    return V[index]; // return array element  
}

template <class el>
void AeDynArray<el>::Add(el item) 
{ 
	V.push_back(item);
	size++;
} 

template <class el>
int AeDynArray<el>::Search(el item) 
{ 
	for(int i = 0; i < V.GetSize(); i++){
		if(item == V[i])
			return i;
	}

	return -1;
} 

#endif