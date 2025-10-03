#include <EEPROM.h>

//#define EEPROM_address_coeff_a 100
//#define EEPROM_address_coeff_b 120

void write_buffer_EEPROM() {
  if (cal_mode == 2) {
    EEPROM.put(240, bufferValue[0]);
    EEPROM.put(246, bufferValue[1]);
    EEPROM.put(252, bufferValue[2]);
    EEPROM.put(258, bufferValue[3]);
    EEPROM.put(264, bufferValue[4]);
  }
  else if (cal_mode == 1) {
    bufferValue3[0] = bufferValue[1];
    bufferValue3[1] = bufferValue[2];
    bufferValue3[2] = bufferValue[3];
    EEPROM.put(470, bufferValue3[0]);
    EEPROM.put(476, bufferValue3[1]);
    EEPROM.put(482, bufferValue3[2]);
  }
  EEPROM.commit();
  Serial.println("Writing buffers into eeprom");
}

void read_buffer_EEPROM() {
  EEPROM.get(680, first_run_flag);
  if (first_run_flag != 1) {
    EEPROM.put(240, bufferValue[0]);
    EEPROM.put(246, bufferValue[1]);
    EEPROM.put(252, bufferValue[2]);
    EEPROM.put(258, bufferValue[3]);
    EEPROM.put(264, bufferValue[4]);
    EEPROM.put(470, bufferValue3[0]);
    EEPROM.put(476, bufferValue3[1]);
    EEPROM.put(482, bufferValue3[2]);
    first_run_flag = 1;
    EEPROM.put(680, first_run_flag);
  }
  EEPROM.get(240, bufferValue[0]);
  EEPROM.get(246, bufferValue[1]);
  EEPROM.get(252, bufferValue[2]);
  EEPROM.get(258, bufferValue[3]);
  EEPROM.get(264, bufferValue[4]);
  EEPROM.get(470, bufferValue3[0]);
  EEPROM.get(476, bufferValue3[1]);
  EEPROM.get(482, bufferValue3[2]);
  Serial.println("Reading buffers from eeprom");
  Serial.println(bufferValue[0]);
  Serial.println(bufferValue[1]);
  Serial.println(bufferValue[2]);
  Serial.println(bufferValue[3]);
  Serial.println(bufferValue[4]);
  Serial.println("bufferValue3");
  Serial.println(bufferValue3[0]);
  Serial.println(bufferValue3[1]);
  Serial.println(bufferValue3[2]);

  // Assign values to your variables

  add_val1 = bufferValue[0];
  add_val2 = bufferValue[1];
  add_val3 = bufferValue[2];
  add_val4 = bufferValue[3];
  add_val5 = bufferValue[4];



}

void write_phcal_EEPROM() {
  if (cal_mode == 2) {
    EEPROM.put(270, phCalValue[0]);
    EEPROM.put(276, phCalValue[1]);
    EEPROM.put(282, phCalValue[2]);
    EEPROM.put(288, phCalValue[3]);
    EEPROM.put(294, phCalValue[4]);
  }
  else if (cal_mode == 1) {
    EEPROM.put(488, phCalValue3[0]);
    EEPROM.put(494, phCalValue3[1]);
    EEPROM.put(500, phCalValue3[2]);
  }
  EEPROM.commit();
  Serial.println("Writing phcals into eeprom");
}

void read_phcal_EEPROM() {
  EEPROM.get(270, phCalValue[0]);
  EEPROM.get(276, phCalValue[1]);
  EEPROM.get(282, phCalValue[2]);
  EEPROM.get(288, phCalValue[3]);
  EEPROM.get(294, phCalValue[4]);
  EEPROM.get(410, cal_mode);
  EEPROM.get(488, phCalValue3[0]);
  EEPROM.get(494, phCalValue3[1]);
  EEPROM.get(500, phCalValue3[2]);
  Serial.println("phCalValue3");
  Serial.println(phCalValue3[0]);
  Serial.println(phCalValue3[1]);
  Serial.println(phCalValue3[2]);
  Serial.println("************cal_mode*************");
  Serial.println(cal_mode);
  Serial.println("Reading phcals from eeprom");
}


void writeCoeffIntoEEPROM() {
  Serial.println("Writing Coeff into eeprom");
  if (cal_mode == 2) {
    EEPROM.put(110, phCalCoeff[0]);
    EEPROM.put(116, phCalCoeff[1]);
    EEPROM.put(122, phCalCoeff[2]);
    EEPROM.put(300, phCalCoeff[3]);
    EEPROM.put(306, phCalCoeff[4]);
    EEPROM.put(312, phCalCoeff[5]);
    EEPROM.put(318, phCalCoeff[6]);
    EEPROM.put(324, phCalCoeff[7]);
    EEPROM.put(330, phCalCoeff[8]);
  }
  else if (cal_mode == 1) {
    EEPROM.put(506, phCalCoeff3[0]);
    EEPROM.put(512, phCalCoeff3[1]);
    EEPROM.put(518, phCalCoeff3[2]);
    EEPROM.put(524, phCalCoeff3[3]);
  }
  EEPROM.put(336, ATCCalCoeff[0]);
  EEPROM.put(342, ATCCalCoeff[1]);
  EEPROM.put(348, ATCCalCoeff[2]);
  EEPROM.put(354, ATCCalCoeff[3]);
  EEPROM.put(360, ATCCalCoeff[4]);
  EEPROM.put(366, ATCCalCoeff[5]);
  EEPROM.put(372, ATCCalCoeff[6]);
  EEPROM.put(378, ATCCalCoeff[7]);
  EEPROM.put(384, ATCCalCoeff[8]);

  EEPROM.commit();
}

