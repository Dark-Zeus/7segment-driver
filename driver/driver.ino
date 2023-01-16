#define DATA 10
#define SHIFT_CLK 11
#define LATCH_CLK 12
 
int arr[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6, 0xee, 0x3e, 0x9c, 0x7a, 0x9e, 0x8e};

int x = 0;
int y = 0;

void latch();
void draw();

void setup() {
  for(int i = 6; i < 13; i++){
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(9600);
  
  for(int i = 6; i < 10; i++){
    digitalWrite(i ,HIGH);
  }
}

void latch(){
  digitalWrite(LATCH_CLK, LOW);
  digitalWrite(LATCH_CLK, HIGH);
  digitalWrite(LATCH_CLK, LOW);
}

void draw(int num, int start_pin, int base){
  int digits = log(num)/log(base) + 1;
  x = 0;
  for(int i = 0; i < digits; i++){
    x = (num % round(pow(base,(i+1))));
    num -= x;
    shiftOut(DATA, SHIFT_CLK, LSBFIRST, arr[x / round(pow(base,i))]);
    latch();
    digitalWrite((start_pin + i), LOW);
    delay(5);
    digitalWrite((start_pin + i), HIGH); 
  }
}

void loop() {
  draw(0xfff, 6, 10);
}
