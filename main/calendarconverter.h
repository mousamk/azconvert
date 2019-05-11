#ifndef CALENDARCONVERTER_H
#define CALENDARCONVERTER_H



class CalendarConverter
{
public:
    static bool Jalali2Gregorian(/*output*/ int& gY, int& gM, int& gD,
                                 /*input*/  int  jY, int  jM, int  jD);
    static bool Gregorian2Jalali(/*output*/ int& jY, int& jM, int& jD,
                                 /*input*/  int  gY, int  gM, int  gD);
};


#endif // CALENDARCONVERTER_H
