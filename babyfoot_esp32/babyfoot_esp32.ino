/************************************************************************************
    
    <babyfoot table football>
    Copyright (C) <2019>  <Fabrice BAUDIN>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    info@innoreentech.fr

****************************************************************************************/




#define gmask_32 0x000000FF
#define bmask_32 0x0000FF00
#define rmask_32 0x00FF0000

volatile const int32_t BLACK_32 = 0;
volatile const int32_t RED_32 = rmask_32;
volatile const int32_t GREEN_32 = gmask_32;
volatile const int32_t BLUE_32 = bmask_32;
volatile const int32_t WHITE_32 = rmask_32 | gmask_32 | bmask_32;
volatile const int32_t CYAN_32 = gmask_32 | bmask_32;
volatile const int32_t YELLOW_32 = rmask_32 | gmask_32;
volatile const int32_t MAGENTA_32 = rmask_32 | bmask_32;

#define rmask 0b0000000000001111
#define gmask 0b0000000011110000
#define bmask 0b0000111100000000

volatile const int16_t BLACK = 0;
volatile const int16_t RED = rmask;
volatile const int16_t GREEN = gmask;
volatile const int16_t BLUE = bmask;
volatile const int16_t WHITE = rmask | gmask | bmask;
volatile const int16_t CYAN = gmask | bmask;
volatile const int16_t YELLOW = rmask | gmask;
volatile const int16_t MAGENTA = rmask | bmask;


/*
* EEPROM setting
*/

#include <EEPROM.h> // Gestion de la mémoire de type eeprom pour la sauvegarde des choix


#define MEM_SSID            0
#define MEM_PASSWORD        100 
#define LED_BRIGHTNESS      200
#define MATRIX_BRIGHTNESS   201
#define SET_VOLUME          202

/*
 *  wifi utilities
 */

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

String      local_mac;                // adress mac of the module
String      local_ip;                 // adress ip of module
String      ssid="";
String      password="";
const char* host="babyfoot";
String      ref_module="";          // référence du module
String      version_module="";      // version of module

WebServer server(80);


/* Set update server */

const char* update_path = "/firmware";
const char* update_username = "admin";
const char* update_password = "admin";

/*
 *  Time library
 */

 #include    <TimeLib.h>
 #include <NtpClientLib.h>

/*
 *  Setting of MP3 player
 */
#include <HardwareSerial.h>
#include "DFRobotDFPlayerMini.h" 



HardwareSerial MySerial(1);     //Define serial1



  //  Serial1 define pin
#define   RX_PIN  13
#define   TX_PIN  12


DFRobotDFPlayerMini DFPlayer;

volatile int set_volume=20;
volatile int play_run=0;

 
/*
 * Define control matrix LED
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Adafruit_GFX.h"
#include "ESP32RGBmatrixPanel.h"


//G1	R1 |
//GND	B1 |
//G2	R2 |
//GND	B2  |
//B		A   |
//D		C  |
//LAT	CLK|
//GND	OE |

//ESP32RGBmatrixPanel matrix(23, 22, 03, 17, 16, 04, 00, 02, 15, 21, 19, 18, 5); //Flexible connection
ESP32RGBmatrixPanel matrix(23, 22, 3, 15, 2, 0,4, 16, 17,5, 18, 19, 21); //Flexible connection

//Default connection
//uint8 OE = 23;
//uint8 CLK = 22;
//uint8 LAT = 03;
//uint8 CH_A = 21;
//uint8 CH_B = 19;
//uint8 CH_C = 18;
//uint8 CH_D = 5;
//uint8 R1 = 17;
//uint8 G1 = 16;
//uint8 BL1 = 4;
//uint8 R2 = 0;
//uint8 G2 = 2;
//uint8 BL2 = 15;


//ESP32RGBmatrixPanel matrix;

int matrix_brightness=25;



 /*
  * Setting NeoPixel
  */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define LED_PIN_1   26
#define LED_PIN_2   14

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 40                // 40x3 LEd

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN_1, NEO_RBG + NEO_KHZ800); // It is possible to use 400 Khz /
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN_2, NEO_RBG + NEO_KHZ800);

int led_brightness=100;

/* GPIO SETTING */

#define RESET_PIN     25                 // Pin to RESET_PIN bascul RS
#define GOAL_RIGHT    36                 // Goal 
#define GAMELLE_RIGHT 39                 // Gamelle
#define GOAL_LEFT     34                 // Goal 
#define GAMELLE_LEFT  35                 // Gamelle 

#define LESS_BUTTOM  32
#define MORE_BUTTOM  33
#define OK_BUTTOM    27

#define DELAY_BUTTOM 5              // Use like a filter, the time depend of speed of one cycle of the program
#define SENS_SET     40               // Set to active buttom 0 to 60 max

