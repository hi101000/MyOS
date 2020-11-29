/*
* THESE ARE COLOR CODES THAT APPLY FOR LINES 12, 14, AND 16
*
* 0x04 is red
* 0x07 is white
* 0x02 is green
*/

#include "keyboard.h"
#include "kernel.h"


#define WHITE 0x07 // white on black text
#define RED   0x04 // red on black text
#define GREEN 0x02 // green on black text

void clear_screen();
unsigned int print(char *message, unsigned int line);
void update_cursor(int row, int col);
void k_delay(int seconds);
void whileloop();
void kernel_entry();
void print_int(int toprint);

long double add(long double x, long double y){return x+y;}
long double sub(long double x, long double y){return x-y;}
long double mul(long double x, long double y){return x*y;}
long double div(long double x, long double y){return x/y;}

kmain(){
  kernel_entry();
  k_delay(5);
  clear_screen();
  print("HI, World!                        ", 0);
  k_delay(5);
  clear_screen();
  print_int(12);
}

int abs(int x){
  if(x>=0){
    return x;
  }
  else{
    return -x;
  }
}

unsigned int print(char *message, unsigned int line) // the message and then the line #
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // check for a new line
		{
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=WHITE;
			i++;
		};
	};

	return(1);
};

void clear_screen() // clear the entire text screen
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE;
		i++;
	};
};

void k_delay(int seconds){
	unsigned long int count=99999999,i,j;
	unsigned long long int instruct=0;
	
	for(i=0;i<seconds;i++){
	    for(j=0;j<count;j++){instruct++;};
	}
}



uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

//clear video buffer array
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for(i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
}

//initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;  //point vga_buffer pointer to VGA_ADDRESS 
  clear_vga_buffer(&vga_buffer, fore_color, back_color);  //clear buffer
}



uint32 strlen(const char* str)
{
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}

uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

//print string by calling print_char

//print int by converting it into string
//& then printing string
void print_int(int toprint){
	char* willprint;
	itoa(toprint, willprint);
	print(willprint, 0);
}

void kernel_entry()
{
  //first init vga with fore & back colors
  init_vga(WHITE, BLACK);

  //assign each ASCII character to video buffer
  //you can change colors here
  vga_buffer[0] = vga_entry('H', WHITE, BLACK);
  vga_buffer[1] = vga_entry('e', WHITE, BLACK);
  vga_buffer[2] = vga_entry('l', WHITE, BLACK);
  vga_buffer[3] = vga_entry('l', WHITE, BLACK);
  vga_buffer[4] = vga_entry('o', WHITE, BLACK);
  vga_buffer[5] = vga_entry(' ', WHITE, BLACK);
  vga_buffer[6] = vga_entry('W', WHITE, BLACK);
  vga_buffer[7] = vga_entry('o', WHITE, BLACK);
  vga_buffer[8] = vga_entry('r', WHITE, BLACK);
  vga_buffer[9] = vga_entry('l', WHITE, BLACK);
  vga_buffer[10] = vga_entry('d', WHITE, BLACK);
}
