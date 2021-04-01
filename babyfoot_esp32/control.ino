void play_show(){

  //Serial.println(statut_game);

  if (bitRead(statut_game,START_GAME)){start_play();}
  else if(bitRead(statut_game,RUN)){run_play();}
  else { waiting_screen();}
  
}

void run_play(){

/* wait to start new game */
  if (bitRead(statut_game,GAME_OVER )){
    
    if(bitRead(inputs, EDGE_OK)){statut_game=0x0000;}
    game_over_screen();
  }


/* here you can chose the effect for the end of the macth  */

  else if (bitRead(statut_game,PLAYER_1_WIN) or bitRead(statut_game,PLAYER_2_WIN)){
    if (!bitRead(statut_animation,READ)){frame=0; statut_animation=0x0004;end_animation();}
    else if ( bitRead(statut_animation,FINISH)){statut_animation=0x0000; bitSet(statut_game,GAME_OVER );matrix.fillScreen(0);}
    else {end_animation();}  
  } 

/* here when the system detect "gamelle" chose the animation */

  else if (bitRead(statut_game,GAMELLE1) or bitRead(statut_game,GAMELLE2)){
    if (!bitRead(statut_animation,READ)){frame=0; statut_animation=0x0004;gamelle_animation();}   
    else if ( bitRead(statut_animation,FINISH)){statut_animation=0x0000;matrix.fillScreen(0);}
    else {gamelle_animation();}  
    }

/* here start the animation when there is a goal */

  else if (bitRead(statut_game, GOAL1) or bitRead(statut_game, GOAL2)){
    if (!bitRead(statut_animation,READ)){frame=0; statut_animation=0x0004;but_animation();}
    else if ( bitRead(statut_animation,FINISH)){statut_animation=0x0000;matrix.fillScreen(0);}
    else {but_animation();}
  }


  else {score_screen();}


}


void start_play(){

/* ecrans choix du terrain */

    if(bitRead(statut_game,CHOSE_SIDE)){side_screen();}
    
/* Animation de lancement de la partie */

    else if (!bitRead(statut_animation,READ)){frame=0; statut_animation=0x0004;start_animation();}
    else if (bitRead(statut_animation,FINISH)){bitSet(statut_game, CHOSE_SIDE);matrix.fillScreen(0);}
    else {start_animation();}

    
  }
