#include "c2lconversion.h"


C2LConversion::C2LConversion()
{
}



QString C2LConversion::Convert(QString str)
{
    str.replace(QChar('\x10', '\x04'), 'A');
    str.replace(QChar('\x30', '\x04'), 'a');
    str.replace(QChar('\x11', '\x04'), 'B');
    str.replace(QChar('\x31', '\x04'), 'b');
    str.replace(QChar('\xb8', '\x04'), 'C');
    str.replace(QChar('\xb9', '\x04'), 'c');
    str.replace(QChar('\x27', '\x04'), '\xc7');
    str.replace(QChar('\x47', '\x04'), '\xe7');
    str.replace(QChar('\x14', '\x04'), 'D');
    str.replace(QChar('\x34', '\x04'), 'd');
    str.replace(QChar('\x15', '\x04'), 'E');
    str.replace(QChar('\x35', '\x04'), 'e');
    str.replace(QChar('\xd8', '\x04'), QChar('\x8f', '\x01'));
    str.replace(QChar('\xd9', '\x04'), QChar('\x59', '\x02'));
    str.replace(QChar('\x24', '\x04'), 'F');
    str.replace(QChar('\x44', '\x04'), 'f');
    str.replace(QChar('\x9c', '\x04'), 'G');
    str.replace(QChar('\x9d', '\x04'), 'g');
    str.replace(QChar('\x92', '\x04'), QChar('\x1e', '\x01'));
    str.replace(QChar('\x93', '\x04'), QChar('\x1f', '\x01'));
    str.replace(QChar('\xba', '\x04'), 'H');
    str.replace(QChar('\xbb', '\x04'), 'h');
    str.replace(QChar('\x25', '\x04'), 'X');
    str.replace(QChar('\x45', '\x04'), 'x');
    str.replace(QChar('\x18', '\x04'), QChar('\x30', '\x01'));
    str.replace(QChar('\x38', '\x04'), 'i');
    str.replace(QChar('\x2b', '\x04'), 'I');
    str.replace(QChar('\x4b', '\x04'), QChar('\x31', '\x01'));
    str.replace(QChar('\x16', '\x04'), 'J');
    str.replace(QChar('\x36', '\x04'), 'j');
    str.replace(QChar('\x1a', '\x04'), 'K');
    str.replace(QChar('\x3a', '\x04'), 'k');
    str.replace(QChar('\x1b', '\x04'), 'L');
    str.replace(QChar('\x3b', '\x04'), 'l');
    str.replace(QChar('\x1c', '\x04'), 'M');
    str.replace(QChar('\x3c', '\x04'), 'm');
    str.replace(QChar('\x1d', '\x04'), 'N');
    str.replace(QChar('\x3d', '\x04'), 'n');
    str.replace(QChar('\x1e', '\x04'), 'O');
    str.replace(QChar('\x3e', '\x04'), 'o');
    str.replace(QChar('\xe8', '\x04'), '\xd6');
    str.replace(QChar('\xe9', '\x04'), '\xf6');
    str.replace(QChar('\x1f', '\x04'), 'P');
    str.replace(QChar('\x3f', '\x04'), 'p');
    str.replace(QChar('\x13', '\x04'), 'Q');
    str.replace(QChar('\x33', '\x04'), 'q');
    str.replace(QChar('\x20', '\x04'), 'R');
    str.replace(QChar('\x40', '\x04'), 'r');
    str.replace(QChar('\x21', '\x04'), 'S');
    str.replace(QChar('\x41', '\x04'), 's');
    str.replace(QChar('\x28', '\x04'), QChar('\x5e', '\x01'));
    str.replace(QChar('\x48', '\x04'), QChar('\x5f', '\x01'));
    str.replace(QChar('\x22', '\x04'), 'T');
    str.replace(QChar('\x42', '\x04'), 't');
    str.replace(QChar('\x23', '\x04'), 'U');
    str.replace(QChar('\x43', '\x04'), 'u');
    str.replace(QChar('\xae', '\x04'), '\xdc');
    str.replace(QChar('\xaf', '\x04'), '\xfc');
    str.replace(QChar('\x12', '\x04'), 'V');
    str.replace(QChar('\x32', '\x04'), 'v');
    str.replace(QChar('\x08', '\x04'), 'Y');
    str.replace(QChar('\x58', '\x04'), 'y');
    str.replace(QChar('\x17', '\x04'), 'Z');
    str.replace(QChar('\x37', '\x04'), 'z');
    return str;
}
