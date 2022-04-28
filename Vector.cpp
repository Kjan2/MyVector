#include "Vector.h"
#include <stdio.h>
using Value = double;

Vector::Vector(const Value* rawArray, const size_t size, float coef)
{
    _data = new Value[size];

    for (size_t i = 0; i < size; i++)
    {
        *_data = *rawArray;
        _data++;
        rawArray++;
    }

    _size = size;
    _capacity = _size;
    _multiplicativeCoef = coef;
}

Vector::Vector(const Vector& other)
{
    this->_data = new Value[other._capacity];

    for (size_t i = 0; i < other._size; i++)
    {
        this->_data[i] = other._data[i];
    }
    
    this->_size = other._size;
    this->_capacity = other._capacity;
    this->_multiplicativeCoef = other._multiplicativeCoef;
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->_data = new Value[other._capacity];

    for (size_t i = 0; i < other._size; i++)
    {
        this->_data[i] = other._data[i];
    }

    this->_size = other._size;
    this->_capacity = other._capacity;
    this->_multiplicativeCoef = other._multiplicativeCoef;
    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
    this->_data = other._data;

    other._data = nullptr;
        
    this->_size = other._size;
    other._size = 0;

    this->_capacity = other._capacity;
    other._capacity = 1;

    this->_multiplicativeCoef = other._multiplicativeCoef;
    other._multiplicativeCoef = 2.0f;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if(this != &other)
    {
        delete[] this->_data;
        this->_data = other._data;
        other._data = nullptr;
        
        this->_size = other._size;
        other._size = 0;
        this->_capacity = other._capacity;
        other._capacity = 1;

        this->_multiplicativeCoef = other._multiplicativeCoef;
        other._multiplicativeCoef = 2.0f;
    }

    return *this;
}

Vector::~Vector()
{
    delete[] _data;
}

Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr)
{
}

