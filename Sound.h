#pragma once
#include <iostream>
template <typename Type, size_t M>
class Sound
{
public:
	Sound(size_t duration) : duration(duration) {}
	virtual ~Sound() = default;
	virtual Type operator[](size_t)const = 0;
	virtual Sound<Type,M>* clone()const = 0;

	virtual size_t getSize() const
	{
		return duration;
	}

	size_t getDuration() const
	{
		return duration;
	}

protected:
	size_t duration;
//private:
//	const unsigned range = M;
};
