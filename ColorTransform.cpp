#include <iostream>
#include "matrixf.h"
using namespace std;

Matrixf convert_rgb_to_hls(double r,double g,double b);
Matrixf convert_hls_to_rgb(double h,double l,double s);
double convert_hue(double x,double y,double h1);
Matrixf hls_linear_interpolation(Matrixf vec1,Matrixf vec2,double t);

int main(int argc, char* argv[])
{
	Matrixf vec1RGB(1,3),vec2RGB(1,3),vec1HLS(1,3),vec2HLS(1,3), ret(1,3),interp(1,3);
	double r1=0,g1=0,b1=0,r2=0,g2=0,b2=0,t=0;
	
	cout<< "For Vector 1, Enter R value: ";
	cin>> r1;
	cout<< "For Vector 1, Enter G value: ";
	cin>> g1;
	cout<< "For Vector 1, Enter B value: ";
	cin>> b1;

	cout<< "For Vector 2, Enter R value: ";
	cin>> r2;
	cout<< "For Vector 2, Enter G value: ";
	cin>> g2;
	cout<< "For Vector 2, Enter B value: ";
	cin>> b2;

	cout<< "Enter the Interpolation factor, t: ";
	cin>> b2;


	vec1HLS=convert_rgb_to_hls(r1,g1,b1);
	cout<<"Vector 1: "<<vec1HLS;

	vec2HLS=convert_rgb_to_hls(r2,g2,b2);
	cout<<"Vector 2: "<<vec2HLS;

	interp=hls_linear_interpolation(vec1HLS,vec2HLS,t);
	cout<<"Interpolated HLS Vector: "<<interp;

	ret=convert_hls_to_rgb(interp(0,0),interp(0,1),interp(0,2));
	cout<<"Interpolated RGB Vector: "<<ret;
	getchar();
	return 0;
}

Matrixf convert_rgb_to_hls(double r,double g,double b)
{
	double hue;
	double sat;
	double light;
	double red =(r/255.0);
	double green=(g/255.0);
	double blue=(b/255.0);

	double minValue=min(min(red,green),blue);
	double maxValue=max(max(red,green),blue);
	double delta=maxValue-minValue;

	light=(maxValue+minValue)/2;
	hue=0;
	sat=0;

	if(maxValue!=minValue)
	{
		if(light < 0.5)
		{
			sat = delta / (maxValue + minValue);
		}
		else
		{
			sat = delta / (2.0 - maxValue - minValue);
		}
		if(red == maxValue)
		{
			hue = (green-blue) / (maxValue - minValue);
		}
		else if(green == maxValue)
		{
			hue = 2.0 + (blue - red) / (maxValue - minValue);
		}
		else{
			hue = 4.0 + (red - green) / (maxValue - minValue);
		}
	}
	light = light * 100;
	sat = sat * 100;
	hue = hue * 60;
	if(hue<0){
		hue += 360;
	}

	Matrixf ret(1,3);
	ret(0,0)=hue;
	ret(0,1)=light;
	ret(0,2)=sat;
	return ret;
}

Matrixf convert_hls_to_rgb(double h,double l,double s)
{
	double light = l / 100.0;
	double sat = s / 100.0;
	double hue=h;
	double red,green,blue,m1,m2;

	if (light<0.5)
	{
		m2=light+(light*sat);
	}
	else
	{
		m2=light+sat-light*sat;
	}
	m1=2*light-m2;

	if ( sat == 0 )                       
	{
		red = light;                     
		green = light;
		blue = light;
	}
	else
	{
		red = convert_hue(m1,m2,hue+120);                     
		green = convert_hue(m1,m2,hue);
		blue = convert_hue(m1,m2,hue-120);
	}
	red*=255.0;
	blue*=255.0;
	green*=255.0;

	Matrixf ret(1,3);
	ret(0,0)=red;
	ret(0,1)=green;
	ret(0,2)=blue;
	return ret;

}

double convert_hue(double n1,double n2,double h)
{
	double hue=h;
	double res;
	if(hue>=360)
	{
		hue-=360;
	}
	if (hue<0)
	{
		hue+=360;
	}
	if (hue<60)
	{
		res=n2+(n2-n1)*hue/60.0;
	}
	else
	{
		if (hue<180)
		{
			res=n2;
		}
		else
		{
			if (hue<240)
			{
				res=n1+(n2-n1)*(240-hue)/60.0;
			}
			else
			{
				res=n1;
			}
		}
	}
	return res;
}

Matrixf hls_linear_interpolation(Matrixf vec1,Matrixf vec2,double t)
{
	Matrixf ret(1,3);
	ret(0,0)=vec1(0,0)+t*(vec2(0,0)-vec1(0,0));
	ret(0,1)=vec1(0,1)+t*(vec2(0,1)-vec1(0,1));
	ret(0,2)=vec1(0,2)+t*(vec2(0,2)-vec1(0,2));
	return ret;
}