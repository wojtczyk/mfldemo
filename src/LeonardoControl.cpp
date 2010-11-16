#include <qtimer.h>
#include "LeonardoModel.h"
#include "LeonardoControl.h"
#include <cmath>

#include <iostream>

using namespace std;

LeonardoControl::LeonardoControl() :QObject()
{
	controlTimer = new QTimer();
	connect(controlTimer, SIGNAL(timeout()), this, SLOT(timeout()));
	controlTimer->start(50, false);
};

LeonardoControl::~LeonardoControl()
{
	delete controlTimer;
};

void LeonardoControl::setModel(LeonardoModel* leonardoModel)
{
	this->leonardoModel = leonardoModel;
};

void LeonardoControl::setConfiguration(double x, double y, double a,
	double s1, double s2, double s3, double e1, double e2, double w1, double w2)
{
	this->leonardoModel->setConfiguration(x, y, a, s1, s2, s3, e1, e2, w1, w2);
	this->currentConfiguration = LeonardoConfiguration(x, y, a, s1, s2, s3, e1, e2, w1, w2);
};

void LeonardoControl::moveConfiguration(double x, double y, double a,
	double s1, double s2, double s3, double e1, double e2, double w1, double w2)
{
	LeonardoConfiguration c(x, y, a, s1, s2, s3, e1, e2, w1, w2);
	configurationList.push_back(c);
};

void LeonardoControl::timeout()
{
	const double TIMESTEP = 0.05;
	const double E_ROT = 0.1;
	const double E_TRANS = 0.1;
	double JV_MAX[7];
	const double RAD2DEG = 180.0 / M_PI;
	const double DEG2RAD = M_PI / 180.0;
	const double PT_MAX = 1 * TIMESTEP * 0.7;
	const double PR_MAX = 90 * TIMESTEP * 0.7;

	JV_MAX[0] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[1] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[2] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[3] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[4] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[5] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[6] = 1 * RAD2DEG * TIMESTEP;

/*
  	JV_MAX[0] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[1] = 1 * RAD2DEG * TIMESTEP;
	JV_MAX[2] = 2 * RAD2DEG * TIMESTEP;
	JV_MAX[3] = 2 * RAD2DEG * TIMESTEP;
	JV_MAX[4] = 2 * M_PI * RAD2DEG * TIMESTEP;
	JV_MAX[5] = 2 * M_PI * RAD2DEG * TIMESTEP;
	JV_MAX[6] = 2 * M_PI * RAD2DEG * TIMESTEP;
*/	
	if (configurationList.size() != 0)
	{
		LeonardoConfiguration t = configurationList.front();

		double adjust;

		double diffX = t.x - currentConfiguration.x;
		double diffY = t.y - currentConfiguration.y;
		double diffA = t.a - currentConfiguration.a;
		double diffA2 = 0;
		double diffXY = sqrt(diffX * diffX + diffY * diffY);
		if (fabs(diffXY) >= E_TRANS)
		{
			double theta = atan2(diffY, diffX) * RAD2DEG;
			
			diffA2 = theta - currentConfiguration.a;
			if (fabs(diffA2) > E_ROT)
			{
				if (fabs(diffA2) > PR_MAX)
				{
					adjust = PR_MAX;
					if (diffA2 < 0)
						adjust *= -1;
				}
				else
				{
					adjust = diffA2;
				};
				currentConfiguration.a += adjust;
			}
			else
			{
				if (diffXY > PT_MAX)
				{
					adjust = PT_MAX;
				}
				else
				{
					adjust = diffXY;
				}
				currentConfiguration.x += adjust * cos(theta * DEG2RAD);
				currentConfiguration.y += adjust * sin(theta * DEG2RAD);
			}
		}
		else
		{
			diffA = t.a - currentConfiguration.a;
			if (fabs(diffA) > E_ROT)
			{
				if (fabs(diffA) > PR_MAX)
				{
					adjust = PR_MAX;
					if (diffA < 0)
						adjust *= -1;
				}
				else
				{
					adjust = diffA;
				};
				currentConfiguration.a += adjust;
			}
		}
		//c.x += 0.01;
		//setConfiguration(c.x, c.y, c.a, c.s1, c.s2, c.s3, c.e1, c.e2, c.w1, c.w2);

		double diffS1 = t.s1 - currentConfiguration.s1;
		if (fabs(diffS1) > JV_MAX[0])
		{
			adjust = JV_MAX[0];
			if (diffS1 < 0)
				adjust *= -1;
		}
		else
		{
			adjust = diffS1;
		};
		currentConfiguration.s1 += adjust;

		double diffS2 = t.s2 - currentConfiguration.s2;
		if (fabs(diffS2) > JV_MAX[1])
		{
			adjust = JV_MAX[1];
			if (diffS2 < 0)
				adjust *= -1;
		}
		else
		{
			adjust = diffS2;
		};
		currentConfiguration.s2 += adjust;

		double diffS3 = t.s3 - currentConfiguration.s3;
		if (fabs(diffS3) > JV_MAX[2])
		{
			adjust = JV_MAX[2];
			if (diffS3 < 0)
				adjust *= -1;
		}
		else
		{
			adjust = diffS3;
		};
		currentConfiguration.s3 += adjust;

		double diffE1 = t.e1 - currentConfiguration.e1;
		if (fabs(diffE1) > JV_MAX[3])
		{
			adjust = JV_MAX[3];
			if (diffE1 < 0)
				adjust *= -1;
		}
		else
		{
			adjust = diffE1;
		};
		currentConfiguration.e1 += adjust;

		double diffE2 = t.e2 - currentConfiguration.e2;
		if (fabs(diffE2) > JV_MAX[4])
		{
			adjust = JV_MAX[4];
			if (diffE2 < 0)
				adjust *= -1;
		}
		else
		{
			adjust = diffE2;
		};
		currentConfiguration.e2 += adjust;

		double diffW1 = t.w1 - currentConfiguration.w1;
		if (fabs(diffW1) > JV_MAX[5])
		{
			adjust = JV_MAX[5];
			if (diffW1 < 0)
				adjust *= -1;
		}
		else
		{
			adjust = diffW1;
		};
		currentConfiguration.w1 += adjust;
		
		double diffW2 = t.w2 - currentConfiguration.w2;
		if (fabs(diffW2) > JV_MAX[6])
		{
			adjust = JV_MAX[6];
			if (diffW2 < 0)
				adjust *= -1;
		}
		else
		{
			adjust = diffW2;
		};
		currentConfiguration.w2 += adjust;
		
		setConfiguration(
			currentConfiguration.x,
			currentConfiguration.y,
			currentConfiguration.a,
			currentConfiguration.s1,
			currentConfiguration.s2,
			currentConfiguration.s3,
			currentConfiguration.e1,
			currentConfiguration.e2,
			currentConfiguration.w1,
			currentConfiguration.w2
		);
		
		if ((fabs(diffS1) + fabs(diffS2) + fabs(diffS3) + fabs(diffE1) +
		    fabs(diffE2) + fabs(diffW1) + fabs(diffW2) < E_ROT) &&
		    (diffXY < E_TRANS) && (fabs(diffA) < E_ROT))
		{
			configurationList.erase(configurationList.begin());
		};
	};
};