void readCoeffFromEEPROM() {
  EEPROM.get(110, phCalCoeff[0]);
  EEPROM.get(116, phCalCoeff[1]);
  EEPROM.get(122, phCalCoeff[2]);
  EEPROM.get(300, phCalCoeff[3]);
  EEPROM.get(306, phCalCoeff[4]);
  EEPROM.get(312, phCalCoeff[5]);
  EEPROM.get(318, phCalCoeff[6]);
  EEPROM.get(324, phCalCoeff[7]);
  EEPROM.get(330, phCalCoeff[8]);


  EEPROM.get(506, phCalCoeff3[0]);
  EEPROM.get(512, phCalCoeff3[1]);
  EEPROM.get(518, phCalCoeff3[2]);
  EEPROM.get(524, phCalCoeff3[3]);
  Serial.println("phCalCoeff3");
  Serial.println(phCalCoeff3[0]);
  Serial.println(phCalCoeff3[1]);
  Serial.println(phCalCoeff3[2]);
  Serial.println(phCalCoeff3[3]);



  EEPROM.get(336, ATCCalCoeff[0]);
  EEPROM.get(342, ATCCalCoeff[1]);
  EEPROM.get(348, ATCCalCoeff[2]);
  EEPROM.get(354, ATCCalCoeff[3]);
  EEPROM.get(360, ATCCalCoeff[4]);
  EEPROM.get(366, ATCCalCoeff[5]);
  EEPROM.get(372, ATCCalCoeff[6]);
  EEPROM.get(378, ATCCalCoeff[7]);
  EEPROM.get(384, ATCCalCoeff[8]);

  Serial.print("Reading NATC Coeff into eeprom...a1 = ");
  Serial.print(phCalCoeff[0]);
  Serial.print("  b1= ");
  Serial.println(phCalCoeff[1]);
  Serial.print("  c1= ");
  Serial.println(phCalCoeff[2]);
  Serial.print("  a2= ");
  Serial.println(phCalCoeff[3]);
  Serial.print("  b2= ");
  Serial.println(phCalCoeff[4]);
  Serial.print("  c2= ");
  Serial.println(phCalCoeff[5]);
  Serial.print("  A1= ");
  Serial.println(phCalCoeff[6]);
  Serial.print("  B1= ");
  Serial.println(phCalCoeff[7]);
  Serial.print("  C1= ");
  Serial.println(phCalCoeff[8]);

  Serial.print("Reading ATC Coeff into eeprom...a1= ");
  Serial.print(ATCCalCoeff[0]);
  Serial.print("  b1= ");
  Serial.println(ATCCalCoeff[1]);
  Serial.print("  c1= ");
  Serial.println(ATCCalCoeff[2]);
  Serial.print("  a2= ");
  Serial.println(ATCCalCoeff[3]);
  Serial.print("  b2= ");
  Serial.println(ATCCalCoeff[4]);
  Serial.print("  c2= ");
  Serial.println(ATCCalCoeff[5]);
  Serial.print("  A1= ");
  Serial.println(ATCCalCoeff[6]);
  Serial.print("  B1= ");
  Serial.println(ATCCalCoeff[7]);
  Serial.print("  C1= ");
  Serial.println(ATCCalCoeff[8]);

}

void read_slopes() {


  EEPROM.get(420, slope_total);
  EEPROM.get(426, buf_slope[0]);
  EEPROM.get(432, buf_slope[1]);
  EEPROM.get(438, buf_slope[2]);
  EEPROM.get(444, buf_slope[3]);
  EEPROM.get(450, Ro);
  EEPROM.get(500, R_C);
  EEPROM.get(510, SENSORSELECT);
  EEPROM.get(460, manual_calibration_flag);


  Serial.print("Main Slope");
  Serial.print(slope_total);
  Serial.print("  Slope I ");
  Serial.println(buf_slope[0]);
  Serial.print("  Slope II ");
  Serial.println(buf_slope[1]);
  Serial.print("  Slope III ");
  Serial.println(buf_slope[2]);
  Serial.print("  Slope IV  ");
  Serial.println(buf_slope[3]);
  Serial.print("  R_C  ");
  Serial.println(R_C);
  Serial.print("  SENSORSELECT  ");
  Serial.println(SENSORSELECT);

}
