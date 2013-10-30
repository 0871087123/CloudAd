Cloud AD
====================
Post Your Information to arduino via Cloud Server and Raspberry Pi
--------------------

How To Use it ?
-------------------
You need:

1 a Linux Server, Use VPS because it's cheap.

2 a RaspberryPi, provide internet accessing.

3 a arduino board, i use mega 2560 in my case.

4 cross-compiler for Raspberry Pi, and your need to edit arm-linux.sh, change the PATH to your PATH


Your Hardware connection should be:

	 
	 +-----------+     +--------------+     +--------------+
	 |  Arduino  |     |              |     |              |
	 |   with	 +-----+ Raspberry Pi +-----+   Network    |
	 |   LCD     |     |              |     |   access     |
	 +-----------+     +--------------+     +--------------+
	
Step:

1 cd to VPS_Server , and make

2 package a tarboll , include VPS_Server/config the directory and VPS_Server/VCloudd the ELF

3 cd to Raspberry_Pi, import enviorment virables use "sh arm-linux.sh", and then make

4 copy the Raspberry_Pi/RasDaemon and Raspberry_Pi/run.sh to your raspberry pi

5 cd to PadMote and download PadMote.ino to your arudino board, notice that if your arduino board is not Mega 2560, your need check this program and change it to fit your LCD port.

6 after download program to your arduino board, you can use TEST_PadMote to test your arduino board, notice your should have a usb-serialport connection with arduino board

7 start daemon in your VPS Server, use option "-debug" to see whether it runs well or not

8 start daemon in your Raspberry pi, use option "-debug" to see whether it runs well or not


