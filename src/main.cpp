#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ArduinoQueue.h>
#include <StackArray.h>

// initializing display object
Adafruit_ST7735 tft = Adafruit_ST7735(5, 14, 23, 18, 13);

// defining Token class
class Token {

  private:
    // data attributes
    int tokenType;        // 0 -> number token
                          // 1 -> operator token
                          // 2 -> L_paren
                          // 3 -> R_paren

    String tokenText;     // token's text

  public:
    // class constructor
    // -> creates new token instance
    Token (String text, int type) {
      tokenType = type;
      tokenText = text;
    };

    // returns type of token
    int getType () {
      return tokenType;
    }

    // returns token's text
    String getText () {
      return tokenText;
    }

    // returns operator precedence ranking
    // assumes it's *only* going to be called for Operator tokens

    /* Operator precedence, highest to lowest:

        ^      > exponent
        * , /  > multiplication, division
        + , -  > addition, subtraction
        =      > equals sign
        (      > L_PAREN --- overrides precedence

    */

    int getPrecedence() {
      if (tokenText == "^") return 4;
      if (tokenText == "*" || tokenText == "/") return 3;
      if (tokenText == "+" || tokenText == "-") return 2;
      if (tokenText == "=") return 1;
      if (tokenText == "(") return 0;
    }

    // useless token class destructor
    //virtual ~Token ();
};


// draws coordinate axes on the display
void draw_axis(){
  for (int i = 0; i<160; i++){
    tft.drawPixel(tft.width()/2, i, ST77XX_RED);
  }

  for (int i = 0; i<160; i++){
    tft.drawPixel(i, tft.height()/2, ST77XX_RED);
  }

}


// draws a sine wave on the display
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

// program setup
void setup() {

  Serial.begin(115200);
  tft.initR(INITR_GREENTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  //double start = millis();

  // draws coordinate axes
  draw_axis();
  // draws function graphs
  //sine_wave();


  /*
  // stopwatch
  double finish = millis();
  double runtime = (finish - start)/1000; //seconds
  Serial.println(runtime);
  */

  //char result[8]; // Buffer big enough for 7-character double
  //dtostrf(runtime, 6, 2, result); // Leave room for too large numbers!

  //char text = "DONE! Runtime: " + sprintf(finish-start/1000) + " s";

  /*
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextWrap(true);
  tft.print("DONE! Runtime: ");
  */

  //tft.print(runtime, 3);

}



// main program loop
void loop() {

  // reset math expression, stored in string
  String expression = "";

  // reading input from the serial terminal
  if (Serial.available() > 0) {
    /*
    int ByteReceived = Serial.read();
    Serial.print(ByteReceived);
    Serial.print("        ");
    Serial.print(ByteReceived, HEX);
    Serial.print("       ");
    Serial.print(char(ByteReceived));
    Serial.println();
    */


    // clear the display
    tft.drawRect(0, 0, tft.width(), 10, ST77XX_BLACK);
    tft.fillRect(0, 0, tft.width(), 10, ST77XX_BLACK);

    // read the incoming byte:
    expression = Serial.readStringUntil('\r');

    if (expression.length() > 1) {
      Serial.println("Got math: " + expression + ".");

      // Printing the math expression to the TFT display
      tft.setCursor(0, 0);
      tft.setTextColor(ST77XX_ORANGE);
      tft.setTextWrap(true);
      tft.print("Here is math: " + expression);




    }

  }
}
