#include "Random.h"

tfloat32 Random::Gen(void)
{
	return (tfloat32)rand()/(tfloat32)RAND_MAX;
}

tint32 Random::Gen(tint32 nMin, tint32 nMax)
{
	if (nMin < nMax)
	{
		tint32 nRet = (tint32)((tfloat32)(nMax - nMin)*Random::Gen()) + nMin;
		if (nRet < nMin)
		{
			nRet = nMin;
		}

		if (nRet>= nMax)
		{
			nRet = nMax - 1;
		}
		return nRet;
	}
	else
	{
		return nMin;
	}
}

bool Random::Sampling(tint32 nNumerator, tint32 nDenominator)
{
	tint32 nRandom = Random::Gen(0,nDenominator);
	if (nRandom < nNumerator)
	{
		return true;
	}
	else
	{
		return false;
	}
}