/*
 * HTP.c
 *
 * Created: 19-07-2018 18:18:18
 *  Author: Akshit Bansal
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void initialize(void)
{
	LCD_4bitcommand(0x02);
	LCD_4bitcommand(0x28);
	LCD_4bitcommand(0x06);
	LCD_4bitcommand(0x0c);
}
void LCD_8bitcommand(unsigned int cmd)
{
	PORTD = (0x04|cmd);
	_delay_ms(1);
	PORTD = (0x00|cmd);
	_delay_ms(1);
}
void LCD_8bitdata(unsigned int data)
{
    PORTD=(0x05|data);	
	_delay_ms(1);
	PORTD = (0x01|data);
	_delay_ms(1);
}
void LCD_4bitcommand(unsigned int command)
{
	unsigned int UN,LN;
	UN = (command & 0xf0);
	LCD_8bitcommand(UN);
	LN = ((command<<4) & 0xf0);
	LCD_8bitcommand(LN);
}
void LCD_4bitdata(int data)
{
	unsigned int UN,LN;
	UN = (data & 0xf0);
	LCD_8bitdata(UN);
	LN = ((data<<4) & 0xf0);
	LCD_8bitdata(LN);
}
void lcd_num(unsigned int num)
{ 
	unsigned int i = 0;
	if(num == 0)
	{
		LCD_4bitdata(48);
	}	
while( num !=0)
{
	i = num%10;
	LCD_4bitdata(i+48);
	num = num/10;
	_delay_ms(1);
}
	LCD_4bitcommand(0x06);	
}
void lcd_str( char *str)
{
	unsigned int i = 0;
	while(str[i] != '\0')
	{
		LCD_4bitdata(str[i]);
		_delay_ms(1);
		i++;
	}
}
int main(void)
{
  int flag,count,count1=0,count2=0;
        DDRA=0b11111100;//sensor
	DDRD=0xff;      //lcd
	_delay_ms(1000);
	initialize();
	LCD_4bitcommand(0x80);
	lcd_str("WELCOME");
	_delay_ms(2000);
	LCD_4bitcommand(0x01);
	while(1)
	{if(PINA==0x00)
	    {
		 LCD_4bitcommand(0x80);
		 lcd_str("enter");
		 _delay_ms(100);
	     //LCD_4bitcommand(0x01);
		  }
		else if(PINA==0x01)
		{   flag=1; }
		else if(PINA==0b00000010)
		{   flag=2;}
			
		if(flag==1)
		{
      if(PINA==0b00000010)
		   { count1++;
         LCD_4bitcommand(0x80);
		     lcd_str("Person Entered");
		     _delay_ms(500);
	       LCD_4bitcommand(0x01);
		     flag=21;
		   }
     }
		if(flag==11)
		{
		 LCD_4bitcommand(0x04);	 
		 LCD_4bitcommand(0xc1);
		 lcd_num(count1);
		 _delay_ms(500);
	     LCD_4bitcommand(0x01);
		 }
		 if(flag==2)
		{if(PINA==0b00000001)
		{ count2++;
         LCD_4bitcommand(0x80);
		 lcd_str("Person Left");
		 _delay_ms(500);
	     LCD_4bitcommand(0x01);
		 flag=21;
		}}
		if(flag==21)
		{count=count1-count2;
		 if(count==0)
		 {       LCD_4bitcommand(0x01);
			 LCD_4bitcommand(0x06);
			 LCD_4bitcommand(0x80);
			 lcd_str("HALL EMPTY");
		 }
		 else
		 {
     LCD_4bitcommand(0x06);	
		 LCD_4bitcommand(0xc1);
		 lcd_str("Head Count");
		 LCD_4bitcommand(0x04);
		 LCD_4bitcommand(0xcc);
		 lcd_num(count);
		 _delay_ms(100);
	     //LCD_4bitcommand(0x01);
       }
     }
  }
}
