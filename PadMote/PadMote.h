
class target
{
	public:
	bool roll;
	unsigned char x,y;
	unsigned char direction;
	unsigned char data;
	unsigned long time;
	unsigned long pointto();
	unsigned long writebyte();
	unsigned long function();
	unsigned long blink();
	unsigned long cursor();
	unsigned long scroll();
	unsigned long clean();
};
