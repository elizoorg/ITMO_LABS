#pragma once
#include <format>
#include <iostream>

template<typename T>
class Array final {
private:
	class dummy final {};

	using CopyArg = std::conditional_t<std::is_copy_constructible_v<T>, const Array&, dummy>;
	template <class Arg>
	using TCopyCtorEnabled = std::void_t<decltype(Arg(std::declval<Arg&>()))>;
	template <class Arg>
	using TDefaultCtorEnabled = std::void_t<decltype(Arg())>;
public:
	Array();
	Array(size_t size);
	~Array();
	int insert(const T& value);
	int insert(int index, const T& value);
	void remove(int index);
	const T& operator[](int index) const;
	T& operator[](int index);
	int size() const;
	void expand();
	Array(CopyArg sd) {
		 		items = (T*)malloc(sizeof(T) * sd._size);
		for (; _size < sd._size; ++_size)
		new(items + _size) T(sd.items[_size]);
	}
	Array &operator=(const CopyArg sd) {
		 		Array copy(sd);
		return *this = std::move(copy);
	}
	Array &operator=(Array&& toMove) noexcept {
		 		std::swap(lastitem, toMove.lastitem);
		std::swap(_size, toMove._size);
		std::swap(items, toMove.items);
		return *this;
	};
	Array(Array&& toMove) noexcept {
		 		std::swap(lastitem, toMove.lastitem);
		std::swap(_size, toMove._size);
		std::swap(items, toMove.items);
	}

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const Array<T> &);

	struct Iterator {
	private:
		friend Array;
		
		T* ptr_;	
		int direction = 1;

		Iterator(T* ptr) noexcept : ptr_(ptr) {
		};
	public:
		using difference_type = std::ptrdiff_t;
		using element_type = T;
		using pointer = element_type*;
		using reference = element_type&;


		Iterator& operator++() {
			 			++ptr_;
			return *this;
		}
		Iterator operator++(int) {
			 			Iterator copy{ *this };
			++ptr_;
			return copy;
		}
		Iterator& operator--() {
			 			--ptr_;
			return *this;
		}
		Iterator operator--(int) {
			 			Iterator copy{ *this };
			--ptr_;
			return copy;
		}
		bool operator==(const Iterator &other) const = default;
		reference operator*() const { return *ptr_; }

		void reverse() { direction *= -1; }
		const T& get() const {  		return *ptr_; }
		void next() { std::format("Iterator next() \n"); ptr_+= direction;}
		void set(const T& value) { std::format("Iterator next(0 \n"); *ptr_ = value; }
		bool hasNext() const { std::format("Iterator hasNext() {} \n",ptr_==nullptr); return ptr_ == nullptr ; }
		
	};
	struct ConstIterator final {
	private:
		Iterator it_;
	public:
		ConstIterator(const Iterator& it) noexcept : it_(it) {}
		ConstIterator(T* ptr) : it_(ptr) {};
		ConstIterator(const ConstIterator &) = default;
		ConstIterator &operator=(const ConstIterator &) = default;

		ConstIterator& operator++() { ++it_; return *this; }
		ConstIterator operator++ (int) { return it_++; }
		const T get() {  		return *it_; }
		const T& operator* () const { return *it_; }
		
		void reverse() { it_.reverse(); }
		
		
	};

	Iterator iterator(){ return Iterator(items); }
	ConstIterator iterator() const { return ConstIterator(items); }
	Iterator reverseIterator() {  	Iterator it(items + lastitem-1);
	it.reverse();
	return it;
	}
	ConstIterator reverseIterator() const {
		 		ConstIterator it(items + lastitem-1);
		it.reverse();
		return it;
	}

	Iterator begin() { return Iterator(items); }
	Iterator end() { return Iterator(items + lastitem); }
	ConstIterator cbegin() const { return ConstIterator(items); }
	ConstIterator cend() const { return ConstIterator(items + lastitem); }



	

	template <class Arg = T , class = TCopyCtorEnabled<Arg>>
	Array(std::initializer_list<T> l) : Array<T>(l.size()) {
		 		static_assert(std::is_same_v < Arg, T>, "Arguments should be default type (T)");
		 		size_t size = 0;
		for (auto it = l.begin(), end = l.end();  it != end; ++it, ++size) {
			new(items+size) T(*it);
		}
		lastitem = size;
	}
	
	


private:
	T* items = nullptr;
	int _size = 0;
	int lastitem = 0;
};

template class Array<int>;
template class Array<std::string>;

template<typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& ar)
{
	os << &ar << std::endl;
	for (int i = 0; i < ar._size; i++)
		os << ar.items[i] << " ";
	return os;
}
