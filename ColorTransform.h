#ifndef ColorTransform_H__
#define ColorTransform_H__

Matrixf convert_rgb_to_hls(double r,double g,double b);
Matrixf convert_hls_to_rgb(double h,double l,double s);
double convert_hue(double x,double y,double h1);
Matrixf hls_linear_interpolation(Matrixf vec1,Matrixf vec2,double t);

#endif // ColorTransform_H__