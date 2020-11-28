/*
* THESE ARE COLOR CODES THAT APPLY FOR LINES 12, 14, AND 16
*
* 0x04 is red
* 0x07 is white
* 0x02 is green
*/
#define WHITE 0x07 // white on black text
#define RED   0x04 // red on black text
#define GREEN 0x02 // green on black text

void clear_screen();
unsigned int print(char *message, unsigned int line);
void update_cursor(int row, int col);
void k_delay(int seconds);

kmain(){
  clear_screen();
  print("Hello, World!                     ", 0);
  k_delay(5);
  clear_screen();
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
