#ifndef LEONARDOCONFIGURATION_H
#define LEONARDOCONFIGURATION_H

class LeonardoConfiguration
{
public:
	double x;
	double y;
	double a;
	double s1;
	double s2;
	double s3;
	double e1;
	double e2;
	double w1;
	double w2;
	
public:
	LeonardoConfiguration(double x = 0, double y = 0, double a = 0,
		double s1 = 0, double s2 = 0, double s3 = 0, double e1 = 0, double e2 = 0,
		double w1 = 0, double w2 = 0);
	virtual ~LeonardoConfiguration();
};

#endif //LEONARDOCONFIGURATION_H
