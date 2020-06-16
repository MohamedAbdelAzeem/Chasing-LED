#define shift_data 3
#define shift_clk 2
#define st_reg_clk 4  
#define shift_data_2 6
#define shift_clk_2  5
#define st_reg_clk_2 7  

byte leds ;
byte leds2 ;
void update_Storage_register();
void game_mode();
void winner_mode();
void 


void setup() {
  pinMode(shift_data, OUTPUT);
  pinMode(shift_clk, OUTPUT);
  pinMode(st_reg_clk, OUTPUT);
  pinMode(shift_data_2, OUTPUT);
  pinMode(shift_clk_2, OUTPUT);
  pinMode(st_reg_clk_2, OUTPUT);
}

void loop() {
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
      update_Storage_register();
      delay(10);
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
      update_Storage_register();
      delay(10);
  }  
}

void update_Storage_register(){
  shiftOut(shift_data, shift_clk, MSBFIRST, leds);
  digitalWrite(st_reg_clk, LOW);
  digitalWrite(st_reg_clk, HIGH);
  digitalWrite(st_reg_clk, LOW);
  shiftOut(shift_data_2, shift_clk_2, MSBFIRST, leds2);
  digitalWrite(st_reg_clk_2, LOW);
  digitalWrite(st_reg_clk_2, HIGH);
  digitalWrite(st_reg_clk_2, LOW);
}
