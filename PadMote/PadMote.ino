#define DBGA(x)	if (!(x)) return -1;
#include <LiquidCrystal.h>		//include libary code~~~
#include "PadMote.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char buffer[20];

target function;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // set up the boder rate of serial port 0 to 9600
  Serial.begin(9600);

  /* init function */
  function.roll = false;
  function.x = 0;
  function.y = 0;
}

void loop() {
	if (Serial.available())
	{
		if (function.function() != 0)
		{
			lcd.clear();
			lcd.home();
			/* things comes wrong , should be alart */
			blink();
		}
	}
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 1);
	// print the number of seconds since reset:
	lcd.print(millis()/1000);
}

unsigned long blink()
{
	pinMode(13, OUTPUT);
	while (1)
	{
		digitalWrite(13, HIGH);
		delay(1000);
		digitalWrite(13, LOW);
		delay(1000);
	}

	return -1;
}

unsigned long target::pointto()
{
	DBGA(Serial.read() == 2);

	this->x = Serial.read();
	this->y = Serial.read();

	/* judge the data is valid */
	DBGA((this->x < 16) && (this->x >= 0));
	DBGA((this->y == 0) || (this->y == 1));

	/* point to the position */
	lcd.setCursor(x,y);

	return 0;
}

unsigned long target::writebyte()
{
	DBGA(Serial.read() == 1);

	this->data = Serial.read();
	lcd.write(this->data);

	return 0;
}

unsigned long target::blink()
{
	DBGA(Serial.read() == 2);

	if (Serial.read() == 0xff)
	{
		this->time = (int) Serial.read();		//read blink time
		lcd.blink();
	}
	else if(Serial.read() == 0)
	{
		(void) Serial.read();					//drop the data
		lcd.noBlink();
	}
	else
	{
		return -1;								//thins wrong
	}
	
	return 0;
}

unsigned long target::cursor()
{
	DBGA(Serial.read() == 1);

	if (Serial.read() == 0xff)
	{
		lcd.cursor();
	}
	else if (Serial.read() == 0x00)
	{
		lcd.noCursor();
	}
	else
	{
		return  -1;
	}

	return 0;
}

unsigned long target::scroll()
{
	unsigned char way;

	DBGA(Serial.read() == 3);

	if (Serial.read() == 0xff)
	{
		this->roll = true;
		way = Serial.read();

		if (way == 0x00)
		{
			this->direction = 0;
			lcd.scrollDisplayLeft();
		}
		else (way == 0xff)
		{
			this->direction = 1;
			lcd.scrollDisplayRight();
		}
		lcd.autoscroll();
	}
	else if (Serial.read() == 0)
	{
		this->roll = false;
		(void) Serial.read();			//drop data
		lcd.noAutoscroll();
	}
	else
	{
		return -1;
	}

	return 0;
}

unsigned long target::clean()
{
	DBGA(Serial.read() == 1);
	DBGA(Serial.read() == 0);
	lcd.clear();
	lcd.home();

	return 0;
}

unsigned long target::function()
{
	/* wait for data string */
	buffer[0] = Serial.read();
	while (buffer[0] == 0)
	{
		buffer[0] = Serial.read();
	}
	
	switch (buffer[0])
	{
		case 0 : DBGA(0);
		case 1 : return this->pointto();
		case 2 : return this->writebyte();
		case 3 : return this->blink();
		case 4 : return this->cursor();
		case 5 : return	this->scroll();
		case 6 : return this->clean();

		default :
				 break;
	}

	return -1;
}



