import processing.serial.*;

Serial port;
String message;
PFont f;
int data0;
int data1;
int data2;
int data3;

int data4;
int data5;
int data6;
int data7;


int data8;
int data9;


PImage bg;
int dim;


void setup() {
  dim = width/2;
  port = new Serial(this, Serial.list()[0], 9600);
  size(1118, 800);
  f = createFont("Arial", 25, true);
  bg = loadImage("stelka.png");
  colorMode(HSB, 360, 100, 100);
  noStroke();
  ellipseMode(RADIUS);
  frameRate(7);
  
}


void draw() {
  background(bg);
  if (port.available()>0) {
    message = port.readString();
    println(message); // выводим message в консоль
    textFont(f);
    //text(message, 10, 50);
    fill(204, 102, 0);
    if (message.length() > 11) {
    data0 = Integer.parseInt(message.substring(0,1))*100 + Integer.parseInt(message.substring(1,2))*10+Integer.parseInt(message.substring(2,3));
    check(data0,200,505);
   // }
   // if (message.length() >4) {
    data1 = Integer.parseInt(message.substring(3,4))*100 + Integer.parseInt(message.substring(4,5))*10+Integer.parseInt(message.substring(5,6)); 
  check(data1,390,497);
   }
//}
 // if (message.length() >7) {
   if (message.length() > 11) {
    data2 = Integer.parseInt(message.substring(6,7))*100 + Integer.parseInt(message.substring(7,8))*10+Integer.parseInt(message.substring(8,9)); 
  check(data2,550,497);
      data3 = Integer.parseInt(message.substring(9,10))*100 + Integer.parseInt(message.substring(10,11))*10+Integer.parseInt(message.substring(12,13)); 
  check(data3,748,493);
  
   data4 = Integer.parseInt(message.substring(12,13))*100 + Integer.parseInt(message.substring(13,14))*10+ Integer.parseInt(message.substring(14,15));//+Integer.parseInt(message.substring(8,9)); 
  check(data4,225,350);
  //println(data4);
     data5 = Integer.parseInt(message.substring(15,16))*100 + Integer.parseInt(message.substring(16,17))*10+ Integer.parseInt(message.substring(17,18));//+Integer.parseInt(message.substring(8,9)); 
  check(data5,390,330);
  
       data6 = Integer.parseInt(message.substring(18,19))*100 + Integer.parseInt(message.substring(19,20))*10+ Integer.parseInt(message.substring(20,21));//+Integer.parseInt(message.substring(8,9)); 
  check(data6,555,350);
  
         data7 = Integer.parseInt(message.substring(21,22))*100 + Integer.parseInt(message.substring(22,23))*10+ Integer.parseInt(message.substring(23,24));//+Integer.parseInt(message.substring(8,9)); 
  check(data7,735,370);
  
  
         data8 = Integer.parseInt(message.substring(24,25))*100 + Integer.parseInt(message.substring(25,26))*10+ Integer.parseInt(message.substring(27,28));//+Integer.parseInt(message.substring(8,9)); 
  check(data8,917,370);
  
     data9 = Integer.parseInt(message.substring(28,29))*100 + Integer.parseInt(message.substring(29,30))*10;//+ Integer.parseInt(message.substring(30,31));//+Integer.parseInt(message.substring(8,9)); 
  check(data9,905,495);
  
  
    /*  data3 = Integer.parseInt(message.substring(9,10))*100 + Integer.parseInt(message.substring(10,11))*10;//+Integer.parseInt(message.substring(12,12)); 
  check(data3,800,400);*/
   }
//}
    //data0 = 0;
    //data0 = (int)(tenzo0[0]*100+tenzo0[1]*10+tenzo0[2]);
   //println(data0);
   // data0 = Integer.parseInt(tenzo0[0]);
    
    //check(data1,700,400);
/*

    if ((data>15)&(data<=50)) {
      fill(255, 255, 0);
      ellipse(400, 400, 80, 80 );
    }
    if ((data>0)&(data<=15)) {
      fill(0, 255, 0);
      ellipse(400, 400, 50, 50 );
    }
    if (data>50) {
      fill(255, 0, 0);
      ellipse(400, 400, 120, 120 );
    }
    println(data);*/
    //text(message, 10, 50);
//  }
}
  delay(200);

}


void drawGradient(float x, float y, int color1, int color2) {
  //int radius = dim/2;
  float h = random(color1, color2);
  for (int r = 40; r > 0; --r) {
    fill(h, 90, 90);
    ellipse(x, y, r, r);
    h = (h + 1) % 360;
  }
}

void check(int data,int x, int y) {

    if ((data>15)&(data<=90)) {
     //   for (int a = 0; a <= width; x+=dim) {
      drawGradient(x,y,40,100); //желтый
      //  }
      //fill(255, 255, 0);
      //ellipse(x, y, 80, 80 );
    }
    if ((data>0)&(data<=15)) {
       // for (int a = 0; a <= width; x+=dim) {
      drawGradient(x,y,100,130); //зеленый
       // }
      //fill(0, 255, 0);
      //ellipse(x, y, 50, 50 );
    }
    if (data>90) {
        
      drawGradient(x,y,0,40); //оранжевый
        
      //fill(255, 0, 0);
      //ellipse(x, y, 120, 120 );
    }
    //println(data);
    fill(0);
    text(data, x-20, y+10);

}
