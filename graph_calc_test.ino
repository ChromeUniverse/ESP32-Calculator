#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

Adafruit_ST7735 tft = Adafruit_ST7735(5, 14, 23, 18, 13);

int button1 = 34;
int button2 = 21;

void setup() {

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  Serial.begin(115200);
  tft.initR(INITR_GREENTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  double start = millis();
  axis();
  sine_wave();
  parabola();
  cubic();
  //quartic();
  double finish = millis();
  double runtime = (finish - start)/1000; //seconds
  Serial.println(runtime);
  
  //char result[8]; // Buffer big enough for 7-character double
  //dtostrf(runtime, 6, 2, result); // Leave room for too large numbers!
  
  //char text = "DONE! Runtime: " + sprintf(finish-start/1000) + " s";
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextWrap(true);
  tft.print("DONE! Runtime: ");
  tft.print(runtime, 3);
  
}


double xmin = -10;
double xmax = 10;

double xspan = xmax - xmin;

double xscl = 1;

double ymin = -10;
double ymax = 10;

double yspan = ymax - ymin;

double yscl = 1;

double xres = xspan/tft.width();
double yres = yspan/tft.height();

double xcurrent = xmin;

int i = 1;

int x_previous = 0;
int y_previous = 0;

bool first = false;

void loop() {  
  int button1state = digitalRead(button1);
  int button2state = digitalRead(button2);

  if (button1state == HIGH){
    xcurrent -= xres;
  }
  if (button2state == HIGH){
    xcurrent += xres;
  }

  double ycurrent = 6*sin(xcurrent);

  int x_pixels = round((xcurrent-0)/xres);
  int y_pixels = round((ycurrent-0)/yres);
  
  //Serial.println("Entry " + String(i) + ": This is the current X: " + String(xcurrent) + "; This is the current Y: " + String(ycurrent) + " NumPixels: " + String(round((ycurrent-0)/yres)) );
  
  int x_graph = tft.width()/2 + x_pixels;
  int y_graph = tft.height()/2 - y_pixels;
  Serial.println(String(xcurrent) + " " + String(ycurrent) + " "+ String(x_graph) + " " + String(y_graph) + " ");
  
  if (y_graph < 128 or y_graph > 0){
    tft.drawPixel(x_graph, y_graph, ST77XX_ORANGE);
  }
  
  if (first == false) {
    first = true;
  } else if (first == true and (y_graph < 128 or y_graph > 0)) {
    if (x_graph != x_previous and y_graph != y_previous){
      tft.drawPixel(x_previous, y_previous, ST77XX_BLACK);
    x_previous = x_graph;
    y_previous = y_graph;  
    }
  }
  
  i++;
  
  delay(100);
}

void axis(){
  for (int i = 0; i<160; i++){
    tft.drawPixel(tft.width()/2, i, ST77XX_RED);  
  }
  
  for (int i = 0; i<160; i++){
    tft.drawPixel(i, tft.height()/2, ST77XX_RED);  
  }

}

void sine_wave(){
  double xmin = -10;
  double xmax = 10;

  double xspan = xmax - xmin;
  
  double xscl = 1;
  
  double ymin = -10;
  double ymax = 10;

  double yspan = ymax - ymin;
  
  double yscl = 1;
  
  double xres = xspan/tft.width();
  double yres = yspan/tft.height();
  
  double xcurrent = xmin;

  int i = 1;

  int x_previous = 0;
  int y_previous = 0;

  bool first = false;
  
  while (xcurrent < xmax){ 
    double ycurrent = 6*sin(xcurrent);

    int x_pixels = round((xcurrent-0)/xres);
    int y_pixels = round((ycurrent-0)/yres);
    
    Serial.println("Entry " + String(i) + ": This is the current X: " + String(xcurrent) + "; This is the current Y: " + String(ycurrent) + " NumPixels: " + String(round((ycurrent-0)/yres)) );

    int x_graph = tft.width()/2 + x_pixels;
    int y_graph = tft.height()/2 - y_pixels;

    if (y_graph < 128 or y_graph > 0){
      tft.drawPixel(x_graph, y_graph, ST77XX_WHITE);
    }

    if (first == false) {
      first = true;
    } else if (first == true and (y_graph < 128 or y_graph > 0)) {
      tft.drawLine(x_previous, y_previous, x_graph, y_graph, ST77XX_WHITE);  
    }
    
    x_previous = x_graph;
    y_previous = y_graph;
    
    xcurrent += xres;
    
    i++;
  }
  
}

void cubic(){
  // width: 128px
  // height: 160px

  double xmin = -10;
  double xmax = 10;

  double xspan = xmax - xmin;
  
  double xscl = 1;
  
  double ymin = -10;
  double ymax = 10;

  double yspan = ymax - ymin;
  
  double yscl = 1;
  
  double xres = xspan/tft.width();
  double yres = yspan/tft.height();
  
  double xcurrent = xmin;

  int i = 1;

  int x_previous = 0;
  int y_previous = 0;

  bool first = false;
  
  while (xcurrent < xmax){ 
    double ycurrent = pow(0.6*xcurrent,3) - 5*xcurrent;

    int x_pixels = round((xcurrent-0)/xres);
    int y_pixels = round((ycurrent-0)/yres);
    
    Serial.println("Entry " + String(i) + ": This is the current X: " + String(xcurrent) + "; This is the current Y: " + String(ycurrent) + " NumPixels: " + String(round((ycurrent-0)/yres)) );

    int x_graph = tft.width()/2 + x_pixels;
    int y_graph = tft.height()/2 - y_pixels;

    if (y_graph < 128 or y_graph > 0){
      tft.drawPixel(x_graph, y_graph, ST77XX_WHITE);
    }

    if (first == false) {
      first = true;
    } else if (first == true and (y_graph < 128 or y_graph > 0)) {
      tft.drawLine(x_previous, y_previous, x_graph, y_graph, ST77XX_GREEN);  
    }
    
    x_previous = x_graph;
    y_previous = y_graph;
    
    xcurrent += xres;
    
    i++;
  }
  
}

void parabola(){
  // width: 128px
  // height: 160px

  double xmin = -10;
  double xmax = 10;

  double xspan = xmax - xmin;
  
  double xscl = 1;
  
  double ymin = -10;
  double ymax = 10;

  double yspan = ymax - ymin;
  
  double yscl = 1;
  
  double xres = xspan/tft.width();
  double yres = yspan/tft.height();
  
  double xcurrent = xmin;

  int i = 1;

  int x_previous = 0;
  int y_previous = 0;

  bool first = false;
  
  while (xcurrent < xmax){ 
    double ycurrent = pow(0.8*xcurrent,2) - 5*xcurrent;

    int x_pixels = round((xcurrent-0)/xres);
    int y_pixels = round((ycurrent-0)/yres);
    
    Serial.println("Entry " + String(i) + ": This is the current X: " + String(xcurrent) + "; This is the current Y: " + String(ycurrent) + " NumPixels: " + String(round((ycurrent-0)/yres)) );

    int x_graph = tft.width()/2 + x_pixels;
    int y_graph = tft.height()/2 - y_pixels;

    if (y_graph < 128 or y_graph > 0){
      tft.drawPixel(x_graph, y_graph, ST77XX_WHITE);
    }

    if (first == false) {
      first = true;
    } else if (first == true and (y_graph < 128 or y_graph > 0)) {
      tft.drawLine(x_previous, y_previous, x_graph, y_graph, ST77XX_BLUE);  
    }
    
    x_previous = x_graph;
    y_previous = y_graph;
    
    xcurrent += xres;
    
    i++;
  }
  
}

void quartic(){
  // width: 128px
  // height: 160px

  double xmin = -10;
  double xmax = 10;

  double xspan = xmax - xmin;
  
  double xscl = 1;
  
  double ymin = -10;
  double ymax = 10;

  double yspan = ymax - ymin;
  
  double yscl = 1;
  
  double xres = xspan/tft.width();
  double yres = yspan/tft.height();
  
  double xcurrent = xmin;

  int i = 1;

  int x_previous = 0;
  int y_previous = 0;

  bool first = false;
  
  while (xcurrent < xmax){ 
    double ycurrent = pow(3*xcurrent,4) - 5*pow(xcurrent,3);

    int x_pixels = round((xcurrent-0)/xres);
    int y_pixels = round((ycurrent-0)/yres);
    
    Serial.println("Entry " + String(i) + ": This is the current X: " + String(xcurrent) + "; This is the current Y: " + String(ycurrent) + " NumPixels: " + String(round((ycurrent-0)/yres)) );

    int x_graph = tft.width()/2 + x_pixels;
    int y_graph = tft.height()/2 - y_pixels;

    if (y_graph < 128 or y_graph > 0){
      tft.drawPixel(x_graph, y_graph, ST77XX_WHITE);
    }

    if (first == false) {
      first = true;
    } else if (first == true and (y_graph < 128 or y_graph > 0)) {
      tft.drawLine(x_previous, y_previous, x_graph, y_graph, ST77XX_BLUE);  
    }
    
    x_previous = x_graph;
    y_previous = y_graph;
    
    xcurrent += xres;
    
    i++;
  }
  
}
