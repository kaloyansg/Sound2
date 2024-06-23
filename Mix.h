#pragma once
#include "Sound.h"
template <typename Type, size_t M>
class Mix : public Sound<Type, M>
{
public:
	Mix(const Sound<Type, M>** arr, size_t size) : Sound<Type, M>(0), numberOfSound(size), sounds(nullptr)
	{
		size_t maxDur = 0;
		sounds = new Sound<Type, M>* [size] {nullptr};
		try
		{
			for (size_t i = 0; i < size; ++i)
			{
				if (maxDur < arr[i]->getDuration())
					maxDur = arr[i]->getDuration();
				sounds[i] = arr[i]->clone();
			}
		}
		catch (...)
		{
			for (size_t i = 0; i < size; i++)
			{
				delete sounds[i];
				delete[] sounds;
				throw;
			}
		}
		Sound<Type, M>::duration = maxDur;
	}
	Mix(const Mix<Type, M>& other) : Sound<Type, M>(other.duration), numberOfSound(other.numberOfSound), sounds(nullptr)
	{
		sounds = new Sound<Type, M>* [numberOfSound] {nullptr};
		try
		{
			for (size_t i = 0; i < numberOfSound; ++i)
			{
				sounds[i] = other.sounds[i]->clone();
			}
		}
		catch (...)
		{
			for (size_t i = 0; i < numberOfSound; ++i)
			{
				delete sounds[i];
			}
			delete[] sounds;
			throw;
		}
	}
	Mix<Type,M>& operator=(const Mix<Type, M>& other)
	{
		if (this == &other)
			return *this;

		Sound<Type,M>** temp = new Sound<Type, M>* [other.numberOfSound] {nullptr};
		try
		{
			for (size_t i = 0; i < other.numberOfSound; ++i)
			{
				temp[i] = other.sounds[i]->clone();
			}
		}
		catch (...)
		{
			for (size_t i = 0; i < other.numberOfSound; ++i)
			{
				delete temp[i];
			}
			delete[] temp;
			throw;
		}

		for (size_t i = 0; i < numberOfSound; ++i)
		{
			delete sounds[i];
		}
		delete[] sounds;
		sounds = temp;
		numberOfSound = other.numberOfSound;
		Sound<Type, M>::duration = other.duration;

		return *this;
	}
	~Mix()
	{
		for (size_t i = 0; i < numberOfSound; ++i)
		{
			delete sounds[i];
		}
		delete[] sounds;
	}

	virtual Type operator[](size_t index) const override
	{
		if (index > Sound<Type, M>::duration)
			throw std::invalid_argument("Invalid index");
		Type sum = 0;
		for (size_t i = 0; i < numberOfSound; ++i)
		{
			try
			{
				sum += (*(sounds[i]))[index];
			}
			catch (...)
			{

			}
		}
		sum /= numberOfSound;
		return sum;
	}

	virtual Sound<Type, M>* clone() const override
	{
		return new Mix<Type, M>(*this);
	}

private:
	Sound<Type, M>** sounds;
	size_t numberOfSound;
};