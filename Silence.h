#pragma once
#include "Sound.h"
template <typename Type, size_t M>
class Silence : public Sound<Type,M>
{
public:
	Silence(size_t duration) : Sound(duration) {}

	virtual const Type& operator[](size_t)const override
	{
		return 0;
	}

	virtual Sound<Type,M>* clone()const override
	{
		return new Silence(*this);
	}
};