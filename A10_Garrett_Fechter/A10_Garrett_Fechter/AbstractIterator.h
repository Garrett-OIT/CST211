#ifndef ABS_ITER_H
#define ABS_ITER_H 

template <typename T>
class AbstractIterator
{
public:
	virtual void MoveNext() = 0;
	virtual void Reset() = 0;
	virtual bool isDone() = 0;
	virtual T GetCurrent() = 0;
};

#endif