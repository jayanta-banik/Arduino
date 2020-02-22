// defining pins to use
byte m_right_F = 7, m_right_R = 6;
byte m_left_F = 8, m_left_R = 9;
//if your motor has higher RPM then decrease the optimal_duration. experiment with values.
int optimal_duration = 5500;

String cmd_phrase[] = {"change duration", "move"};
String data;
void the_car(int dataLoad);
void process_data(String);
void move_the_car(char ch, int duration);
void show(String s, boolean n = true);
void getData(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m_left_F, OUTPUT);
  pinMode(m_left_R, OUTPUT);
  pinMode(m_right_F, OUTPUT);
  pinMode(m_right_R, OUTPUT);
  show("ready");
//  the_car(3);
}

void loop() {
  //needs to input -- direction (w,a,s,d,r) & duration || staring with ':' || seperated by ',' || ending with '.'
  getData();
  process_data(data);
  delay(100);
  show("Ready");

}

void show(String s, boolean n = true) {
  // add code to print status on servers or LAN
  Serial.print(s);
  if (n) {
    Serial.println();
  }
}

void getData() {
  while (!Serial.available());
  data = Serial.readStringUntil('\n');
  show("got the data -", false);
  show(data);
}

void process_data(String s) {
  if (s.substring(0, cmd_phrase[0].length()).equals(cmd_phrase[0])) {
    optimal_duration = s.substring(s.indexOf(':') + 1, s.indexOf('.')).toInt();
  }
  else if (s.substring(0, cmd_phrase[1].length()).equals(cmd_phrase[1])) {
    int del_time = (s.substring(s.indexOf(',') + 1, s.indexOf('.'))).toInt();
    move_the_car(s.charAt(s.indexOf(':') + 1), (s.indexOf(',') > 0) ? s.substring(s.indexOf(',') + 1, s.indexOf('.')).toInt() : 0);
  }
}
void move_the_car(char ch, int duration) {//duration can be -ve(infite) or 0(default) or +ve number(set time)
  Serial.println(ch);
  switch (ch) {
    case 'w':
      show("moving: forward");
      the_car(3);
      break;
    case 'a':
      show("moving: left 90");
      the_car(2);
      break;
    case 's':
      show("moving: backward");
      the_car(0);
      break;
    case 'd':
      show("moving: right 90");
      the_car(1);
      break;
    case 'r':
      show("moving: reverse");
      the_car(-3);
      break;
    default:
      show("error");
  }
  if (duration > 0) {
    delay(duration);
    the_car(0);
  }
  else if (duration == 0) {
    delay(optimal_duration);
    the_car(0);
  }
  delay(20);
}

void the_car(byte dataLoad) {
  if (dataLoad < 0) {
    dataLoad *= -1;
    digitalWrite(m_left_F, LOW);
    digitalWrite(m_left_R, dataLoad % 2);
    digitalWrite(m_right_F, LOW);
    digitalWrite(m_right_R, dataLoad / 2 % 2);
  }
  else {
    digitalWrite(m_left_F, dataLoad % 2);
    digitalWrite(m_left_R, LOW);
    digitalWrite(m_right_F, dataLoad / 2 % 2);
    digitalWrite(m_right_R, LOW);
  }
}

