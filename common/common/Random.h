#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "BaseType.h"
#include "BaseLib.h"

class Random
{
public:
	//生成一个随机数，范围[0, 1]
	static tfloat32 Gen(void);

	//生成一个随机数，范围[nMin, nMax)，注意取值区间，nMax是取不到的
	static tint32	Gen(tint32 nMin, tint32 nMax);

	//对一个概率采样一次
	//例如nNumerator = 20 nDenominator = 100，就是判断一次20%的概率
	static bool		Sampling(tint32 nNumerator, tint32 nDenominator);
};

#endif
