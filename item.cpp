#include "item.h"

item::item(int initial_w, int initial_v)
{
	weight = initial_w;
	value = initial_v;
}

void item::setW(int w)
{
	weight = w;
}

void item::setV(int v)
{
	value = v;
}