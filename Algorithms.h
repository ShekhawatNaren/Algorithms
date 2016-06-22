#pragma once
using namespace std;
namespace MyAlgos {
	template<typename RandomAccessIterator>
	RandomAccessIterator randomized_partition(RandomAccessIterator _First, RandomAccessIterator _Last) {
		size_t distance = _Last - _First;
		RandomAccessIterator randomIter = _Last;
		if (distance <= 0)
			return randomIter;
		else {
			randomIter = rand() % distance + _First;
		}
		std::swap(*randomIter, *_Last);
		
		RandomAccessIterator smallIter = _First;
		for (; _First <= _Last-1; ++_First) {
			if (*_First <= *_Last) {
				std::swap(*smallIter, *_First);
				++smallIter;
			}
		}
		std::swap(*smallIter, *_Last);
		return smallIter;
	}

	/*
	Takes first and last iterator of the container and sorts the data for [first,last] (inclusive) range
	*/
	template<typename RandomAccessIterator>
	void qsort(RandomAccessIterator _First, RandomAccessIterator _Last) {
		if (_First < _Last) {
			RandomAccessIterator pIter = randomized_partition(_First, _Last);
			if(pIter>_First)
				qsort(_First, --pIter);
			if(pIter<_Last)
				qsort(++pIter, _Last);
		}
	}

	/*
	Takes first and last iterator of the container and finds the nth(index starts at 0th) smallest
	element in range [first,last] (inclusive)
	*/
	template<typename RandomAccessIterator>
	RandomAccessIterator nth_element(RandomAccessIterator _First, RandomAccessIterator _Last, size_t n) {
		if ((_Last - _First) < n)
			return _Last;

		RandomAccessIterator pIter = randomized_partition(_First, _Last);
		if (pIter == _First + n) {
			return pIter;
		}
		else if (pIter < _First + n) {
			return MyAlgos::nth_element(pIter + 1, _Last, n - (pIter - _First) - 1);
		}
		else {
			return MyAlgos::nth_element(_First, pIter - 1, n);
		}
	}
}