Value& Vector::Iterator::operator*()
{
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const
{
    return *_ptr;
}

Value* Vector::Iterator::operator->()
{
    return _ptr;
}

const Value* Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{
    ++_ptr;
    return *this;   
}

Vector::Iterator Vector::Iterator::operator++(int num)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const
{
    return (this->_ptr == other._ptr);
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const
{
    return (this->_ptr != other._ptr);
}

Vector::Iterator Vector::begin()
{
    Iterator begin(_data);
    return begin;
}

Vector::Iterator Vector::end()
{
    if (_size != 0)
    {
        Iterator end(_data + _size - 1);
        return end;
    }

    Iterator end(_data);
    return end;
}

void Vector::pushBack(const Value& value)
{
    _size++;
    if ((_size > _capacity) || (_data == nullptr))
    {
        _capacity *= _multiplicativeCoef;
        Value* newData = new Value[_capacity];
        
        for (size_t i = 0; i < (_size - 1); i++)
        {
            newData[i] = _data[i];
        }

        newData[_size - 1] = value;

        delete[] _data;

        _data = newData;

        newData = nullptr;
    }

    else
    {
        _data[_size - 1] = value;     
    }  
}

void Vector::pushFront(const Value& value)
{
    _size++;

    if ((_size > _capacity) || (_data == nullptr))
    {
        _capacity *= _multiplicativeCoef;
    }

    Value* newData = new Value[_capacity];
    
    for (size_t i = 0; i < (_size - 1); i++)
    {
        newData[i + 1] = _data[i];
    }

    newData[0] = value;

    delete[] _data;

    _data = newData;

    newData = nullptr;
}

void Vector::insert(const Value& value, size_t pos)
{
    if ((pos >= _size) ||  (_data == nullptr))
    {
        return;
    }
    
    _size++;

    if (_size > _capacity)
    {
        _capacity *= _multiplicativeCoef;

        Value* newData = new Value[_capacity];

        for (size_t i = 0; i < (pos + 1); i++)
        {
            newData[i] = _data[i];
        }
        
        for (size_t i = 1; i < (_size - pos + 1); i++)
        {
            newData[_size - i] = _data[_size - i - 1];
        }

        newData[pos] = value;

        delete[] _data; 
        _data = newData;
        newData = nullptr; 
    }

    else
    {
        for (size_t i = 2; i < (_size - pos + 1); i++)
        {
            _data[_size - i + 1] = _data[_size - i];
        }
        _data[pos] = value;
    }
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    int allocFlag = 0;

    _size += size;

    while (_size > _capacity)
    {
        _capacity *= _multiplicativeCoef;
        int allocFlag = 1;
    }

    if (!allocFlag)
    {
        Value* newData = new Value[_capacity];

        for (size_t i = 0; i < (pos + 1); i++)
        {
            newData[i] = _data[i];
        }
        
        for (size_t i = 1; i < (_size - pos - size  + 1); i++)
        {
            newData[_size - i] = _data[_size - i - size];
        }

        for (size_t i = pos; i < (pos + size); i++)
        {
            newData[i] = values[i];
        }

        delete[] _data; 
        _data = newData;
        newData = nullptr;
    }

    else
    {
        for (size_t i = 2; i < (_size - pos + size + 1); i++)
        {
            _data[_size - i + 1] = _data[_size - i];
        }

        for (size_t i = 0; i < size; i++)
        {
            _data[i] = values[i];
        }
    }
}

void Vector::insert(const Vector& vector, size_t pos)
{
    int allocFlag = 0;

    _size += vector.size();

    while (_size > _capacity)
    {
        _capacity *= _multiplicativeCoef;
        int allocFlag = 1;
    }

    if (!allocFlag)
    {
        Value* newData = new Value[_capacity];

        for (size_t i = 0; i < (pos + 1); i++)
        {
            newData[i] = _data[i];
        }
        
        for (size_t i = 1; i < (_size - pos - vector.size() + 1); i++)
        {
            newData[_size - i] = _data[_size - i - vector.size()];
        }

        for (size_t i = pos; i < (pos + vector.size()); i++)
        {
            newData[i] = vector[i];
        }

        delete[] _data; 
        _data = newData;
        newData = nullptr;
    }

    else
    {
        for (size_t i = 2; i < (_size - pos + vector.size() + 1); i++)
        {
            _data[_size - i + 1] = _data[_size - i];
        }

        for (size_t i = 0; i < vector.size(); i++)
        {
            _data[i] = vector[i];
        }
    }

}

void Vector::popBack()
{
    _size--;
}

void Vector::popFront()
{
    for (size_t i = 0; i < (_size - 1); i++)
    {
        _data[i] = _data[i + 1];
    }
    _size--;
}

void Vector::erase(size_t pos, size_t count)
{
    if (pos + count > _size)
    {
        count = _size - pos;
    }
    for (size_t i = 0; i < (_size - pos - count); i++)
    {   
        _data[pos + i] = _data[pos + count + i];
    }   

    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (endPos < beginPos)
    {
        return;
    }

    size_t count = _size - beginPos;

    for (size_t i = 0; i < (_size - beginPos - count); i++)
    {   
        _data[beginPos + i] = _data[beginPos + count + i];
    }   

    _size -= count;
 
}
size_t Vector::capacity() const 
{
    return _capacity;
}

size_t Vector::size() const
{
    return _size;
}

double Vector::loadFactor() const
{
    return (static_cast<double> (_size)) /( static_cast<double> (_capacity));
}

Value& Vector::operator[](size_t idx)
{
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const
{
    return _data[idx];
}

long long Vector::find(const Value& value) const
{
    for (long long i = 0; i < _size; i++)
    {
        if (_data[i] == value)
        {
            return i;
        }
    }

    return -1;
}

void Vector::reserve(size_t capacity)
{
    if (_capacity >= capacity)
    {
        return;
    }

    _capacity = capacity;

    Value* newData = new Value[_capacity];

    for (size_t i = 0; i <  _size; i++)
    {
        newData[i] = _data[i];
    }

    delete[] _data;
    _data = newData;
    newData = nullptr;
}

void Vector::shrinkToFit()
{
    if (_capacity ==  _size)
    {
        return;
    }

    _capacity = _size;

    Value* newData = new Value[_capacity];

    for (size_t i = 0; i <  _size; i++)
    {
        newData[i] = _data[i];
    }

    delete[] _data;
    _data = newData;
    newData = nullptr;
}
