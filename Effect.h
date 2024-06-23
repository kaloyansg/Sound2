#pragma once
#include "Sound.h"
template<typename T, size_t M, typename Functor>
class Effect : public Sound<T,M>
{
public:
	Effect(const Sound<T, M>& snd, const Functor& compr) : Sound<T, M>(snd.getDuration()), comperator(&compr)
	{
		sound = snd.clone();
	}
	Effect(const Effect<T, M, Functor>& other) : Sound<T, M>(other.sound->getDuration()), comperator(other.comperator)
	{
		sound = other.sound->clone();
	}
	Effect<T, M, Functor> operator=(const Effect<T, M, Functor>& other)
	{
		Sound<T, M>* temp = other.sound->clone();
		delete sound;
		sound = temp;
		comperator = other.comperator;
	}
	~Effect()
	{
		delete sound;
	}

	virtual T operator[](size_t index)const override
	{
		return (*comperator)((*sound)[index]);
	}

	virtual Sound<T,M>* clone()const override
	{
		return new Effect(*this);
	}

private:
	Sound<T, M>* sound;
	const Functor* comperator;
};