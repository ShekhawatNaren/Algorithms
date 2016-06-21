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
		std::swap(*(smallIter), *_Last);
		return smallIter;
	}

	template<typename RandomAccessIterator>
	void qsort(RandomAccessIterator _First, RandomAccessIterator _Last,vector<int>& v) {
		if (_First < _Last) {
			RandomAccessIterator pIter = randomized_partition(_First, _Last);
			if(pIter>_First)
				qsort(_First, pIter - 1,v);
			if(pIter<_Last)
				qsort(pIter + 1, _Last,v);
		}
	}
}
