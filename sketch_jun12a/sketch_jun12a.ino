#define shift_data 3
#define shift_clk 2
#define st_reg_clk 4  
#define shift_data_2 6
#define shift_clk_2  5
#define st_reg_clk_2 7  
#define button 12





byte leds ;
byte leds2 ;
int speed = 100;


void game_mode(int speed);
void update_Storage_register();
void chasing_led();
void winner_mode();
void lose_mode();


void setup() {
  pinMode(shift_data, OUTPUT);
  pinMode(shift_clk, OUTPUT);
  pinMode(st_reg_clk, OUTPUT);
  pinMode(shift_data_2, OUTPUT);
  pinMode(shift_clk_2, OUTPUT);
  pinMode(st_reg_clk_2, OUTPUT);
  pinMode(button, INPUT);
  
}

void loop() {
  game_mode(speed);

 }

void update_Storage_register(){
  shiftOut(shift_data, shift_clk, LSBFIRST, leds);
  digitalWrite(st_reg_clk, LOW);
  digitalWrite(st_reg_clk, HIGH);
  digitalWrite(st_reg_clk, LOW);
  shiftOut(shift_data_2, shift_clk_2, LSBFIRST, leds2);
  digitalWrite(st_reg_clk_2, LOW);
  digitalWrite(st_reg_clk_2, HIGH);
  digitalWrite(st_reg_clk_2, LOW);
}


void game_mode(int speed){
  leds = 0;
  leds2 = 0;
  update_Storage_register();
  for (int i = 0; i < 8; i++)  // Turn all the LEDs ON one by one.
  {
      bitSet(leds, i); // Set the bit that controls that LED in the variable 'leds'
      update_Storage_register();
      if(i != 0){
      leds &= ~(1<<(i-1));
      }
      if (digitalRead(button) == 0 && leds == 0b00000001)
      {
        winner_mode();
        speed -= 20;
      }else if(digitalRead(button) == 0 && leds != 0b00000001){
        lose_mode();
        speed = 100;
      }
      update_Storage_register();
      delay(speed);
  }
  leds = 0;
  update_Storage_register();
  for (int i = 0; i < 8; i++)  // Turn all the LEDs ON one by one.
  {
      bitSet(leds2, i); // Set the bit that controls that LED in the variable 'leds'
      update_Storage_register();
      if(i != 0){
      leds2 &= ~(1<<(i-1));
      }
      if(digitalRead(button) == 0 && leds2 != 0b00000001){
        lose_mode();
        speed = 100;
      }
      update_Storage_register();
      delay(speed);
  }  
}

void winner_mode(){  
  leds = 0;
  leds2 = 0;
  update_Storage_register();
  for (int i = 0; i < 8; i++)  // Turn all the LEDs ON one by one.
  {
      bitSet(leds, i); // Set the bit that controls that LED in the variable 'leds'
      update_Storage_register();
      delay(50);
  }
  leds = 0;
  update_Storage_register();
  for (int i = 0; i < 8; i++)  // Turn all the LEDs ON one by one.
  {
      bitSet(leds2, i); // Set the bit that controls that LED in the variable 'leds'
      update_Storage_register();
      delay(50);
  }  
}

void lose_mode(){
    leds = 0xFF;
    leds2 = 0xFF;
    update_Storage_register();
    delay(200);
    leds = 0x00;
    leds2 = 0x00;
    update_Storage_register();
     delay(250);
}
