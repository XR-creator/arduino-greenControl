/**
  А A
  Б 6
  В B
  Г *
  Д *
  Е E
  Ж *
  З 3
  И *
  К K
  Л 0xCA
  М M
  Н H
  О O
  П *
  Р P
  С C
  Т T
  У 0xF9
  Ф 0xEC
  Х X
  Ц u
  Ч *
  Ш 0xC2
  Щ 0xC2
  Ы *
  Ь b
  Э 0xD6
  Ю 0x7E
  Я *
 */
//
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x38,16,2);

byte symbols[8][8] = {
  {//Г
    B11111,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
  },
  {//Д
    B01111,
    B01001,
    B01001,
    B01001,
    B11001,
    B11111,
    B10001
  },
  {//Ж
    B10101,
    B10101,
    B01110,
    B00100,
    B01110,
    B10101,
    B10101
  },
  {//И
    B10001,
    B10001,
    B10011,
    B10101,
    B11001,
    B10001,
    B10001
  },
  {//П
    B11111,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001
  },
  {//Ч
    B10001,
    B10001,
    B10001,
    B11111,
    B00001,
    B00001,
    B00001
  },
  {//Ы
    B10001,
    B10001,
    B10001,
    B11101,
    B10101,
    B10101,
    B11101
  },
  {//Я
    B11111,
    B10001,
    B10001,
    B11111,
    B00101,
    B01001,
    B10001
  }
};

void displayInit() {  
  lcd.init();                     
  lcd.backlight();
  for (int i = 0; i < 8; i++) {
    lcd.createChar(i, symbols[i]);
  }
  lcd.setCursor(0, 0);
//  displayLCD("Загрузка...");
}

void displayLCD(String text) {
  int len = text.length() + 1;
  char buf[len];
  text.toCharArray(buf, len);
  char optionChar = buf[0];
  for (int i = 0;i < len - 1;i++) {
    switch(buf[i])
      {
        case -48: break;                      case -47: break;
        case -112: lcd.print('A');break;      case -80: lcd.print('A');break;
        case -111: if(optionChar == -48)lcd.print('6');else lcd.print('E');break; case -79: lcd.print('6');break;
        case -110: lcd.print('B');break;      case -78: lcd.print('B');break;
        case -109: lcd.write(byte(0));break;  case -77: lcd.write(byte(0));break;
        case -108: lcd.write(byte(1));break;  case -76: lcd.write(byte(1));break;
        case -107: lcd.print('E');break;      case -75: lcd.print('E');break;
        case -127: if(optionChar == -48)lcd.print('E');else lcd.print('C');break;
        case -106: lcd.write(byte(2));break;  case -74: lcd.write(byte(2));break;
        case -105: lcd.print('3');break;      case -73: lcd.print('3');break;
        case -104: lcd.write(byte(3));break;  case -72: lcd.write(byte(3));break;
        case -103: lcd.write(byte(3));break;  case -71: lcd.write(byte(3));break;
        case -102: lcd.print('K');break;      case -70: lcd.print('K');break;
        case -101: lcd.write(0xCA);break;     case -69: lcd.write(0xCA);break;
        case -100: lcd.print('M');break;      case -68: lcd.print('M');break;
        case -99: lcd.print('H');break;       case -67: lcd.print('H');break;
        case -98: lcd.print('O');break;       case -66: lcd.print('O');break;
        case -97: lcd.write(byte(4));break;   case -65: lcd.write(byte(4));break;
        case -96: lcd.print('P');break;       case -128: lcd.print('P');break;
        case -95: lcd.print('C');break;       
        case -94: lcd.print('T');break;       case -126: lcd.print('T');break;
        case -93: lcd.write(0xBF);break;      case -125: lcd.write(0xBF);break;
        case -92: lcd.write(0xEC);break;      case -124: lcd.write(0xEC);break;
        case -91: lcd.print('X');break;       case -123: lcd.print('X');break;
        case -90: lcd.write(0xF9);break;      case -122: lcd.write(0xF9);break;
        case -89: lcd.write(byte(5));break;   case -121: lcd.write(byte(5));break;
        case -88: lcd.write(0xC2);break;      case -120: lcd.write(0xC2);break;
        case -87: lcd.write(0xC2);break;      case -119: lcd.write(0xC2);break;
        case -86: lcd.print('b');break;       case -118: lcd.print('b');break;
        case -85: lcd.write(byte(6));break;   case -117: lcd.write(byte(6));break;
        case -84: lcd.print('b');break;       case -116: lcd.print('b');break;
        case -83: lcd.write(0xD6);break;      case -115: lcd.write(0xD6);break;
        case -82: lcd.write(0x7E);break;      case -114: lcd.write(0x7E);break;
        case -81: lcd.write(byte(7));break;   case -113: lcd.write(byte(7));break;
        default: lcd.print(buf[i]); break;
      };

      optionChar = buf[i];
  }
}

void displayLCD(String text, int line, int column) {
  lcd.setCursor(column, line);
  displayLCD(text);
}

void displayLCDClear() {
  lcd.clear();
}
