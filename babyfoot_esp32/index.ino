
void indexRoot(){


              String lecture="";
              if ( server.hasArg("RAZ")) 
              {      
                ESP.restart();
              }

              if ( server.hasArg("LED")) 
              {   
                  lecture=   server.arg("LED");
                  led_brightness = lecture.toInt();
                  strip1.setBrightness(led_brightness);
                  strip2.setBrightness(led_brightness);
                  EEPROM.write(LED_BRIGHTNESS,led_brightness);  // Réglage du pointeur sur l'adresse mémoire
              }

              if ( server.hasArg("MATRIX")) 
              {   
                  lecture=   server.arg("MATRIX");
                  matrix_brightness= lecture.toInt();
                  matrix.setBrightness(matrix_brightness);
                  EEPROM.write(MATRIX_BRIGHTNESS,matrix_brightness);  // Réglage du pointeur sur l'adresse mémoire
              }

              if ( server.hasArg("VOLUME")) 
              {   
                  lecture=   server.arg("VOLUME");
                  set_volume= lecture.toInt();
                  DFPlayer.volume(set_volume);
                  EEPROM.write(SET_VOLUME,set_volume);  // Réglage du pointeur sur l'adresse mémoire
              }

               EEPROM.commit();
               server.send ( 200, "text/html", indexPage() );   // envoi de la page
                }
  

String indexPage(){
                    String page =F("<!DOCTYPE html> <html lang=fr-FR><head><meta charset='utf-8'><link rel='stylesheet'type='text/css'href='style.css'><title>Babyfoot</title><meta http-equiv='Refresh' content='30; url=index.html' /></head>");
                           page +=F("<body>");
                           page +=F("<nav> <ul id='menu'><li><a href='index.html'> Accueil </a></li><li><a href='firmware'> Update </a></li</ul></nav>");
                          
                           page +=F("<div id='page'>");
                           
                           page +=F("<header><h1>Babyfoot</h1></header>");

                           page +=F("<div id='corp'>");
                           page +=F("<section id='datedujour'><h2>");
                           page +=NTP.getDateStr();
                           page +=F("</h2><h3>");
                           page +=NTP.getTimeStr();
                           page +=F("</h3>");
                           page +=F("<Table><tr><td>Joueur 1:</td><td></td><td>");
                           page +=score_p1;
                           page +=F("</td></tr><tr><td>Joueur 2:</td><td></td><td>");
                           page +=score_p2;
                           page +=F("</td></tr><tr><td>Balles restantes:</td><td></td><td>");
                           page +=ball;
                           page +=F("</td></tr><tr><td>Demi:</td><td></td><td>");
                           page +=waiting_goal;
                           page +=F("</td></tr></tr></Table></section>");
      
                           page +=F("<section id='Statut'><h2> Réglage </h2>");
                           page +=F("<form method='post' accept='' >");
                           page +=F("<table><tr><td>Luminosité écran (1->250):</td><td></td><td>");
                           page +=F("<label></label><input type='number' name='MATRIX' id='MATRIX' step='1' max='250' min='1' required  value='");page +=matrix_brightness; page +=F("'/>");
                           page +=F("</td></tr><tr><td> Luminosité rubans LED (1->250):</td><td></td><td>");
                           page +=F("<label></label><input type='number' name='LED' id='LED' step='1' max='250' min='1' required  value='");page +=led_brightness; page +=F("'/>");
                           page +=F("</td></tr><tr><td>Volume Audio (0->30) :</td><td></td><td>");
                           page +=F("<label></label><input type='number' name='VOLUME' id='VOLUME' step='1' max='30' min='0' required  value='");page +=set_volume; page +=F("'/>");
                           page +=F("</td></tr><tr><td></td><td><input type='submit'  value='Envoi'></td><td>");
                           page +=F("</td></tr></table></form></section>"); 
                                                                 
                                                    

                           page +=F("<section id='sent'><h2> Redemarrage  </h2><table><tr><td> ");
                           page +="";
                           page +=F(" </td><td></td><td><form method='post' accept=''><input type='hidden' name='RAZ' value='1'/><input type='submit' value='RAZ'/>");                      
                           page +=F("</form></td></tr></table></section>");
                                 
                           page +=F("</div>");
                           
                           page +=F("<footer><table><tr><td><a href='http://innogreentech.fr'>InnoGreenTech  </a></td><td></td><td><a href='mailto: info@innogreentech.fr'> Contactez moi</a></td></tr></table></footer>");
                           page +=F("</body></html>");                 
                           return page;
                          }
