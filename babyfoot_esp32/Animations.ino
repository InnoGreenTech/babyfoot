


/*
 * Ecran d'affichage du score
 */


void score_screen(){

  /* choix de la position du texte en fonction du choix de terrain */
  
  if ((last_frame + 100)< millis()){
      matrix.setTextSize(1);
    
      if(bitRead(statut_game,SWITCH_TEAM)){
          matrix.setCursor(2,1);  
          matrix.setTextColor(CYAN,BLACK);
          matrix.print("GUEST");
          matrix.setCursor(36,1);
          matrix.setTextColor(MAGENTA,BLACK);
          matrix.print("HOME");    
      }
    
      else{
          matrix.setCursor(4,1);  
          matrix.setTextColor(MAGENTA,BLACK);
          matrix.print("HOME");
          matrix.setCursor(34,1);
          matrix.setTextColor(CYAN,BLACK);
          matrix.print("GUEST");
      }
    
        matrix.setTextSize(2);
      
      /* Score player 1 */
    
      if (bitRead(statut_game,SCORE_CHANGE)) {
        if (bitRead(statut_game,PLAYER_1)){
        matrix.setTextColor(RED,BLACK);}
        else {matrix.setTextColor(BLACK,BLACK);}
      }
      else {matrix.setTextColor(WHITE,BLACK);}   
    
      
      if (score_p1>9 or score_p1 < 0){matrix.setCursor(0,9);}
      else {matrix.setCursor(8,9);}
      matrix.print(score_p1);
    
      /* Score player 2 */
      
      if (bitRead(statut_game,SCORE_CHANGE)) {
        
        if (bitRead(statut_game,PLAYER_2)){
        matrix.setTextColor(RED,BLACK);}
        else {matrix.setTextColor(BLACK,BLACK);}
      }
      else {matrix.setTextColor(WHITE,BLACK);}
      
      if (score_p2>9 or score_p2 < 0){matrix.setCursor(40,9);}
      else {matrix.setCursor(46,9);}
      matrix.print(score_p2);
    
    
      /* rest ball */
      matrix.drawRect(24, 11, 15, 11,YELLOW);
      matrix.setTextSize(1);
      matrix.setTextColor(YELLOW,BLACK);
      if (ball>9 or ball < 0){matrix.setCursor(26,13);}
      else {matrix.setCursor(29,13);}
      matrix.print(ball);
    
       /* Demi ball */
      if (waiting_goal>0){
        matrix.setTextSize(1);
        matrix.setTextColor(RED,BLACK);
        if (waiting_goal>9 or waiting_goal < 0){matrix.setCursor(26,23);}
        else {matrix.setCursor(30,23);}
        matrix.print(waiting_goal);
      }
    
      /* Time duration game */
    
      else{
      matrix.setTextSize(0);
      matrix.setTextColor(GREEN,BLACK);
      matrix.setCursor(12,24);
      matrix.print(duration()); }

      /* Choix des couleurs des rubans LED */

      if (waiting_goal>0){                              // si demi
        color_neo(YELLOW_32);
      }
      else if (bitRead(statut_game,SCORE_CHANGE)){     //changement de Score
        color_neo(CYAN_32);
      }
      else {color_neo(0x00FFFFFF);}                   //SINON BLANC

      strip1.show();
      strip2.show();      
      last_frame=millis();

    }    
  
 }



/* 
 *  Ecran du choix du côté de terrain 
 */
 

void side_screen(){

  matrix.setTextSize(1);

  if(bitRead(statut_game,SWITCH_TEAM)){
      matrix.setCursor(2,2);  
      matrix.setTextColor(BLUE,BLACK);
      matrix.print("GUEST");
      matrix.setCursor(36,2);
      matrix.setTextColor(RED,BLACK);
      matrix.print("HOME");
  }

  else{
      matrix.setCursor(4,1);  
      matrix.setTextColor(RED,BLACK);
      matrix.print("HOME");
      matrix.setCursor(34,2);
      matrix.setTextColor(BLUE,BLACK);
      matrix.print("GUEST");
  }

  matrix.setCursor(11,12);
  matrix.setTextColor(GREEN,BLACK);
  matrix.print("OK pour");
  matrix.setCursor(11,22);
  matrix.print("valider");


  
  
}

/*
 *  Ecran d'attente 
 */

void waiting_screen(){
  
  statut_animation=LOOP;
  read_fire(200);
  if(play_run==0){DFPlayer.play(2);play_run=1;}
  else if(DFPlayer.readType()==DFPlayerPlayFinished){play_run=0;}
  
 }

/*
 *  Ecran de lancement d'une nouvelle partie
 */
 
void start_animation(){
   play_run=0;
   if(frame==1){DFPlayer.play(1);}
   read_open(100);
}

/*
 *  Animation de fin de partie
 */

void end_animation(){
  
  if(frame==1){DFPlayer.playMp3Folder(2);}
  if(bitRead(statut_game,PLAYER_1_WIN)){
       read_artifice2(200);}
  else {read_soccer(200);}
  
 }

 /*
  * Animation d'une gamelle
  */

void gamelle_animation(){
    if(frame==1){DFPlayer.play(4);}
    read_time(100);
  
 }

 /*
  *  Animation sur un but
  */
  
void but_animation(){
    if(frame==1){DFPlayer.play(3);}
    read_goal(100);  
}


/*
 *  Ecran Game over
 */

void game_over_screen(){
  
  if ((last_frame + 100)< millis()){
      matrix.setTextSize(1);
    
      if(bitRead(statut_game,SWITCH_TEAM)){
          matrix.setCursor(2,1);  
          matrix.setTextColor(CYAN,BLACK);
          matrix.print("GUEST");
          matrix.setCursor(36,1);
          matrix.setTextColor(MAGENTA,BLACK);
          matrix.print("HOME");
    
      }
    
      else{
          matrix.setCursor(4,1);  
          matrix.setTextColor(MAGENTA,BLACK);
          matrix.print("HOME");
          matrix.setCursor(34,1);
          matrix.setTextColor(CYAN,BLACK);
          matrix.print("GUEST");
      }
    
        matrix.setTextSize(2);
      
      /* Score player 1 */
    
      if (bitRead(statut_game,SCORE_CHANGE)) {
        if (bitRead(statut_game,PLAYER_1)){
        matrix.setTextColor(RED,BLACK);}
        else {matrix.setTextColor(BLACK,BLACK);}
      }
      else {matrix.setTextColor(WHITE,BLACK);}   
    
      
      if (score_p1>9 or score_p1 < 0){matrix.setCursor(0,9);}
      else {matrix.setCursor(8,9);}
      matrix.print(score_p1);
    
      /* Score palyer 2 */
      
      if (bitRead(statut_game,SCORE_CHANGE)) {
        
        if (bitRead(statut_game,PLAYER_2)){
        matrix.setTextColor(RED,BLACK);}
        else {matrix.setTextColor(BLACK,BLACK);}
      }
      else {matrix.setTextColor(WHITE,BLACK);}
      
      if (score_p2>9 or score_p2 < 0){matrix.setCursor(40,9);}
      else {matrix.setCursor(46,9);}
      matrix.print(score_p2);  
       
      /* Time duration party */
    
      matrix.setTextSize(1);
      matrix.setTextColor(RED,BLACK);
      matrix.setCursor(6,24);
      matrix.print("GAME OVER"); 

      color_neo(RED_32);
      
      strip1.show();
      strip2.show();
      
      last_frame=millis();

    }
      
 }
