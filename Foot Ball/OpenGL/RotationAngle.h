#ifndef _ROTATION_ANGLE_H
#define _ROTATION_ANGLE_H

//This class keeps track of a rotation angle, specified with respect to each of the 3 axes.

class RotationAngle
{
private:
	float theta[3];			//Angle made with each of the 3 axes

public:

	RotationAngle();
	RotationAngle(float thetax, float thetay, float thetaz);

	float getTheta(AxisType axisType);
	float getThetaRadians(AxisType axisType);

	void setTheta(AxisType axisType, float value);

	friend ostream& operator<<(ostream& out, RotationAngle &angle);
};

RotationAngle::RotationAngle()
{
	theta[X_AXIS] = theta[Y_AXIS] = theta[Z_AXIS] = 0;
}

RotationAngle::RotationAngle(float thetaX, float thetaY, float thetaZ)
{
	theta[X_AXIS] = thetaX;
	theta[Y_AXIS] = thetaY;
	theta[Z_AXIS] = thetaZ;
}

float RotationAngle::getTheta(AxisType axisType)
{
	return theta[axisType];
}

float RotationAngle::getThetaRadians(AxisType axisType)
{
	return theta[axisType] / 180 * 3.141592654f;
}

void RotationAngle::setTheta(AxisType axisType, float value)
{
	theta[axisType] = value;
}

ostream & operator<<(ostream& out, RotationAngle &angle)
{
	out << "(" << angle.theta[X_AXIS] << ", " << angle.theta[Y_AXIS] << ", " << angle.theta[Z_AXIS] << ")";
    return out;
}

#endif