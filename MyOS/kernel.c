/*
* THESE ARE COLOR CODES THAT APPLY FOR LINES 12, 14, AND 16
*
* 0x04 is red
* 0x07 is white
* 0x02 is green
*/

kmain(){
  char* vidmem=(char*)0xb8000;
  vidmem[0]='H';
  vidmem[1]=0x04;
  vidmem[2]='I';
  vidmem[3]=0x07;
  vidmem[4]='!';
  vidmem[5]=0x02;
}
