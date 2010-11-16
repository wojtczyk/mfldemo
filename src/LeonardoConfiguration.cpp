#include "LeonardoConfiguration.h"

LeonardoConfiguration::LeonardoConfiguration(double x, double y, double a,
	double s1, double s2, double s3, double e1, double e2,
	double w1, double w2)
{
	this->x = x;
	this->y = y;
	this->a = a;
	this->s1 = s1;
	this->s2 = s2;
	this->s3 = s3;
	this->e1 = e1;
	this->e2 = e2;
	this->w1 = w1;
	this->w2 = w2;
}

LeonardoConfiguration::~LeonardoConfiguration()
{
}
