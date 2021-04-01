

uint32_t convert_16bit_color(uint16_t color){

                uint32_t c;


                c = 0x0000000F & color;
                c |= 0x000000F0 & color<<4;              
                c |= 0x00000F00 & color<<4;
                c |= 0x0000F000 & color<<8;
                c |= 0x000F0000 & color<<8; 
                c |= 0x00F00000 & color<<12; 

                return c;  
}

void black_neo(){
  strip1.clear(); 
  strip2.clear(); 
}


void color_neo(uint32_t c){

  for(int y=0; y<LED_COUNT; y++)
  {
  strip1.setPixelColor(y, c);
  strip2.setPixelColor(y, c);
  }

}


void edge_color(int x=0,int y=0,uint32_t color=0 ){  

   if (x==0 and y<31 ){               
                strip1.setPixelColor(y, color);
                }
   if (y==31 && x<9){
                strip1.setPixelColor(y+x,color);                        
              }  
   if (x==63 and y<31 ){ 
                strip2.setPixelColor(y,color);
              }
  if (y==31 && x>52){
                strip2.setPixelColor(x-22, color);                          
              }
}





void colorWipe(uint32_t color) {
  for(int i=0; i<strip1.numPixels(); i++) { // For each pixel in strip...
    strip1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip2.setPixelColor(i, color);         //  Set pixel's color (in RAM)
  }
}
