bool play_game(){

/* play the game */

 if(bitRead(statut_game,RUN)){
    if (score_change()){}
    else {demi();
          gamelle();
          but();}
    if(ball==0 and statut_animation==0x0000){ //
      if (score_p1>score_p2){bitSet(statut_game, PLAYER_1_WIN);}
      else{bitSet(statut_game, PLAYER_2_WIN);
      statut_animation=0x0010;
      //bitClear(statut_animation,RUN);
      }
    } 
  }
  
 /* push buttom ok to begin the game */
  
  else if (!bitRead(statut_game,START_GAME)){ 
    if(bitRead(inputs, EDGE_OK)){
    bitSet(statut_game,START_GAME);
    score_p2=0;
    score_p1=0;
    ball=11;
    waiting_goal=0;  
    raz_but();     
    matrix.fillScreen(0);
    }
  }
  
 /* chose the side of play with more or less follow by ok buttom to confirm the choice */ 

   else if (bitRead(statut_game,CHOSE_SIDE)){
   
    if(bitRead(inputs, EDGE_OK)){bitSet(statut_game, RUN);bitClear(statut_game,START_GAME);start_time=millis(); bitClear(statut_game,CHOSE_SIDE);statut_animation=0x0000; matrix.fillScreen(0);raz_but();}
    else if(bitRead(inputs,EDGE_LESS) || bitRead(inputs,EDGE_MORE)){ 
       if(bitRead(statut_game,SWITCH_TEAM)){bitClear(statut_game,SWITCH_TEAM);matrix.fillScreen(0);}
       else if(!bitRead(statut_game,SWITCH_TEAM)){bitSet(statut_game,SWITCH_TEAM);matrix.fillScreen(0);}
    }
   
  }
 
  else if (bitRead(statut_game,START_GAME)){ 
    if(bitRead(inputs, EDGE_OK)){bitSet(statut_game, CHOSE_SIDE);matrix.fillScreen(0);}
  }
  


}


bool score_change(){
  
  if( !bitRead(statut_game,SCORE_CHANGE) and bitRead(inputs,EDGE_OK) ){
    bitSet(statut_game,SCORE_CHANGE);
    return 1;
  }
  else if (bitRead(statut_game,SCORE_CHANGE)){
    
    /* select the player where we want to change the score */
    
    if (!bitRead(statut_game,PLAYER_SELECTED)){
      if ( bitRead(inputs,EDGE_LESS)||bitRead(inputs,EDGE_MORE)){ 
        if (bitRead(statut_game,PLAYER_1)){ bitSet(statut_game,PLAYER_2);bitClear(statut_game,PLAYER_1);}
        else{ bitSet(statut_game,PLAYER_1);bitClear(statut_game,PLAYER_2);}
      }
      if (bitRead(inputs,EDGE_OK)){bitSet(statut_game,PLAYER_SELECTED);}      
    }

    /* When the player is selected we can change his score  enter to validate */

    else {
      if (bitRead(statut_game,PLAYER_1)){
        if ( bitRead(inputs,EDGE_LESS)){ score_p1--;matrix.fillScreen(0);}
        else if (bitRead(inputs,EDGE_MORE)){score_p1++;matrix.fillScreen(0);}        
      }
      if (bitRead(statut_game,PLAYER_2)){
        if ( bitRead(inputs,EDGE_LESS)){ score_p2--;matrix.fillScreen(0);}
        else if (bitRead(inputs,EDGE_MORE)){score_p2++;matrix.fillScreen(0);}        
      }
      if (bitRead(inputs,EDGE_OK)){
        statut_game &= 0xF0FF;                              // END of the score change
      }
    }
    return 1;
  }
  else {return 0;}
    
}

bool gamelle(){

  if (!bitRead(statut_game,GAMELLE1) and !bitRead(statut_game,GAMELLE2)){
    if(bitRead(inputs,EDGE_GAMELLE_P1)){bitSet(statut_game,GAMELLE1); start_gamelle_validation=millis();statut_animation=0x0010;return 1;}
    else if(bitRead(inputs,EDGE_GAMELLE_P2)){bitSet(statut_game,GAMELLE2);start_gamelle_validation=millis();statut_animation=0x0010; return 1;}
  }
  else if ( millis()>(start_gamelle_validation+GAMELLE_VALIDATION) ||  statut_animation==0x0000){
    if(bitRead(statut_game,GAMELLE1)){score_p2--;bitClear(statut_game,GAMELLE1);raz_but();matrix.fillScreen(0);}
    if(bitRead(statut_game,GAMELLE2)){score_p1--;bitClear(statut_game,GAMELLE2);raz_but();matrix.fillScreen(0);}
  return 1;
  }
  else if (bitRead(statut_game,GAMELLE1)|| bitRead (statut_game, GAMELLE2)){return 1;}
  else {return 0;}
  
}

bool but(){
 
 if (!bitRead(statut_game,GOAL1) and !bitRead(statut_game,GOAL2)){
  if(bitRead(inputs,EDGE_GOAL_P1)){bitSet(statut_game,GOAL1);bitClear(statut_game,GAMELLE1);bitClear(statut_game,GAMELLE2);statut_animation=0x0010;return 1;}
  if(bitRead(inputs,EDGE_GOAL_P2)){bitSet(statut_game,GOAL2);bitClear(statut_game,GAMELLE2);bitClear(statut_game,GAMELLE1);statut_animation=0x0010;return 1;}
 }
  
 else if(bitRead(statut_game,GOAL1) and statut_animation==0x0000){
    last_points=1+waiting_goal;
    score_p1=score_p1+1+waiting_goal;
    ball--;
    raz_but();
    bitClear(statut_game,GOAL1); 
    bitClear(statut_game,PLAYER_1);
    bitSet(statut_game,PLAYER_2);
    waiting_goal=0;
    bitClear(statut_game,DEMI);
    }
  else if(bitRead(statut_game,GOAL2) and statut_animation==0x0000){
    last_points=1+waiting_goal;
    score_p2=score_p2+1+waiting_goal;
    ball--;
    raz_but();
    bitClear(statut_game,GOAL2); 
    bitClear(statut_game,PLAYER_2);
    bitSet(statut_game,PLAYER_1);
    waiting_goal=0;
    bitClear(statut_game,DEMI);
  }
  else if ( bitRead(statut_game,GOAL2) || bitRead(statut_game,GOAL1)){return 1;}

 return 0;  
}

/* It is not a beer, french joke */
bool demi(){
  if(!bitRead(statut_game,DEMI)){
    if(bitRead(inputs,LESS) and bitRead(inputs,MORE)){
      if (bitRead(statut_game,PLAYER_2)){score_p1=score_p1-last_points; waiting_goal=last_points;}
      if (bitRead(statut_game,PLAYER_1)){score_p2=score_p2-last_points; waiting_goal=last_points;}
      bitSet(statut_game,DEMI);
      matrix.fillScreen(0);
    }   
  }
}

void raz_but(){
    while(digitalRead(GOAL_RIGHT) || digitalRead(GOAL_LEFT) || digitalRead(GAMELLE_RIGHT)|| digitalRead(GAMELLE_LEFT)){
        digitalWrite(RESET_PIN,0);
        unsigned long over_time=0;
        while(digitalRead(GOAL_RIGHT) || digitalRead(GOAL_LEFT) || digitalRead(GAMELLE_RIGHT)|| digitalRead(GAMELLE_LEFT))
        {
           over_time++;
          if (over_time>1000000){
            break;}
          
          }
        delay(10);
        digitalWrite(RESET_PIN,1);
        delay(10);
    }
}
