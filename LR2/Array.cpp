#include "Array.h"

template<typename T>
Array<T>::Array()
{
	std::cout << std::format("Default constructor with no arguments\n");
	items = (T*)malloc(sizeof(T) * 16);
	_size = 16;
}

template<typename T>
Array<T>::Array(size_t size)
{
	std::cout << std::format("Default constructor with {} size\n",size);
	items = (T*)(malloc(sizeof(T) * size));
	std::cout << items << std::endl;
	_size = size;

}

template<typename T>
Array<T>::~Array()
{
	std::cout << std::format(  "Default destructor\n");
	for (size_t i = 0; i < lastitem; i++)
		items[i].~T();
	free(items);
	_size = 0;
	lastitem = 0;
}

template<typename T>
int Array<T>::insert(const T& value)
{
	if (lastitem == _size) {
		expand();
	}
	std::cout << std::format( "Insert func without index\n" );
	new (items+(lastitem++)) T(value);
	return 0;
}

template<typename T>
void Array<T>::expand() {
	std::cout << std::format("Expand array\n");
	_size = std::max(lastitem, _size * 2);
	T* newData = (T*)(malloc(_size * sizeof(T)));
	std::cout << _size << std::endl;

	if (!newData) /
	{
		throw std::bad_alloc(); 
	}

	for (int i = 0; i < lastitem; ++i)
	{
		new (newData+i) T(items[i]); 
		items[i].~T();
	}
	free(items);

	items = newData;
}

template<typename T>
int Array<T>::insert(int index, const T& value)
{
	if (lastitem == _size) {
		expand();
	}
	std::cout << std::format( "Insert func w index {}\n",index );
	if (index <= _size && index > 0)
		new (items+index) T(value);
	lastitem++;
	return 0;
}

template<typename T>
void Array<T>::remove(int index)

{
	std::cout << std::format("Remove func w index {}\n",index);
	for (int i = index; i < _size; i++)
		items[i] = items[i + 1];
	lastitem--;
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
	std::cout << std::format("Const operator [] \n");
	return items[index];
}

template<typename T>
T& Array<T>::operator[](int index)
{
	std::cout << std::format( "Operator [] \n" );
	return items[index];
}

template<typename T>
int Array<T>::size() const
{
	std::cout << std::format( "Operator size()\n" );
	return _size;
}

