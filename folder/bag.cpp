#include "bag.h"

bag::bag(int maxInitial, int valueInitial, int weightInitial)
{
	bagMax = maxInitial;
	bagValue = valueInitial;
	bagWeight = weightInitial;
}

void bag::setBagMax(int max)
{
	bagMax = max;
}

void bag::setBagValue(int value)
{
	bagValue = value;
}

void bag::setBagWeight(int weight)
{
	bagWeight = weight;
}
