#ifndef COLLECTION_H
#define COLLECTION_H

#include "Arduino.h"


template<class E, int ARRAYSIZE = 10>
class CircularQueue{
protected:
	E col[ARRAYSIZE];
	byte size = ARRAYSIZE;
public:
	byte length(){return size;}
	E& operator[](const byte& index){return col[index]}
};

#include <collection.cpp>

#endif //COLLECTION_H