#include "Array.h"

template<typename T>
Array<T>::Array()
{
	 	items = (T*)malloc(sizeof(T) * 16);
	_size = 16;
}

template<typename T>
Array<T>::Array(size_t size)
{
	 	items = (T*)(malloc(sizeof(T) * size));
	 	_size = size;

}

template<typename T>
Array<T>::~Array()
{
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
	 	new (items+(lastitem++)) T(value);
	return 0;
}

template<typename T>
void Array<T>::expand() {
	 	_size = std::max(lastitem, _size * 2);
	T* newData = (T*)(malloc(_size * sizeof(T)));
	 
	if (!newData) // Проверка на успех выделения новой памяти
	{
		throw std::bad_alloc(); // Выделяем память для массива, при неудаче выкидываем исключение bad_alloc
	}

	for (int i = 0; i < lastitem; ++i)
	{
		new (newData+i) T(items[i]); // Перенос данных из старой в новую выделенную память
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
	 	if (index <= _size && index > 0)
		new (items+index) T(value);
	lastitem++;
	return 0;
}

template<typename T>
void Array<T>::remove(int index)

{
		for (int i = index; i < _size; i++)
		items[i] = items[i + 1];
	lastitem--;
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
		return items[index];
}

template<typename T>
T& Array<T>::operator[](int index)
{
		return items[index];
}

template<typename T>
int Array<T>::size() const
{
		return _size;
}

