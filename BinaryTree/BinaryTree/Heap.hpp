#pragma once
#include <vector>
#include <assert.h>
using namespace std;

template<class T, class Compare = less<T> >
class Heap
{
public:
	Heap()
	{}

	Heap(const T* array, size_t size)
	{
		assert(array);

		for (int i = 0; i< size; ++i)
		{
			_vec.push_back(array[i]);
		}

		for (int i = _vec.size()/2 - 1; i >=0; --i)
		{
			_AdjustDown(_vec, i, _vec.size());
		}
	}

	// ����һ������x����С����
	void Insert(const T& x)
	{
		_vec.push_back(x);

		if (_vec.size() > 1)
		{
			_AdjustUp(_vec, _vec.size() - 1);
		}
	}

	// ɾ���Ѷ�Ԫ��
	void Remove()
	{
		int size = _vec.size();
		assert(size > 0);

		swap(_vec[0], _vec[size - 1]);
		_vec.pop_back();

		if (_vec.size() > 1)
		{
			_AdjustDown(_vec, 0, _vec.size());
		}
	}

	const T& GetHeapTop()
	{
		return _vec[0];
	}

	// �����ڵ����µ�����С�Ѿ�����
	void _AdjustDown(vector<T>& vec, int root, int size)
	{
		// 1.childָ�����ӽڵ�
		int child = root * 2 + 1;
		while (child < size)
		{
			// 2.childָ�����Һ�����С�Ľڵ�
			if (child + 1 < size && Compare()(vec[child + 1], vec[child]))
			{
				++child;
			}

			// 3.��childС�ڸ��ڵ㣬�򽻻�child��root�ڵ㣬���������µ���
			if (Compare()(vec[child], vec[root]))
			{
				swap(vec[child], vec[root]);
				root = child;
				child = root*2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	// һ���ڵ����ϵ�����С�Ѿ���˵����
	void _AdjustUp(vector<T>& vec, int pos)
	{
		// 1.parentָ�򸸽ڵ�
		int child = pos;
		int parent = (child - 1) / 2;
		while(parent >= 0)
		{
			// 2.��childС�ڸ��ڵ㣬�򽻻����ӽڵ㣬���������ϵ�����ֱ�����ڵ�
			if (Compare()(vec[child], vec[parent]))
			//if (vec[child] < vec[parent])
			{
				swap(vec[child], vec[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	// �ж��Ƿ�Ϊ��
	bool Empty()
	{
		return _vec.empty();
	}

private:
	vector<T> _vec;
};