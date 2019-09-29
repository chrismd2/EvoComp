#ifndef BAG_H
#define BAG_H

class bag
{
private:
	int bagMax;
	int bagValue;
	int bagWeight;
public:
	bag(int maxInitial = 0, int valueInitial = 0, int weightInitial = 0);
	int getBagMax() const { return bagMax; };
	void setBagMax(int max);
	int getBagValue() const { return bagValue; };
	void setBagValue(int value);
	int getBagWeight() const { return bagWeight; };
	void setBagWeight(int weight);
};


#endif
