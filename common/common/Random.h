#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "BaseType.h"
#include "BaseLib.h"

class Random
{
public:
	//����һ�����������Χ[0, 1]
	static tfloat32 Gen(void);

	//����һ�����������Χ[nMin, nMax)��ע��ȡֵ���䣬nMax��ȡ������
	static tint32	Gen(tint32 nMin, tint32 nMax);

	//��һ�����ʲ���һ��
	//����nNumerator = 20 nDenominator = 100�������ж�һ��20%�ĸ���
	static bool		Sampling(tint32 nNumerator, tint32 nDenominator);
};

#endif
