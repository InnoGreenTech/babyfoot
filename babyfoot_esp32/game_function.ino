String duration(){
  unsigned long convert_time;
  String duration_game;
  String s;
  String h;
  String m;
  //if( bitRead(statut_game,START_GAME)){ start_time=millis();bitClear(statut_game,START_GAME);}
  convert_time=(millis()-start_time)/1000;
  int minutes= floor(convert_time/60);
  int seconde= convert_time-(minutes*60);
  int heures=0;
  if(minutes>61){ heures= floor(minutes/60); minutes= minutes-(heures*60);}
  s=seconde;
  if(seconde<10){s="0"+s;}
  m=minutes;
  if(minutes<10){ m= "0"+ m;}

  h = heures;
   
  duration_game = h + ":" + m + ":" + s;

  return duration_game;
}
