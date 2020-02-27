# FT897D CAT command in arduino
This Arduino library created will allow you to control various functions of your radio via an Arduino micro-controller through the use of “Computer Aided Transceiver” (CAT) functions. Although the CAT command byte definitions are aimed at a Yaesu FT-897D, many of the functions should work along the FT-8*7 platform with little or no need for modification.

Requirements:
Arduino 1.8.x
FT897D library
CAT control interface from radio

    GND -> Arduino GND
    TX -> Arduino pin 2 (can be changed in library)
    RX -> Arduino pin 3 (can be changed in library)

Command Set:

To use the library functions, call them using the identifier you have chosen (ie. “radio” as the above example suggests). A list of the functions is as follows:

    lock on / off = radio.lock(true / false);
    PTT on / off = radio.PTT(true / false);
    Set frequency = radio.setFreq( desired frequency – no decimals );
    Set operating mode = radio.setMode( mode name  – eg. usb );
    Clarifier on / off = radio.clar( true / false );
    Clarifier frequency = radio.clarFreq( desired frequency – again, no decimals );
    VFO A / B swapping = radio.switchVFO();
    Split operation on / off = radio.split( true / false );
    Repeater offset direction (+, -, simplex) = radio.rptrOffset( +, -, or s );
    Repeater offset frequency = radio.rptrOffsetFreq( offset frequench in kHz );
    CTCSS / DCS on / off = radio.squelch( DCS or TEN );
    CTCSS tone / DCS code = radio.squelchFreq( frequency, T or D );
    Read TX status = radio.chkTX(); – returns true / false
    Read RX frequency & mode = radio.getFreqMode();

Installation:

To install this library, simply extract the archived file inside the libraries directory 
found in the root Arduino IDE directory 

To test your physical connection to the radio, and to ensure you are able to #include the library,
would suggest you try the example sketch that is included in the library. 

Эта созданная библиотека Arduino позволит вам управлять различными функциями вашего радио через микроконтроллер Arduino с помощью функций «Computer Aided Transceiver» (CAT). Хотя определения командных байтов CAT предназначены для Yaesu FT-897D, многие функции должны работать на платформе FT-8 * 7 практически без необходимости модификации.

Требования: Arduino 1.8.x FT897D библиотека CAT интерфейс управления с радио

GND -> Arduino GND
TX -> Arduino pin 2 (можно изменить в библиотеке)
RX -> Arduino pin 3 (можно изменить в библиотеке)

Набор команд:

Чтобы использовать библиотечные функции, вызывайте их, используя выбранный вами идентификатор (т. Е. «Радио», как показано в приведенном выше примере). Список функций выглядит следующим образом:

блокировка вкл / выкл = radio.lock (true / false);
PTT вкл / выкл = радио.PTT (истина / ложь);
Установить частоту = radio.setFreq (желаемая частота - без десятичных знаков);
Установите режим работы = radio.setMode (название режима - например, usb);
Осветлитель вкл / выкл = radio.clar (true / false);
Частота осветлителя = radio.clarFreq (желаемая частота - опять же, без десятичных дробей);
VFO A / B swapping = radio.switchVFO ();
Операция разделения вкл. / Выкл. = Radio.split (true / false);
Направление смещения повторителя (+, -, симплекс) = radio.rptrOffset (+, - или s);
Частота смещения повторителя = radio.rptrOffsetFreq (частота смещения в кГц);
CTCSS / DCS вкл / выкл = radio.squelch (DCS или TEN);
Тон CTCSS / код DCS = radio.squelchFreq (частота, T или D);
Read TX status = radio.chkTX (); - возвращает истину / ложь
Чтение частоты приема и режима = radio.getFreqMode ();

Установка:

Чтобы установить эту библиотеку, просто извлеките заархивированный файл из каталога библиотек в корневом каталоге Arduino IDE

Чтобы проверить ваше физическое соединение с радиоприемником и убедиться, что вы можете # включить библиотеку, предложите вам попробовать пример скетча, который включен в библиотеку.