volatile int less_buttom_start=0;
volatile int more_buttom_start=0;
volatile int ok_buttom_start=0;

volatile unsigned int inputs=0;            // use bit to read input               

#define OK          0
#define LESS        1
#define MORE        2
#define GOAL_P1     3
#define GAMELLE_P1  4
#define GOAL_P2     5
#define GAMELLE_P2  6

#define EDGE_OK          8
#define EDGE_LESS        9
#define EDGE_MORE        10
#define EDGE_GOAL_P1     11
#define EDGE_GAMELLE_P1  12
#define EDGE_GOAL_P2     13
#define EDGE_GAMELLE_P2  14




/*
 * Memory to control gif animation
 */

volatile unsigned long last_frame; 
//volatile unsigned long speed_frame=100;      //time between two frame 
volatile int frame = 1;                // Current frame

volatile unsigned int statut_animation=0; 
#define STOP      0
#define START     1
#define READ      2
#define LOOP      3
#define FINISH    4

volatile int neo_animation=0;  
#define CLEAR     0
#define EDGE      1
#define AVERAGE   2

/*
 * Game information
 */

volatile int score_p1=         0;
volatile int score_p2=         0;
volatile int ball=             11;          // rest of balls to play
volatile int waiting_goal=      0;           // for demi 
volatile int save_waiting_goal= 0;
volatile int last_points=       0;
volatile unsigned long start_time=     0;   // La durée de la partie

volatile uint32_t round_color;

volatile unsigned long statut_game;   // Use like bit status 
 
 #define RUN              0
 #define GOAL1            1
 #define GOAL2            2
 #define GAMELLE1         3
 #define GAMELLE2         4
 #define START_GAME       5
 #define SWITCH_TEAM      6
 #define GAME_OVER        7
 
 #define SCORE_CHANGE     8
 #define PLAYER_1         9
 #define PLAYER_2         10
 #define PLAYER_SELECTED  11

 #define PLAYER_1_WIN     12
 #define PLAYER_2_WIN     13
 #define CHOSE_SIDE       14
 #define DEMI             15
 
volatile unsigned long start_gamelle_validation=0; 

#define GAMELLE_VALIDATION 6000              //waiting time in ms befor validation of gamelle





 /*
 *create a hardware timer to refresh screen
 */
 
 hw_timer_t* displayUpdateTimer = NULL;

 void IRAM_ATTR onDisplayUpdate() {
   matrix.update();
 }



 
void setup() {

   /*Debug port*/
   
  Serial.begin(115200);

  
  /*Gpio Define*/
  pinMode(GOAL_RIGHT, INPUT); // Gaol player 1 input
  pinMode(GAMELLE_RIGHT, INPUT); // Gamelle player 1 input
  pinMode(GOAL_LEFT, INPUT); // Gaol player 1 input
  pinMode(GAMELLE_LEFT, INPUT); // Gamelle player 1 input
  pinMode(RESET_PIN, OUTPUT);         //RESET_PIN 
  digitalWrite(RESET_PIN,0); // RESET_PIN hazard signal
  delay(20);
  digitalWrite(RESET_PIN,1);

  /* Read EEPROM */
  
  EEPROM.begin(256);

  char carac='1';   // Name of module
  int a=0;
  String read_mem="";
  

  carac='1';                
  a=0;
  while (!(carac=='\0')&&a<100){carac=char (EEPROM.read(MEM_SSID+a));
  if (!(carac=='\0')){ssid +=carac;} a++;}  //récupération du lien d'information
  if (ssid=='\0'||a>50){ssid=F("");}
  //Serial.println(ssid);
            
  carac='1';
  a=0;
  while (!(carac=='\0')&&a<100){carac=char (EEPROM.read(MEM_PASSWORD+a));
  if (!(carac=='\0')){password +=carac;} a++;}  //récupération du lien d'information
  if (password=='\0'||a>50){password=F("");}
  //Serial.println(password);


  led_brightness = EEPROM.read(LED_BRIGHTNESS );

  matrix_brightness = EEPROM.read(MATRIX_BRIGHTNESS);

  set_volume = EEPROM.read(SET_VOLUME);

    /* mp3 player*/
  
   MySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);


     
   if (!DFPlayer.begin( MySerial,false)) {  
   Serial.println(F("Unable to begin:"));
   Serial.println(F("1.Please recheck the connection!"));
   Serial.println(F("2.Please insert the SD card!"));
   while(true);
   }
  Serial.println(F("DFPlayer Mini online."));

  delay(200);
  int number_of_tracks=DFPlayer.readFileCounts();
  Serial.println(number_of_tracks);

 // DFPlayer.outputSetting(0, 0);
  //delay(200);
  DFPlayer.volume(30); 
  
  delay(200);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  delay(200);
  DFPlayer.EQ(DFPLAYER_EQ_BASS);
  delay(200);

    strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
