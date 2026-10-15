#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

const int rs = 9, en = 8, d4 = 13, d5 = 12, d6 = 11, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','a'},
  {'4','5','6','b'},
  {'7','8','9','c'},
  {'*','0','#','d'}
};
byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {7, 6, 5, 4}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define BUZZER A3
#define RELAY 4
char pass[6] = {'1','2','3','4','5','\0'}; 
char adminPass[6] = {'9','9','9','9','9','\0'};  
unsigned char password = 0;
int t = 0;
int x = 0;
int q = 0;
char p[6];
int wrong = 0;
bool keypadLocked = false;
unsigned long lockTime = 0;


void beep(int duration = 100) {
  digitalWrite(BUZZER, HIGH);
  delay(duration);
  digitalWrite(BUZZER, LOW);
}
void loadPassword() {
  if (EEPROM.read(0) == 255) { 
    lcd.clear();
    lcd.print("First Time Setup");
    lcd.setCursor(0,1);
    lcd.print("Set New Password:");
    delay(2000);
    getNewPasswordFromUser();
    savePassword();
    beep(500);
  } else {
    for(int i = 0; i < 5; i++) {
      pass[i] = EEPROM.read(i+1);
    }
  }
}
void savePassword() {
  for(int i = 0; i < 5; i++) {
    EEPROM.write(i+1, pass[i]);
  }
  EEPROM.write(0, 1); 
}
void getNewPasswordFromUser() {
  int idx = 0;
  lcd.clear();
  lcd.print("Enter 5-digit pass:");
  while(idx < 5) {
    char key = keypad.getKey();
    if(key && key >= '0' && key <= '9') {
      pass[idx++] = key;
      lcd.setCursor(7 + idx - 1, 1);
      lcd.print('*');
      beep(80);
    }
  }
  pass[5] = '\0';
}

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT); 
  pinMode(A2, OUTPUT); 
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  digitalWrite(A0, 0);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(RELAY, 0);
  digitalWrite(BUZZER, 0);

  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Welcome");
  lcd.setCursor(1,1);
  lcd.print("to the Digital lock");
  beep(200);
  delay(2000);

  loadPassword();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter password:");
  lcd.setCursor(0,2);
  lcd.print("Attempts left: 3");
}

void loop() {
  if (keypadLocked && millis() - lockTime >= 60000) {
    keypadLocked = false;
    wrong = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter password:");
    lcd.setCursor(0,2);
    lcd.print("Attempts left: 3");
    beep(300);
  }

  if(keypadLocked) {
    delay(100);
    return;
  }

  char key = keypad.getKey();
  
  if (key != NO_KEY) {
    beep(80);

    if (key == 'c' || key == 'C') {
      t = x = q = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter password:");
      lcd.setCursor(0,2);
      lcd.print("Attempts left: "); lcd.print(3-wrong);
      return;
    }
    if (key != NO_KEY){
      lcd.setCursor(0,0);
      lcd.print("Enter password:     ");
      lcd.setCursor(x+7, 1);
      lcd.print('*');
      t++;
      x++;
      p[q] = key;
      q++;
      change();
      if (t>=5){
        lcd.clear();
        check();
        timer();
      }
    }
  }
}
void check() {
  p[5] = '\0';
  bool correct = true;
  for(int i=0; i<5; i++) if(p[i] != pass[i]) correct = false;
  
  bool adminCorrect = true;
  for(int i=0; i<5; i++) if(p[i] != adminPass[i]) adminCorrect = false;

  if (correct || adminCorrect) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Correct Password!");
    lcd.setCursor(1, 1);
    lcd.print("Door Opening...");
    digitalWrite(A0, 1);
    digitalWrite(RELAY, 1);
    for(int i=0; i<10; i++) { beep(100); delay(100); }
    delay(3000);
    digitalWrite(RELAY, 0);
    digitalWrite(A0, 0);
    lcd.clear();
    t=0; x=0; q=0; wrong=0;
    lcd.setCursor(0,0);
    lcd.print("Enter password:");
    lcd.setCursor(0,2);
    lcd.print("Attempts left: 3");
  }
  else {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("ERROR");
    lcd.setCursor(1, 1);
    lcd.print("Wrong password!");
    digitalWrite(A2, 1);
    beep(800);
    delay(1500);
    digitalWrite(A2, 0);
    lcd.clear();
    t=0; x=0; q=0; wrong++;
    lcd.setCursor(0,0);
    lcd.print("Enter password:");
    lcd.setCursor(0,2);
    lcd.print("Attempts left: "); lcd.print(3-wrong);
  }
}
void timer() {
  if (wrong == 2) {
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("WARNING!");
    digitalWrite(A2, 1);
    beep(1000);
    lcd.setCursor(0, 1);
    lcd.print("  2 wrong attempts!");
    delay(3000);
    digitalWrite(A2, 0);
    lcd.clear();
    lcd.print("Enter password:");
    lcd.setCursor(0,2);
    lcd.print("Attempts left: 1");
  }
  if (wrong >= 3) {
    keypadLocked = true;
    lockTime = millis();
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("TOO MANY ERRORS!");
    lcd.setCursor(2, 1);
    lcd.print("Keypad Locked");
    digitalWrite(A2, 1);
    beep(1500);
    
    for (int timer=59; timer>=0; timer--) {
      digitalWrite(A1, 1);
      lcd.setCursor(6, 2);
      lcd.print("Time: 0:");
      if(timer < 10) lcd.print("0");
      lcd.print(timer);
      lcd.setCursor(7, 3);
      lcd.print("Wait please...");
      delay(1000);
      if(timer > 0) lcd.clear(), lcd.setCursor(2,0), lcd.print("TOO MANY ERRORS!"), lcd.setCursor(2,1), lcd.print("Keypad Locked");
    }
    digitalWrite(A1, 0);
    digitalWrite(A2, 0);
    wrong = 0;
    keypadLocked = false;
    lcd.clear();
    lcd.print("Enter password:");
    lcd.setCursor(0,2);
    lcd.print("Attempts left: 3");
    beep(400);
  }
}
void check_oldpassword() {
  savePassword();
}

void change() {
  if (q >= 2 && p[0]=='#' && p[1]=='#') {
    savePassword();
  }
}