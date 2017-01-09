#pragma once

#include "Utils.h"
#include <string>
#include <cmath>
#include <functional>


template<typename T>
class MinHeap
{
private:
	std::function<bool(T, T)> comp;
	T* _heap = new T[16];
	int _heapLen;

public:
	MinHeap(std::function<bool(T, T)> comp)
	{
		InitializeInstanceFields();
		this->comp = comp;
	}

	void ConstructHeap(T heap[])
	{
		_heapLen = 0;
		Expand(sizeof(heap) / sizeof(heap[0]));
		std:memcpy(_heap, heap, sizeof(heap));
		_heapLen = sizeof(heap) / sizeof(heap[0]);
		for (int i = static_cast<int>(floor(static_cast<float>((_heapLen - 1) / 2))); i >= 0; --i)
		{
			MinHeapify(i);
		}
	}

	// O(n)
	MinHeap(T heap[], std::function<bool(T, T)> comp)
	{
		InitializeInstanceFields();
		this->comp = comp;
		ConstructHeap(heap);
	}

	// O(log(n))
	void Expand(int len)
	{
		if (len < sizeof(_heap) / sizeof(_heap[0]))
		{
			return;
		}
		int heapLen = sizeof(_heap) / sizeof(_heap[0]);
		while (len > heapLen)
		{
			heapLen *= 2;
		}

		T *oldHeap = _heap;
		_heap = new T[heapLen];
		std::memcpy(_heap, oldHeap, sizeof(oldHeap));

		delete[] oldHeap;
	}

	// O(log(n))
	void Insert(T element)
	{
		Expand(_heapLen + 1);
		_heap[_heapLen] = element;
		_heapLen += 1;
		int child = _heapLen - 1;
		int parent = static_cast<int>(std::floor(static_cast<float>((_heapLen - 1) / 2)));
		while (child != 0)
		{
			if (!comp(_heap[parent], _heap[child]))
			{
				Swap(parent, child);
			}
			else
			{
				break;
			}
			child = parent;
			parent = static_cast<int>(floor(static_cast<float>((parent - 1) / 2)));
		}
	}

	const int &getHeapLen() const
	{
		return _heapLen;
	}

	// O(log(n))
	T ExtractMin()
	{
		T min = _heap[0];
		Swap(0, _heapLen - 1);
		_heapLen -= 1;
		MinHeapify(0);
		return min;
	}

	void Heapify()
	{
		MinHeapify(0);
	}

private:
	void MinHeapify(int i)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int smallest = i;
		if (left < _heapLen && comp(_heap[left], _heap[smallest]))
		{
			smallest = left;
		}
		if (right < _heapLen && comp(_heap[right], _heap[smallest]))
		{
			smallest = right;
		}
		if (smallest != i)
		{
			Swap(i, smallest);
			MinHeapify(smallest);
		}
	}

	void Swap(int i, int j)
	{
		T tmp = _heap[i];
		_heap[i] = _heap[j];
		_heap[j] = tmp;
	}

public:
	void Print()
	{
		for (int i = 0; i < _heapLen; ++i)
		{
			Print(i);
		}
	}

private:
	void Print(int i)
	{
		if (i >= _heapLen)
		{
			return;
		}
		int level = 0;
		int j = i;
		while (j > 0)
		{
			j = (j - 1) / 2;
			level += 1;
		}
		std::string log = std::string("level ") + std::to_string(level) + std::string(": ") + _heap[i];
		if (2 * i + 1 < _heapLen)
		{
			log += std::string(" -> ") + _heap[2 * i + 1];
		}
		if (2 * i + 2 < _heapLen)
		{
			log += std::string(", ") + _heap[2 * i + 2];
		}
		Utils::Log(log);
	}

private:
	void InitializeInstanceFields()
	{
		_heapLen = 0;
	}
};