//  strip1.show();            // Turn OFF all pixels ASAP
  strip1.setBrightness(led_brightness); // Set BRIGHTNESS to about 1/5 (max = 255)

  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
//  strip2.show();              // Turn OFF all pixels ASAP
  strip2.setBrightness(led_brightness);  // Set BRIGHTNESS to about 1/5 (max = 255)*/ 

  DFPlayer.volume(set_volume);   
  delay(200);

 /* creat a task for the matrix, like this it is possible to use  */
    
  xTaskCreate(&loop2_task, "loop2_task", 4096, NULL, 5, NULL);  //2048
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  displayUpdateTimer = timerBegin(0, 110, true);
  timerAttachInterrupt(displayUpdateTimer, &onDisplayUpdate, true);
  timerAlarmWrite(displayUpdateTimer, 2, true);
  timerAlarmEnable(displayUpdateTimer);
  
  /*matrix setting */
  
  //matrix.setRotation(2);
  matrix.setTextWrap(false);
  matrix.invertDisplay(0);
  matrix.setBrightness(matrix_brightness);
  matrix.fillScreen(0);



  //DFPlayer.playFolder(01,0001);
 // DFPlayer.playLargeFolder(01,0001);

 //DFPlayer.play(0001);

   /* Connexion wifi */
  int c;
  WiFi.mode(WIFI_STA);
           
  c =ssid.length()+1;
  char char_ssid[50];
  ssid.toCharArray(char_ssid, c);

  c =password.length()+1;
  char char_password[50];
  password.toCharArray(char_password, c);
   
        
  WiFi.begin(char_ssid,char_password);
           
  unsigned long time_out_connection = millis();
  
  while (WiFi.status() != WL_CONNECTED)
  {
    if (millis() - time_out_connection > 20000)
    {
      Serial.println F("");
      Serial.println F ("connection Wifi fail !");            
      break;
    }
    delay(100);
    Serial.print('-');
  }
           
  if ( WiFi.status()!= WL_CONNECTED)        
  {
    Serial.println F ("Open setting gate !");
    WiFi.disconnect();
    WiFi.mode(WIFI_AP); 
    delay(200);
    WiFi.softAP("InnoGreenTech", "innogreentech");
    server.on ( "/index.html", handleRoot );    // go to set up wifi page
    delay(100);
    server.on ("/style.css", cssRoot);     // envoi au fichier de configuration de style
    local_mac = WiFi.macAddress();
    local_ip="Wifi no connected";
    delay(100);
    server.begin();
  }
  else
  {     
    /*Read the hour and date on internet */
            
    NTP.begin("pool.ntp.org", 1, true);  //configuration de la récupération de la date,  Serveur+1 heure, Heure été/hivers
    NTP.setInterval(3600);                // Toutes les heures


    
                      
    /*information of module*/

    local_ip=WiFi.localIP().toString().c_str();              
    local_mac=WiFi.macAddress();//.toString().c_str();
    //gate_way=WiFi.gatewayIP().toString().c_str();
    ref_module="babyfoot";
    version_module="V1";

    /* Host name start */

    if (!MDNS.begin(host)) { //http://"host".local
      Serial.println("Error setting up MDNS responder!");
      while (1) {
        delay(1000);
      }
    }
                             
    /* setting of web server */
              
    server.on ( "/index.html", indexRoot );    // Renvoi à la page de index
    delay(100);
    server.on ( "/", indexRoot );    // Renvoi à la page de index
    delay(100);
      server.on ("/style.css", cssRoot);     // envoi au fichier de configuration de style
    delay(100);
               
    /*return index page which is stored in serverIndex */
    server.on("/firmware", HTTP_GET, update_login);
    server.on("/serverIndex", HTTP_GET, update_index);

    /*handling uploading firmware file */

    server.on("/update", HTTP_POST, update_error, update_file);
    server.begin();
}

  Serial.print(F("référence:"));Serial.println(ref_module);
  Serial.print(F("Version:"));Serial.println(version_module);
  Serial.print(F("Adresse IP:"));Serial.println(local_ip);
  Serial.print(F("Adresse MAC:"));Serial.println(local_mac); 
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.dnsIP(1)); 

 


}

/* loop 1 use to wifi management */


void loop() {


     //Serial.println(statut_game,BIN);
     delay(1);
  

}

/*
 * Loop to can use the second corp of esp 32 
 */
 
void loop2_task(void *pvParameter){


   unsigned long Test_animation;
   int animation_run=0;
   for(;;)
   {  
         server.handleClient();  
        

        read_inputs();
        play_game();
        play_show();
        delay(1);

    }

 
 }
 
