# include <Servo.h> 
# include <LiquidCrystal.h>


# define ir_c  A0
# define ir_o  A1
# define ir_s  A2

# define ir_eo A3
# define ir_ec A4

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2 ;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo gate ;
Servo exitG ;

int count = 0 ;
int maxCount = 0 ;
int e = 0 ;

void setup() {

  lcd.begin(16, 4) ;  
  lcd.print("Hello, World!") ;

  lcd.setCursor(0,1) ;
  lcd.print("LOADING      ") ;
  
  gate.attach(6) ;
  exitG.attach(10) ;
  
  pinMode(7, OUTPUT) ;
  
  pinMode(ir_s, INPUT) ;
  pinMode(ir_o, INPUT) ;
  pinMode(ir_c, INPUT) ;
  
  pinMode(ir_eo, INPUT) ;
  pinMode(ir_ec, INPUT) ;
  
  lcd.setCursor(0,1) ;
  lcd.print("LOADING.     ") ;
  
  for( int clsG = 90 ; clsG > 0 ; clsG -- ) { 
                                  
    gate.write(clsG) ;               
    delay(20) ;
    
  }
  
  lcd.setCursor(0,1) ;
  lcd.print("LOADING..    ") ;
  
  for( int clsG = 90 ; clsG < 180 ; clsG ++ ) {
                                   
    exitG.write(clsG) ;               
    delay(20) ;

  }
  
  lcd.setCursor(0,1) ;
  lcd.print("LOADING...   ") ;
  delay(500);
  lcd.clear() ;
  
}

void loop() {

  int d = 0 ;
  delay(10) ;

  while( analogRead(ir_c) > 300 ){
    
    Serial.println(analogRead(ir_o)) ;
    delay(10) ;
    
    while( count == 3 ){
      
       lcd.setCursor(0, 0) ;
       lcd.print("Limit Exeeded ") ;
       
       lcd.setCursor(0, 1) ;
       lcd.print("Keep 5m Distance") ;
       
       lcd.setCursor(0, 3) ;
       lcd.print("Gate Locked Wait") ;
       
       exitGate() ;
    }
  
  exitGate() ;
    
    if( d == 0 ){
      
      lcd.setCursor(0, 1) ;
      lcd.print("Apply Sanitizer ") ;
      
      lcd.setCursor(0, 0) ;
      lcd.print("PLEASE COME IN  ") ;
       
      lcd.setCursor(0, 3);
      lcd.print("Gate closed     ") ;
    
   }
    
    if( analogRead(ir_s) < 300 ){
      
      lcd.setCursor(0, 1) ;
      lcd.print("Test Temperature") ;
      
      digitalWrite(7, HIGH) ;
      delay(2000) ;
      
      digitalWrite(7, LOW) ;
      
      d ++ ;
    
      lcd.setCursor(0, 1) ;
      lcd.print("Heat & Mask Done") ;
      
      lcd.setCursor(0, 0) ;
      lcd.print("Sanitizer Done  ") ;
      
    }
    
    if( analogRead(ir_o) < 300 ){
    
      lcd.setCursor(0, 3) ;
      lcd.print("Gate Opened" ) ;
      
      for( int openG = 0 ; openG < 180 ; openG += 10 ) {  
    
        gate.write(openG) ;               
        delay(10) ;
        
      }  
       
    }
    
  } 
  
  if( analogRead(ir_c) < 300 && d > 0 ){
      
    for( int closeG = 180 ; closeG > 0 ; closeG -= 10 ) {  

      gate.write(closeG) ;               
      delay(10);
      
  }
      
    lcd.setCursor(0, 3) ;
    lcd.print("Gate Closed") ;
      
    count ++ ;

    lcd.setCursor(0, 2) ;
    lcd.print("Entered Count:") ;
      
    lcd.setCursor(14, 2) ;
    lcd.println(count) ;
      
    d -= 1;
    
  }
  
}

void boot(int boot){
  
  lcd.begin(16, 4) ;  
  lcd.print("hello, world!") ;
  
  
  lcd.setCursor(0,1) ;
  lcd.print("loading.      ") ;
  delay(boot) ;
  
  lcd.setCursor(0,1) ;
  lcd.print("loading..     ") ;
  delay(boot) ;
  
  lcd.setCursor(0,1) ;
  lcd.print("loading...    ") ;
  
}

void exitGate(){

  if( analogRead(ir_eo) < 300 ){
    
    for( int openG = 180 ; openG > 0 ; openG -= 10 ) { 
       
      exitG.write(openG) ;               
      delay(10) ;
      
      }
      
    e ++ ;
    
  }
  
  if( analogRead(ir_ec) < 300 && e == 1 ){
    
    for( int closeG = 0 ; closeG < 180 ; closeG += 10 ) {  
      
      exitG.write(closeG) ;               
      delay(10) ;
    
      
    }
    
    count -- ;
    e -- ;
      
    lcd.setCursor(0, 2);
    lcd.print("Entered Count: ");
      
    lcd.setCursor(14, 2);
    lcd.println(count);
      
  }
  
}
