
#include "animations/but.c"
#include "animations/artifice.c"
#include "animations/artifice2.c"
#include "animations/open.c"
#include "animations/soccer.c"
#include "animations/time.c"
#include "animations/Water.c"
#include "animations/fire.c"

/*
 * Animation water
 */

int read_water(unsigned long speed_frame){
  
/* Read matrix picture */

if (frame== 0 or (last_frame + speed_frame)< millis()){   
  for(int y=0; y<32; y++){ 
  
              for (int x=0; x<64; x++){
                int pix= y*64+x;
                unsigned int color= water_data[frame][pix];                    // Mettre à jour le nom en fonction de l'animation
                //Serial.println(color,HEX);
                matrix.drawPixel(x, y,color);
                uint32_t color_32 = convert_16bit_color(color);  
                edge_color(x,y,color_32);                                     // anime les rubans LED
                 
                }
   }
   last_frame=millis();
   frame++;
   strip1.show();
   strip2.show();
}
if (frame>=WATER_FRAME_COUNT){if(!bitRead(statut_animation,LOOP)){bitSet(statut_animation,FINISH);}frame=0;}  // Mettre à jour le nom du FRAME_COUNT

}


/*
 * Animation Goal
 */

int read_goal(unsigned long speed_frame){
  
/* Read matrix picture */

if (frame == 0 or (last_frame + speed_frame)< millis()){   
  for(int y=0; y<32; y++){ 
  
              for (int x=0; x<64; x++){
                int pix= y*64+x;
                unsigned int color= but_data[frame][pix];
                //Serial.println(color,HEX);
                matrix.drawPixel(x, y,color);
              
               uint32_t color_32 = convert_16bit_color(color);
               edge_color(x,y,color_32);                          // Anime les rubans Led

              }                                
   }
                 
   last_frame=millis();
   frame++;
   strip1.show();
   strip2.show();
}
if (frame>=BUT_FRAME_COUNT){if(!bitRead(statut_animation,LOOP)){bitSet(statut_animation,FINISH);}frame=0;}
}

/*
 * Animation time
 */

int read_time(unsigned long speed_frame){
  
/* Read matrix picture */

if (frame == 0 or (last_frame + speed_frame)< millis()){   
  for(int y=0; y<32; y++){ 
  
              for (int x=0; x<64; x++){
                int pix= y*64+x;
                unsigned int color= time_data[frame][pix];      // !!! Changer le nom de la data par le nom qui ce trouve dans le fichier
                //Serial.println(color,HEX);
                matrix.drawPixel(x, y,color);
              
               uint32_t color_32 = convert_16bit_color(color);
               edge_color(x,y,color_32);                        // Anime les rubans led

              }                                
   }
                 
   last_frame=millis();
   frame++;
   strip1.show();
   strip2.show();
   
}
if (frame>=TIME_FRAME_COUNT){if(!bitRead(statut_animation,LOOP)){bitSet(statut_animation,FINISH);}frame=0;} // !!! Utiliser le nom du FRAME_COUNT
}

/*
 * Animation soccer
 */

int read_soccer(unsigned long speed_frame){
  
/* Read matrix picture */

if (frame == 0 or (last_frame + speed_frame)< millis()){   
  for(int y=0; y<32; y++){ 
  
              for (int x=0; x<64; x++){
                int pix= y*64+x;
                unsigned int color= soccer_data[frame][pix];      // !!! Changer le nom de la data par le nom qui ce trouve dans le fichier
                //Serial.println(color,HEX);
                matrix.drawPixel(x, y,color);
              
               uint32_t color_32 = convert_16bit_color(color);
               edge_color(x,y,color_32);                        // Anime les rubans led

              }                                
   }
                 
   last_frame=millis();
   frame++;
   strip1.show();
   strip2.show();
   
}
if (frame>=SOCCER_FRAME_COUNT){if(!bitRead(statut_animation,LOOP)){bitSet(statut_animation,FINISH);} else {frame=0;}} // !!! Utiliser le nom du FRAME_COUNT
}

/*
 * Animation open
 */

int read_open(unsigned long speed_frame){
  
/* Read matrix picture */

if (frame == 0 or (last_frame + speed_frame)< millis()){   
  for(int y=0; y<32; y++){ 
  
              for (int x=0; x<64; x++){
                int pix= y*64+x;
                unsigned int color= open_data[frame][pix];      // !!! Changer le nom de la data par le nom qui ce trouve dans le fichier
                //Serial.println(color,HEX);
                matrix.drawPixel(x, y,color);
              
               uint32_t color_32 = convert_16bit_color(color);
               edge_color(x,y,color_32);                        // Anime les rubans led

              }                                
   }
                 
   last_frame=millis();
   frame++;
   strip1.show();
   strip2.show();
   
}
if (frame>=OPEN_FRAME_COUNT){if(!bitRead(statut_animation,LOOP)){bitSet(statut_animation,FINISH);} else {frame=0;}} // !!! Utiliser le nom du FRAME_COUNT
}

/*
 * Animation artifice2
 */

int read_artifice2(unsigned long speed_frame){
  
/* Read matrix picture */

if (frame == 0 or (last_frame + speed_frame)< millis()){   
  for(int y=0; y<32; y++){ 
  
              for (int x=0; x<64; x++){
                int pix= y*64+x;
                unsigned int color= artifice2_data[frame][pix];      // !!! Changer le nom de la data par le nom qui ce trouve dans le fichier
                //Serial.println(color,HEX);
                matrix.drawPixel(x, y,color);
              
               uint32_t color_32 = convert_16bit_color(color);
               edge_color(x,y,color_32);                        // Anime les rubans led

              }                                
   }
                 
   last_frame=millis();
   frame++;
   strip1.show();
   strip2.show();
   
}
if (frame>=ARTIFICE2_FRAME_COUNT){if(!bitRead(statut_animation,LOOP)){bitSet(statut_animation,FINISH);}frame=0;} // !!! Utiliser le nom du FRAME_COUNT
}


/*
 * Animation water
 */

int read_fire(unsigned long speed_frame){
  
/* Read matrix picture */

if (frame== 0 or (last_frame + speed_frame)< millis()){   
  for(int y=0; y<32; y++){ 
  
              for (int x=0; x<64; x++){
                int pix= y*64+x;
                unsigned int color= fire_data[frame][pix];                    // Mettre à jour le nom en fonction de l'animation
                //Serial.println(color,HEX);
                matrix.drawPixel(x, y,color);
                uint32_t color_32 = convert_16bit_color(color);  
                edge_color(x,y,color_32);                                     // anime les rubans LED
                 
                }
   }
   last_frame=millis();
   frame++;
   strip1.show();
   strip2.show();
}
if (frame>=FIRE_FRAME_COUNT){if(!bitRead(statut_animation,LOOP)){bitSet(statut_animation,FINISH);}frame=0;}  // Mettre à jour le nom du FRAME_COUNT

}
