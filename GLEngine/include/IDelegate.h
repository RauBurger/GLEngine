#ifndef IDELEGATE_H
#define IDELEGATE_H

class IDelegate
{
public:
	virtual void Invoke() = 0;
};

#endif // IDELEGATE_H