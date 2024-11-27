#pragma once
#include <vector>
class depthDecision
{
private:
	int maxValue=-1;
	const int minDepth = 0;
	double p = 0.2;
	double sigma = 150.;
	std::vector<int> table;
	double calcx(int difV);
public:
	void setMaxValue(int maxValue);
	void init();
	int getDepth(int kingDepth,int diffirenceOfValue);
};

