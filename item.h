#ifndef ITEM_H
#define ITEM_H

class item
{
	private:
		float weight;
		float value;
	public:
		item(float initial_w = 0.0, float initial_v = 0.0);
		float getW() const { return weight; };
		float getV() const { return value; };
		void setW(float w);
		void setV(float v);
};

#include "item.cpp"
#endif 