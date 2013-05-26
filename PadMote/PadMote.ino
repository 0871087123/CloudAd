#define DBGA(x)	if (!(x)) return -1;
#include <LiquidCrystal.h>		//include libary code~~~
#include "PadMote.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char buffer[60];
int timeoutcount = 100;			//Serial timeout 0.5 second

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

  /* low Led */
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
	if (Serial.available())
	{
		if (function.function() != 0)
		{
			/* things comes wrong , should be alart */
			lcd.display();
			lcd.clear();
			lcd.home();
			blink();
		}
	}
}

char readByte()
{
	int i = 0;
	/* check the serial data per 5 miliseconds */
	while (!Serial.available())
	{
		if (i > timeoutcount)
		{
			return 0;
		}
		delay(5);
		i++;
	}

	return Serial.read();
}

unsigned long blink()
{
	int i;
	pinMode(13, OUTPUT);
	for (i = 0; i < 2; i++)
	{
		digitalWrite(13, HIGH);
		delay(1000);
		digitalWrite(13, LOW);
		delay(1000);
	}

	return 0;
}

unsigned long target::pointto()
{
	DBGA(readByte() == 0x02);	//data length is 2 byte

	this->x = readByte();
	this->y = readByte();

	/* judge the data is valid */
	DBGA((this->x < 16) && (this->x >= 0));
	DBGA((this->y == 0) || (this->y == 1));

	/* point to the position */
	lcd.setCursor(x,y);

	return 0;
}

unsigned long target::writebyte()
{
	DBGA(readByte() == 1);

	this->data = readByte();
	lcd.write(this->data);

	return 0;
}

unsigned long target::blink()
{
	DBGA(readByte() == 2);

	if (readByte() == 0xff)
	{
		this->time = (int) readByte();		//read blink time
		lcd.blink();
	}
	else if(readByte() == 0)
	{
		(void) readByte();					//drop the data
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
	DBGA(readByte() == 1);

	if (readByte() == 0xff)
	{
		lcd.cursor();
	}
	else if (readByte() == 0x00)
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

	DBGA(readByte() == 3);

	if (readByte() == 0xff)
	{
		this->roll = true;
		way = readByte();

		if (way == 0x00)
		{
			this->direction = 0;
			lcd.scrollDisplayLeft();
		}
		else if (way == 0xff)
		{
			this->direction = 1;
			lcd.scrollDisplayRight();
		}
		lcd.autoscroll();
	}
	else if (readByte() == 0)
	{
		this->roll = false;
		(void) readByte();			//drop data
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
	DBGA(readByte() == 1);
	DBGA(readByte() == 0);
	lcd.clear();
	lcd.home();

	return 0;
}

unsigned long target::printf()
{
	unsigned char length = 0;
	int i;
	length = readByte();

	DBGA(length <= 32);

	for (i = 0; i < length; i++)
	{
		buffer[i] = readByte();
	}

	lcd.print(buffer);

	return 0;
}

unsigned long target::function()
{
	/* wait for data string */
	buffer[0] = readByte();
	
	switch (buffer[0])
	{
		case 0 : return 0;
		case 1 : return this->pointto();
		case 2 : return this->writebyte();
		case 3 : return this->blink();
		case 4 : return this->cursor();
		case 5 : return	this->scroll();
		case 6 : return this->clean();
		case 8 : return this->printf();

		default :
				 break;
	}

	return -1;
}



