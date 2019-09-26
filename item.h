#ifndef ITEM_H
#define ITEM_H

class item
{
	private:
		int weight;
		int value;
	public:
		item(int initial_w = 0.0, int initial_v = 0.0);
		int getW() const { return weight; };
		int getV() const { return value; };
		void setW(int w);
		void setV(int v);
};

//#include "item.cpp"
#endif 