#pragma once
#include "Sound.h"
#include <fstream>

template <typename Type, size_t M>
class Filed : public Sound<Type, M>
{
public:
	Filed(const char* file) : Sound<Type,M>(0), arr(nullptr)
	{
		std::ifstream reader(file, std::ios::binary);
		if (!reader)
			throw std::invalid_argument("Failed opening file");
		reader.seekg(0, std::ios::end);
		size_t filesize = reader.tellg();
		reader.seekg(0, std::ios::beg);
		size_t duration = filesize / sizeof(Type);
		Sound<Type, M>::duration = duration;

		arr = new Type[duration];
		Type curr = 0;
		for (size_t i = 0; i < duration && !reader.eof(); ++i)
		{
			reader.read(reinterpret_cast<char*>(&curr), sizeof(curr));
			//if (std::abs(curr) > std::abs(M))
			if ((curr > 0 && curr > M) || (curr < 0 && curr*-1 > M))
			{
				delete[] arr;
				arr = nullptr;
				throw std::invalid_argument("Sample out of the range");
			}
			arr[i] = curr;
		}
	}
	Filed(const Filed<Type, M>& other) : Sound<Type, M>(other.duration), arr(nullptr)
	{
		arr = new Type[other.duration];
		for (size_t i = 0; i < other.duration; ++i)
		{
			arr[i] = other.arr[i];
		}
	}
	Filed<Type,M>& operator=(const Filed<Type, M>& other)
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
		Sound<Type,M>::duration = other.duration;

		return *this;
	}

	~Filed()
	{
		delete[] arr;
		arr = nullptr;
	}

	virtual Type operator[](size_t index)const override
	{
		if (index >= Sound<Type,M>::duration)
			throw std::invalid_argument("Invalid index");
		return arr[index];
	}

	virtual Sound<Type,M>* clone()const override
	{
		return new Filed<Type, M>(*this);
	}

private:
	Type* arr;
};