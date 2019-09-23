#include "item.h"

item::item(float initial_w, float initial_v)
{
	weight = initial_w;
	value = initial_v;
}

void item::setW(float w)
{
	weight = w;
}

void item::setV(float v)
{
	value = v;
}