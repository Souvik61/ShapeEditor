#include "Helpers.h"

float Helper::map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
	return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}
