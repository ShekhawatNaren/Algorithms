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
		size_t nElem = 0;
		//Partition the container around the partition element
		RandomAccessIterator smallIter = _First;
		for (; _First <= _Last-1; ++_First) {
			if (*_First <= *_Last) {
				//Handle the case when elements are all same to avoid n-1,1 split and make it n/2 split
				if (*_First == *_Last) {
					nElem++;
				}
				std::swap(*smallIter, *_First);
				++smallIter;
			}
		}
		if (nElem == distance)
			smallIter = _Last - (distance / 2);
		else
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

	//The container should have a bidirectional iterator
	//Binary function that accepts two elements in the range as arguments, and returns a value convertible to bool. 
	//The value returned indicates whether the element passed as first argument is considered to go 
	//before the second in the specific strict weak ordering
	template<typename BidirectionalIterator, typename Comparator>
	void insertion_sort(BidirectionalIterator start, BidirectionalIterator end, Comparator compare) {
		BidirectionalIterator current = start + 1;
		while (current != end) {
			BidirectionalIterator temp = current;
			while (current != start && compare(*(current - 1), *current) == 1) {
				std::swap(*(current - 1), *current);
				--current;
			}
			//move current to next element
			current = temp + 1;
		}
	}
}
