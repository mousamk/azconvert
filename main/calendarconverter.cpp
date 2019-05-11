/* This file is part of:
 *    Jalali, a Gregorian to Jalali and inverse date convertor
 * Copyright (C) 2001  Roozbeh Pournader <roozbeh@sharif.edu>
 * Copyright (C) 2001  Mohammad Toossi <mohammad@bamdad.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You can receive a copy of GNU Lesser General Public License at the
 * World Wide Web address <http://www.gnu.org/licenses/lgpl.html>.
 *
 * For licensing issues, contact The FarsiWeb Project Group,
 * Computing Center, Sharif University of Technology,
 * PO Box 11365-8515, Tehran, Iran, or contact us the
 * email address <FWPG@sharif.edu>.
 */



#include "calendarconverter.h"


int g_days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int j_days_in_month[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};


bool CalendarConverter::Jalali2Gregorian(int& gY, int& gM, int& gD, int jY, int jM, int jD)
{
   //Check validateness:
   if (jD > j_days_in_month[jM-1] && !(jM == 12 && jD == 30))
       return false;


   int gy, gm, gd;
   int jy, jm, jd;
   long gDay_no, j_day_no;
   int leap;

   int i;

   jy = jY-979;
   jm = jM-1;
   jd = jD-1;

   j_day_no = 365*jy + (jy/33)*8 + (jy%33+3)/4;
   for (i=0; i < jm; ++i)
      j_day_no += j_days_in_month[i];

   j_day_no += jd;

   gDay_no = j_day_no+79;

   gy = 1600 + 400*(gDay_no/146097); /* 146097 = 365*400 + 400/4 - 400/100 + 400/400 */
   gDay_no = gDay_no % 146097;

   leap = 1;
   if (gDay_no >= 36525) /* 36525 = 365*100 + 100/4 */
   {
      gDay_no--;
      gy += 100*(gDay_no/36524); /* 36524 = 365*100 + 100/4 - 100/100 */
      gDay_no = gDay_no % 36524;

      if (gDay_no >= 365)
         gDay_no++;
      else
         leap = 0;
   }

   gy += 4*(gDay_no/1461); /* 1461 = 365*4 + 4/4 */
   gDay_no %= 1461;

   if (gDay_no >= 366) {
      leap = 0;

      gDay_no--;
      gy += gDay_no/365;
      gDay_no = gDay_no % 365;
   }

   //continue validating:
   /*if (leap != 1 && jM == 12 && jD == 30)
       return false;*/
   //I removed above, because it can be harmful in years outside 1925-2088

   for (i = 0; gDay_no >= g_days_in_month[i] + (i == 1 && leap); i++)
      gDay_no -= g_days_in_month[i] + (i == 1 && leap);
   gm = i+1;
   gd = gDay_no+1;

   //Setting output:
   gY = gy;
   gM = gm;
   gD = gd;
   return true;
}


bool CalendarConverter::Gregorian2Jalali(int& jY, int& jM, int& jD, int gY, int gM, int gD)
{
   //Check validateness:
   if (gD > g_days_in_month[gM-1] && !(gM == 2 && gD == 29))
       return false;

   int gy, gm, gd;
   int jy, jm, jd;
   long gDay_no, j_day_no;
   int j_np;

   int i;

   gy = gY-1600;
   gm = gM-1;
   gd = gD-1;

   gDay_no = 365*gy+(gy+3)/4-(gy+99)/100+(gy+399)/400;
   for (i=0;i<gm;++i)
      gDay_no += g_days_in_month[i];
   if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
      /* leap and after Feb */
      ++gDay_no;
   gDay_no += gd;

   j_day_no = gDay_no-79;

   j_np = j_day_no / 12053;
   j_day_no %= 12053;

   jy = 979+33*j_np+4*(j_day_no/1461);
   j_day_no %= 1461;

   if (j_day_no >= 366) {
      jy += (j_day_no-1)/365;
      j_day_no = (j_day_no-1)%365;
   }

   for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i) {
      j_day_no -= j_days_in_month[i];
   }
   jm = i+1;
   jd = j_day_no+1;

   //Settig output:
   jY = jy;
   jM = jm;
   jD = jd;
   return true;
}
