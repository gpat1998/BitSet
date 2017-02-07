#pragma
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class Bitset
{
public:
    static const long MAX_BITSET_SIZE = 1000 * 1000 * 1000;
    static const long MIN_BITSET_SIZE = 0;
    static const long DEFAULT_BITSET_SIZE = 16;
    
private:
    unsigned char *bits;
    long bitsetCardinality;
    long bitsetSize;
    long numberOfElementsInCharArray;
    
    long lastElementAccessed;
    
public:
    Bitset(const long size = DEFAULT_BITSET_SIZE);
    ~Bitset();
    bool setBit(const long index, bool value);
    bool operator[](const long index) const;
    long cardinality() const { return bitsetCardinality; }
    long size() const { return bitsetSize; }
    bool resetAllBits();
    string toString() const;
    
    Bitset operator!();
    Bitset operator&(const Bitset &other);
    Bitset operator|(const Bitset &other);
    
private:
    bool setSize(const long size = DEFAULT_BITSET_SIZE);
    bool getBit(const long index) const;
};


Bitset::Bitset(const long size)
{
    bitsetCardinality = 0;
    lastElementAccessed = -1;
    if (!setSize(size))
        setSize(DEFAULT_BITSET_SIZE);
    bits = new unsigned char[size];
    resetAllBits();
}

Bitset::~Bitset()
{
    delete[] bits;
}

bool Bitset::setBit(const long index, bool value)
{
    if (index < MIN_BITSET_SIZE || index > MAX_BITSET_SIZE)
        return false;
    long charNum = index / 8;
    int mask = 1 << (index % 8);
    if (value){
        if (!getBit(index))
        {
            bitsetCardinality++;
            bits[charNum] += mask;
        }
    }
    else
    {
        if(getBit(index))
        {
            bitsetCardinality--;
            bits[charNum] -= mask;
        }
    }
    return true;
}

bool Bitset::operator[](const long index) const
{
    return getBit(index);
}

bool Bitset::resetAllBits()
{
    for (int i = 0; i < numberOfElementsInCharArray; i++)
        bits[i] = 0;
    
    return true;
}

string Bitset::toString() const
{
    ostringstream w;
    
    for (long i = bitsetSize - 1; i >= 0; i--)
    {
        w << "" << (getBit(i) ? 1 : 0);
        
        if (i % 8 == 0)
        {
            w << " ";
        }
    
    }
    
    return w.str();
}

Bitset Bitset::operator!()
{
    Bitset bs(bitsetSize);
    for (long i = 0; i < numberOfElementsInCharArray; i++)
    {
        bs.bits[i] = 255 - bits[i];
    }
    return bs;
}

Bitset Bitset::operator&(const Bitset &other)
{
    Bitset bs(bitsetSize);
    
    for (long i = 0; i <bitsetSize; i++)
    {
        bs.setBit(i, (getBit(i) == other.getBit(i) && getBit(i)));
    }
    return bs;
}

Bitset Bitset::operator|(const Bitset &other)
{
    Bitset bs(bitsetSize);
    
    for (long i = 0; i <bitsetSize; i++)
    {
        bs.setBit(i, (getBit(i) || other.getBit(i)));
    }
    return bs;
}

bool Bitset::setSize(const long size)
{
    if (size > MAX_BITSET_SIZE || size < MIN_BITSET_SIZE)
        return false;
    
    bitsetSize = size;
    long bitsToBytes = size / 8;
    numberOfElementsInCharArray = bitsToBytes + (((size % 8) == 0) ? 0 : 1);
    
    return true;
}

bool Bitset::getBit(const long index) const
{
    long charNum = index / 8;
    int mask = 1 << (index % 8);
    return (bits[charNum] & mask) != 0;
}

int main()
{
    Bitset bits(80);
    Bitset bitsto(80);
    bits.setBit(7, true);
    bits.setBit(4, true);
    bitsto.setBit(4, true);
    bitsto.setBit(42, true);
    cout << "Bits1" << "\n\n" << bits.toString() << "\n" << endl;
    cout << "NotBits1" << "\n\n" << (!bits).toString() << "\n" << endl;
    cout << "Bits1AndBits2" << "\n\n" << (bits & bitsto).toString() << "\n" << endl;
    cout << "Bits1OrBits2" << "\n\n" << (bits | bitsto).toString() << "\n" << endl;
    
    return 0;
}
