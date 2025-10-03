#include <curveFitting.h>






//////////////////////////////////////////////////////////                                  *********************************************************************
//********************************************************            5-POINT               *********************************************************************
//////////////////////////////////////////////////////////                                  *********************************************************************
void getCoeff(float x_a[5], float y_a[5], int eq) {     // phCalValue, bufferValue, atcbufferValue
  char buf[10];
  int xpower = 1;
  int order = 1;
  double a[2], b[2], c[2], d[2], e[2];       // Arrays for 5-point spline-calibration
  double at[2], bt[2], ct[2], dt[2], et[2];


  // 5-POINT CALIBRATION
  if (eq == 11 || eq == 21 || eq == 31 || eq == 41 || eq == 51) {
    for (int i = 0; i <= 1; i++) {
      a[i]  = y_a[i];
      b[i]  = y_a[i + 1];
      c[i]  = y_a[i + 2];
      d[i]  = y_a[i + 3];
      at[i] = x_a[i];
      bt[i] = x_a[i + 1];
      ct[i] = x_a[i + 2];
      dt[i] = x_a[i + 3];
    }
  }
  double coeffs[order + 1];
  int ret = 1;
  if (eq == 11) ret = fitCurve(order, sizeof(a) / sizeof(double), at, a, sizeof(coeffs) / sizeof(double), coeffs);
  if (eq == 21) ret = fitCurve(order, sizeof(b) / sizeof(double), bt, b, sizeof(coeffs) / sizeof(double), coeffs);
  if (eq == 31) ret = fitCurve(order, sizeof(c) / sizeof(double), ct, c, sizeof(coeffs) / sizeof(double), coeffs);
  if (eq == 41) ret = fitCurve(order, sizeof(d) / sizeof(double), dt, d, sizeof(coeffs) / sizeof(double), coeffs);
  //if(eq == 51) ret = fitCurve(order, sizeof(d) / sizeof(double), dt, d, sizeof(coeffs) / sizeof(double), coeffs);
  //if(eq == 61) ret = fitCurve(order, sizeof(g) / sizeof(double), gt, g, sizeof(coeffs) / sizeof(double), coeffs);
  if (ret == 0) {

    if (eq == 11) {
      phCalCoeff[0] = coeffs[0];
      phCalCoeff[1] = coeffs[1];
      Serial.println("Cal: 5 EQ: 1");
      Serial.print(coeffs[0]);
      Serial.print("x + ");
      Serial.print(coeffs[1]);
    }
    else if (eq == 21) {
      phCalCoeff[2] = coeffs[0];
      phCalCoeff[3] = coeffs[1];
      Serial.println("Cal: 5 EQ: 2");
      Serial.print(coeffs[0]);
      Serial.print("x + ");
      Serial.print(coeffs[1]);
    }
    else if (eq == 31) {
      phCalCoeff[4] = coeffs[0];
      phCalCoeff[5] = coeffs[1];
      Serial.println("Cal: 5 EQ: 3");
      Serial.print(coeffs[0]);
      Serial.print("x + ");
      Serial.print(coeffs[1]);
    }
    else if (eq == 41) {
      phCalCoeff[6] = coeffs[0];
      phCalCoeff[7] = coeffs[1];
      Serial.println("Cal: 5 EQ: 4");
      Serial.print(coeffs[0]);
      Serial.print("x + ");
      Serial.print(coeffs[1]);

    }
  }
}
//////////////////////////////////////////////////////////                                  *********************************************************************
//********************************************************            5-POINT               *********************************************************************
//////////////////////////////////////////////////////////                                  *********************************************************************

















//////////////////////////////////////////////////////////                        *********************************************************************
//********************************************************            3-POINT     *********************************************************************
//////////////////////////////////////////////////////////                        *********************************************************************
void getCoeff3(float x_a[3], float y_a[3], int eq) {     // phCalValue, bufferValue, atcbufferValue
  char buf[10];
  int xpower = 1;
  int order = 1;
  // Arrays for 3-point spline-calibration
  double f[2], g[2] , h[2];
  double ft[2], gt[2], ht[2];


  // 3-POINT CALIBRATION
  if (eq == 11 || eq == 21 || eq == 31) {
    for (int i = 0; i <= 1; i++) {
      f[i]  = y_a[i];
      g[i]  = y_a[i + 1];
      h[i]  = y_a[i];

      ft[i] = x_a[i];
      gt[i] = x_a[i + 1];
      ht[i] = x_a[i + 2];
    }
  }
  double coeffs[order + 1];
  int ret = 1;
  if (eq == 11) ret = fitCurve(order, sizeof(f) / sizeof(double), ft, f, sizeof(coeffs) / sizeof(double), coeffs);
  if (eq == 21) ret = fitCurve(order, sizeof(g) / sizeof(double), gt, g, sizeof(coeffs) / sizeof(double), coeffs);
  if (ret == 0) {
    if (eq == 11) {
      phCalCoeff3[0] = coeffs[0];
      phCalCoeff3[1] = coeffs[1];
      Serial.println("Cal: 3 EQ: 1");
      Serial.print(coeffs[0]);
      Serial.print("x + ");
      Serial.print(coeffs[1]);
    }
    else if (eq == 21) {
      phCalCoeff3[2] = coeffs[0];
      phCalCoeff3[3] = coeffs[1];
      Serial.println("Cal: 3 EQ: 2");
      Serial.print(coeffs[0]);
      Serial.print("x + ");
      Serial.print(coeffs[1]);
    }

  }
}
//////////////////////////////////////////////////////////                                 *********************************************************************
//********************************************************            3-POINT_END          *********************************************************************
//////////////////////////////////////////////////////////                                 *********************************************************************
