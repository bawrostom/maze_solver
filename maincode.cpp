#define echof A5
#define trigf A4
#define echol A0
#define trigl A1
#define echor A2
#define trigr A3

int pin4=3;
int pin3=9;
int pinE=13;
int pin1=11;
int pin2=10;
int IRSensor = 2;

int k=10;
int cs=0;
int ps=0;
int encoderr=13;
int encoderl=7;
int counterr=0;
int counterl=0;
char path[]={'\0'};
int x=5;
bool IR= false;
int i=0;
char L;
int a;
long int* p;
int disf,disr,disl;
long durationl,durationr,durationf;





void setup() {
pinMode(pin1, OUTPUT);
pinMode(pin2, OUTPUT);
pinMode(pin3, OUTPUT);
pinMode(pin4, OUTPUT);
pinMode(pinE, OUTPUT);

pinMode(trigf, OUTPUT); 
pinMode(echof, INPUT);
pinMode(trigl, OUTPUT); 
pinMode(echol, INPUT);
pinMode(trigr, OUTPUT); 
pinMode(echor, INPUT);
pinMode (IRSensor, INPUT);
pinMode(encoderr, INPUT);
pinMode(encoderl, INPUT);
digitalWrite(pinE, HIGH);
Serial.begin(9600);

}
long int* distance() {
digitalWrite(trigl, LOW);
delayMicroseconds(2);
digitalWrite(trigl, HIGH);
delayMicroseconds(5);
digitalWrite(trigl, LOW);
durationl = pulseIn(echol, HIGH);
disl = durationl * 0.034 / 2; 
digitalWrite(trigf, LOW);
delayMicroseconds(2);
digitalWrite(trigf, HIGH);
delayMicroseconds(5);
digitalWrite(trigf, LOW);
durationf = pulseIn(echof, HIGH);
disf = durationf * 0.034 / 2;
delay(1);
digitalWrite(trigr, LOW);
delayMicroseconds(2);
digitalWrite(trigr, HIGH);
delayMicroseconds(5);
digitalWrite(trigr, LOW);
durationr = pulseIn(echor, HIGH);
disr = durationr * 0.034 / 2; 
static long int dis[3]={0};
dis[0]=disf;
dis[1]=disr;
dis[2]=disl;
return dis;
}
int step_calc_r(){
  cs=digitalRead(encoderr);
  if (cs !=ps){
    counterr++;
    }
  ps=cs;
  return counterr;
}
int step_calc_l(){
  cs=digitalRead(encoderl);
  if (cs !=ps){
    counterl++;
    }
  ps=cs;
  return counterl;
}
int forward(){
  long int* p=distance();
  a=min((k * (*p-10)),80);
  analogWrite(pin1, a);
  analogWrite(pin2, 0);
  analogWrite(pin3, a);
  analogWrite(pin4, 0);
  Serial.println(a);
  return a;
}
void right(){
step_calc_l();
if (counterl< 100) {
    step_calc_l();

    analogWrite(pin3,100);
    analogWrite(pin4,0);    
    analogWrite(pin1, 35);
    analogWrite(pin2,0);}
else{
   analogWrite(pin1, 0);
    analogWrite(pin2,0);
    analogWrite(pin3,0);
    analogWrite(pin4,0);

}
}
void stopo(int x){
  analogWrite(pin1, 0);
    analogWrite(pin2,0);
    analogWrite(pin3,0);
    analogWrite(pin4,0);step_calc_r();
if (counterr < 315) {
    step_calc_r();
    analogWrite(pin1, 140);
    analogWrite(pin2,0);
    analogWrite(pin3,35);
    analogWrite(pin4,0);}
    else{
   analogWrite(pin1, 0);
    analogWrite(pin2,0);
    analogWrite(pin3,0);
    analogWrite(pin4,0);
    delay(x);
  }
void dicision(char d){
  path[i]=d;
  i++;
  }
  
void infrared(){
 int statusSensor = digitalRead (IRSensor);
  
  if (statusSensor == 1){
    IR=true; 
  } 
}
void rotate(){
  
  
  }
void left(){
step_calc_r();
if (counterr < 315) {
    step_calc_r();
    analogWrite(pin1, 140);
    analogWrite(pin2,0);
    analogWrite(pin3,35);
    analogWrite(pin4,0);}
    else{
   analogWrite(pin1, 0);
    analogWrite(pin2,0);
    analogWrite(pin3,0);
    analogWrite(pin4,0);
  }

}



void loop(){
long int* p=distance();
counterr=0;
counterl=0;
while (*(p+2)>10){
left();
distance();
Serial.print("dis l");
Serial.println(*(p+2));
}
counterr=0;
counterl=0;
while (*(p+2)<10 && *(p)>10){
  forward();
  distance();
  
//Serial.print("disf  ");
  //Serial.print(*(p));
  //Serial.print("speed  ");
  //Serial.println(a);
  }
while (*(p+2)<10 && *(p)<15 && *(p+1)>10){
  
  right();
  distance();
  Serial.print("disr");
  Serial.println(*(p+1));
  }
while (*(p+2)<10 && *(p)<10 && *(p+1)<10){
  stopo(500);
  }
}
