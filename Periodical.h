#pragma once
#include "Sound.h"
template <typename Type, size_t M>
class Periodical : public Sound<Type, M>
{
public:
	Periodical(const Type* arrayy, size_t size, unsigned rep) : Sound<Type, M>(size), arr(nullptr), rep(rep)
	{
		arr = new Type[size];
		for (size_t i = 0; i < size; ++i)
		{
			if ((arrayy[i] > 0 && arrayy[i] > M) || (arrayy[i] < 0 && arrayy[i] * -1 > M))
			{
				delete[] arr;
				arr = nullptr;
				throw std::invalid_argument("Sample out of the range");
			}
			arr[i] = arrayy[i];
		}
	}
	Periodical(const Periodical<Type, M>& other) : Sound<Type, M>(other.duration), arr(nullptr), rep(other.rep)
	{
		arr = new Type[other.duration];
		for (size_t i = 0; i < other.duration; ++i)
		{
			arr[i] = other.arr[i];
		}
	}
	Periodical<Type,M>& operator=(const Periodical<Type, M>& other)
	{
		if (this == &other)
			return *this;

		Type* temp = new Type[other.duration];
		for (size_t i = 0; i < other.duration; ++i)
		{
			temp[i] = other.arr[i];
		}
		delete[] arr;
		arr = temp;
		rep = other.rep;
		Sound<Type,M>duration = other.duration;

		return *this;
	}
	~Periodical()
	{
		delete[] arr;
		arr = nullptr;
	}

	virtual Type operator[](size_t index)const override
	{
		if (index >= Sound<Type, M>::duration * rep)
			throw std::invalid_argument("Invalid index");
		return arr[index% Sound<Type, M>::duration];
	}

	virtual Sound<Type,M>* clone()const override
	{
		return new Periodical(*this);
	}

	virtual size_t getSize()const override
	{
		return this->getDuration() * rep;
	}

private:
	Type* arr;
	unsigned rep;
};