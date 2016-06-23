#pragma once
using namespace std;
namespace MyAlgos {
	template<typename RandomAccessIterator>
	RandomAccessIterator randomized_partition(RandomAccessIterator _First, RandomAccessIterator _Last) {
		//Find the random partition element
		size_t distance = _Last - _First;
		RandomAccessIterator randomIter = _Last;
		if (distance <= 0)
			return randomIter;
		else {
			randomIter = rand() % distance + _First;
		}
		std::swap(*randomIter, *_Last);
		
		//Partition the container around the partition element
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
	Inplace algorithm
	*/
	template<typename RandomAccessIterator>
	void qsort(RandomAccessIterator _First, RandomAccessIterator _Last) {
		while (_First < _Last) {
			RandomAccessIterator pIter = randomized_partition(_First, _Last);
			if (pIter>_First)
				qsort(_First, pIter - 1);

			_First = pIter + 1; //tail recursive
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

	/*
	insertion sort algorithm (in-place)
	*/
	template<typename BidirectionalIterator>
	void insertion_sort(BidirectionalIterator _First, BidirectionalIterator _Last) {
		if (_First == _Last)
			return;
		BidirectionalIterator right = std::next(_First);
		for (; right <= _Last; ++right) {
			BidirectionalIterator left = std::prev(right);
			auto key = *right;
			bool flag = true;
			while( flag && left >= _First && *left > key) {
				*(left + 1) = *left;
				if (left != _First)
					--left;
				else
					flag = false;
			}
			if (flag)
				*(left + 1) = key;
			else
				*left = key;
		}
	}
}
