#ifndef LEONARDOCONTROL_H
#define LEONARDOCONTROL_H

#include <qobject.h>
#include "LeonardoConfiguration.h"
#include <vector>

class QTimer;
class LeonardoModel;

class LeonardoControl :public QObject
{
	Q_OBJECT
	
private:
	LeonardoModel* leonardoModel;
	std::vector<LeonardoConfiguration> configurationList;
	LeonardoConfiguration currentConfiguration;
	QTimer* controlTimer;
	
private slots:
	void timeout();
	
public:
	LeonardoControl();
	virtual ~LeonardoControl();
	
	void setModel(LeonardoModel* leonardoModel);
	void setConfiguration(double x, double y, double a,
		double s1, double s2, double s3, double e1, double e2,
		double w1, double w2);
	
	void moveConfiguration(double x, double y, double a,
		double s1, double s2, double s3, double e1, double e2,
		double w1, double w2);
};

#endif //LEONARDOCONTROL_H
