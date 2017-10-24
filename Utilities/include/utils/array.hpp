#ifndef UTILS_ARRAY_HEADER_INCLUDED
#define UTILS_ARRAY_HEADER_INCLUDED

namespace utils
{
	template <class T>
	class Array {
		typedef T* Iterator;
	public:
		Array();
		Array(unsigned int size);
		Array(unsigned int size, const T&);
		Array(const Array<T>&);
		~Array();

		unsigned int capacity() const;
		unsigned int size() const;
		bool empty() const;

		Iterator begin();
		Iterator end();

		T& front();
		T& front() const;
		T& back();
		T& back() const;
		void addItem(const T& value);
		void pop_back();

		void reserve(unsigned int capacity);
		void resize(unsigned int);
		 
		T& operator[](unsigned int index);
		Array<T>& operator = (const Array<T> &);
		void clear();
	private:
		unsigned int _size;
		unsigned int _capacity;
		unsigned int Log;
		T* buffer;
	};

	template<class T>
	Array<T>::Array() {
		_capacity = 0;
		_size = 0;
		buffer = 0;
		Log = 0;
	}

	template<class T>
	Array<T>::Array(const Array<T>& o) {
		_size = o._size;
		_capacity = o._capacity;
		buffer = new T[_size];
		for (unsigned int i = 0; i < _size; i++)
			buffer[i] = o.buffer[i];
	}

	template<class T>
	Array<T>::Array(unsigned int size) {
		_size = size;
		Log = ceil(log((double)size) / log(2.0));
		_capacity = 1 << Log;
		buffer = new T[_capacity];
	}

	template<class T>
	bool Array<T>::empty() const {
		return _size == 0;
	}

	template<class T>
	Array<T>::Array(unsigned int size, const T& original) {
		_size = size;
		Log = ceil(log((double)size) / log(2.0));
		_capacity = 1 << Log;
		buffer = new T[_capacity];
		for (unsigned int i = 0; i < size; i++)
			buffer[i] = original;
	}

	template<class T>
	Array<T>& Array<T>::operator= (const Array<T>& o){
		delete[] buffer;
		_size = o._size;
		Log = o.Log;
		_capacity = o._capacity;
		buffer = new T[_capacity];
		for (unsigned int i = 0; i < _size; i++)
			buffer[i] = o.buffer[i];
		return *this;
	}

	template<class T>
	typename Array<T>::Iterator Array<T>::begin() {
		return buffer;
	}

	template<class T>
	typename Array<T>::Iterator Array<T>::end() {
		return buffer + size();
	}

	template<class T>
	T& Array<T>::front() {
		return buffer[0];
	}

	template<class T>
	T& Array<T>::front() const {
		return buffer[0];
	}

	template<class T>
	T& Array<T>::back() {
		return buffer[_size - 1];
	}

	template<class T>
	T& Array<T>::back() const {
		return buffer[_size - 1];
	}

	template<class T>
	void Array<T>::addItem(const T& value) {
		if (_size >= _capacity) {
			reserve(1 << Log);
			Log++;
		}
		buffer[_size++] = value;
	}

	template<class T>
	void Array<T>::pop_back() {
		_size--;
	}

	template<class T>
	void Array<T>::reserve(unsigned int capacity) {
		T* newBuffer = new T[capacity];

		for (unsigned int i = 0; i < _size; i++)
			newBuffer[i] = buffer[i];

		_capacity = capacity;
		delete[] buffer;
		buffer = newBuffer;
	}

	template<class T>
	unsigned int Array<T>::size() const {
		return _size;
	}

	template<class T>
	void Array<T>::resize(unsigned int size) {
		Log = ceil(log((double)size) / log(2.0));
		reserve(1 << Log);
		_size = size;
	}

	template<class T>
	T& Array<T>::operator[](unsigned int index) {
		return buffer[index];
	}

	template<class T>
	unsigned int Array<T>::capacity() const {
		return _capacity;
	}

	template<class T>
	Array<T>::~Array() {
		delete[] buffer;
	}

	template<class T>
	void Array<T>::clear() {
		_capacity = 0;
		_size = 0;
		buffer = 0;
		Log = 0;
	}
}

#endif