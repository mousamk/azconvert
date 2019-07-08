# AzConvert

AzConvert is an automatic transliteration program for Azerbaijani language.

Due to historical reasons, the [Azerbaijani language](https://en.wikipedia.org/wiki/Azerbaijani_language) is currently being written in three different scripts. Latin script is used in the republic of Azerbaijan, Perso-Arabic script is used in the Iranian Azerbaijan and the Cyrillic script is used in the Republic of Dagestan, Russia. Converting between Latin and Cyrillic is pretty obvious and straight-forward, since it's a one-to-one character conversion. However, converting between Latin and Arabic scripts is hard, because of different rules of writing. AzConvert aimed to fix this problem and provide an easy and automated solution.

## Programming
This program is creating in C++ language, using Qt framework. It can be compiled and run on Windows, Linux and Mac operating systems. It uses SQLite to hold some static data, including predefined irregular words and their conversions, prefixed, suffixed, characters and etc. There's also a php port of it, which uses the same data and algorithms but can be run on a web server and provide conversion services.