#include "bitset.h"
#include "bitreference.h"
#include "bitsetiterator.h"

Bitset::Bitset() : bits(0) {}

size_t Bitset::size() const {
	return BPW;
}

bool Bitset::operator[](size_t pos) const {
	return (bits & (1L << pos)) != 0;
}

BitReference Bitset::operator[](size_t pos) {
	return BitReference(bits, pos);
}


Bitset::iterator Bitset::begin() {
	BitsetIterator itr(bits, 0);
	return itr;
}

Bitset::iterator Bitset::end() {
	BitsetIterator itr(bits, BPW);
	return itr;
}