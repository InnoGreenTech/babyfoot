void read_inputs(){
  
  
  if (less_buttom()){
    if(!bitRead(inputs,LESS)){bitSet(inputs,LESS);bitSet(inputs,EDGE_LESS);}
    else{bitClear(inputs,EDGE_LESS);}
  }
  else {bitClear(inputs,LESS);bitClear(inputs,EDGE_LESS);}
  
  if(more_buttom()){
    if(!bitRead(inputs,MORE)){bitSet(inputs,MORE);bitSet(inputs,EDGE_MORE);}
    else{bitClear(inputs,EDGE_MORE);}
  }
  else {bitClear(inputs,MORE);bitClear(inputs,EDGE_MORE);}
  
  
  if(ok_buttom()){
    if(!bitRead(inputs,OK)){bitSet(inputs,OK);bitSet(inputs,EDGE_OK);}
    else{bitClear(inputs,EDGE_OK);}
  }  
  else {bitClear(inputs,OK);bitClear(inputs,EDGE_OK);}
  
  //if(bitRead(statut_game, SWITCH_TEAM)){
        
    if(goal_right()){
      
      if(!bitRead(inputs,GOAL_P2)){bitSet(inputs,GOAL_P2);bitSet(inputs,EDGE_GOAL_P2);}
      else{bitClear(inputs,EDGE_GOAL_P2);}
    }
    else{bitClear(inputs,GOAL_P2);bitClear(inputs,EDGE_GOAL_P2);}

    if(gamelle_right()){
      if(!bitRead(inputs,GAMELLE_P2)){bitSet(inputs,GAMELLE_P2);bitSet(inputs,EDGE_GAMELLE_P2);}
      else{bitClear(inputs,EDGE_GAMELLE_P2);}
    }
    else{bitClear(inputs,GAMELLE_P2);bitClear(inputs,EDGE_GAMELLE_P2);}

    if(goal_left()){
      if(!bitRead(inputs,GOAL_P1)){bitSet(inputs,GOAL_P1);bitSet(inputs,EDGE_GOAL_P1);}
      else{bitClear(inputs,EDGE_GOAL_P1);}
    }
    else{bitClear(inputs,GOAL_P1);bitClear(inputs,EDGE_GOAL_P1);}

    if(gamelle_left()){
      if(!bitRead(inputs,GAMELLE_P1)){bitSet(inputs,GAMELLE_P1);bitSet(inputs,EDGE_GAMELLE_P1);}
      else{bitClear(inputs,EDGE_GAMELLE_P1);}
    }
    else{bitClear(inputs,GAMELLE_P1);bitClear(inputs,EDGE_GAMELLE_P1);} 
  //}
  /*else{   
     
     if(goal_left()){
      if(!bitRead(inputs,GOAL_P2)){bitSet(inputs,GOAL_P2);bitSet(inputs,EDGE_GOAL_P2);}
      else{bitClear(inputs,EDGE_GOAL_P2);}
    }
    else{bitClear(inputs,GOAL_P2);bitClear(inputs,EDGE_GOAL_P2);}

    if(gamelle_left()){
      if(!bitRead(inputs,GAMELLE_P2)){bitSet(inputs,GAMELLE_P2);bitSet(inputs,EDGE_GAMELLE_P2);}
      else{bitClear(inputs,EDGE_GAMELLE_P2);}
    }
    else{bitClear(inputs,GAMELLE_P2);bitClear(inputs,EDGE_GAMELLE_P2);}

    if(goal_right()){
      if(!bitRead(inputs,GOAL_P1)){bitSet(inputs,GOAL_P1);bitSet(inputs,EDGE_GOAL_P1);}
      else{bitClear(inputs,EDGE_GOAL_P1);}
    }
    else{bitClear(inputs,GOAL_P1);bitClear(inputs,EDGE_GOAL_P1);}

    if(gamelle_right()){
      if(!bitRead(inputs,GAMELLE_P1)){bitSet(inputs,GAMELLE_P1);bitSet(inputs,EDGE_GAMELLE_P1);}
      else{bitClear(inputs,EDGE_GAMELLE_P1);}
    }
    else{bitClear(inputs,GAMELLE_P1);bitClear(inputs,EDGE_GAMELLE_P1);}    
  }*/

//Serial.print(bitRead(inputs,GOAL_P1));Serial.print(bitRead(inputs,GAMELLE_P1));Serial.print(bitRead(inputs,GOAL_P2));Serial.println(bitRead(inputs,GAMELLE_P2));

}


bool less_buttom(){
  int read_buttom=touchRead(LESS_BUTTOM);

  if(read_buttom<SENS_SET){
    less_buttom_start++;
  }
  else if (read_buttom>SENS_SET and less_buttom_start>0){less_buttom_start--; }

  if(less_buttom_start>DELAY_BUTTOM){
    return 1;
  }
  else if(less_buttom_start<=0) { return 0;}  
  else {return bitRead(inputs,LESS);}
  
}

bool more_buttom(){
 
  int read_buttom=touchRead(MORE_BUTTOM);

  if(read_buttom<SENS_SET){
    more_buttom_start++;
  }
  else if (read_buttom>SENS_SET and more_buttom_start>0){more_buttom_start--; }

  if(more_buttom_start>DELAY_BUTTOM){
    return 1;
  }
  else if(more_buttom_start<=0) { return 0;}  
  else {return bitRead(inputs,MORE);}
   
}

bool ok_buttom(){
  int read_buttom=touchRead(OK_BUTTOM);

  if(read_buttom<SENS_SET){
    ok_buttom_start++;
  }
  else if (read_buttom>SENS_SET and ok_buttom_start>0){ok_buttom_start--; }

  if(ok_buttom_start>DELAY_BUTTOM){
    return 1;
  }
  else if(ok_buttom_start<=0) { return 0;}  
  else {return bitRead(inputs,OK);}
    
}

bool goal_right(){
  if (digitalRead(GOAL_RIGHT)){return 1;}
  else{return 0;}
}


bool goal_left(){
  if (digitalRead(GOAL_LEFT)){return 1;}
  else{return 0;}
}

bool gamelle_right(){
  if (digitalRead(GAMELLE_RIGHT)){return 1;}
  else{return 0;}
}

bool gamelle_left(){
  if (digitalRead(GAMELLE_LEFT)){return 1;}
  else{return 0;}
}
