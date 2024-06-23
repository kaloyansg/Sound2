#include <iostream>
#include <fstream>
#include "Sound.h"
#include "Filed.h"
#include "Periodical.h"
#include "Mix.h"
#include "Effect.h"

template<typename Type>
class DoubleUp
{
public:
	Type operator()(const Type& x) const
	{
		return x * 2;
	}
};

template <typename Type, size_t M>
void save(const char* fileName, const Sound<Type,M>& sound)
{
	std::ofstream writer(fileName, std::ios::binary);
	if (!writer)
		throw std::invalid_argument("File not loaded");

	size_t size = sound.getSize();
	Type curr;
	for (size_t i = 0; i < size; ++i)
	{
		curr = sound[i];
		writer.write(reinterpret_cast<const char*>(&curr), sizeof(Type));
	}
	writer.close();
}

int main()
{
    /*std::cout << "Hello World!\n";
    std::ofstream file("file.dat", std::ios::binary);
	for (size_t i = 0; i < 5; i++)
	{
		file.write(reinterpret_cast<const char*>(&i), sizeof(i));
	}
	file.close();*/

	Filed<size_t, 7> f("file.dat");
	Filed<size_t, 7> f2(f);

	size_t arr[] = { 0,1 };
	Periodical<size_t, 7> p(arr, 2, 3);
	Periodical<size_t, 7> p2(p);

	const Sound<size_t, 7>* sounds[4]{nullptr};
	sounds[0] = &f;
	sounds[1] = &f2;
	sounds[2] = &p;
	sounds[3] = &p2;

	size_t size = 4;
	//Mix<size_t, 7> m(sounds, size);
	Mix<size_t, 7> m(sounds, size);
	DoubleUp<size_t> functor;
	Effect<size_t, 7, DoubleUp<size_t>> e(m, functor);

	save("file2.dat", e);

	Filed<size_t, 7> ff("file2.dat");

	try
	{
		for (size_t i = 0; i < 7; i++)
		{
			if (i == 3)
				int a = 5;
			std::cout << e[i] << " " << ff[i] << '\n';
		}
	}
	catch (std::invalid_argument err)
	{
		std::cout << err.what();
	}
	
}