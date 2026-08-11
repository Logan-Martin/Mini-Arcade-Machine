#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>

// --- Touchscreen pin definitions ---
#define YP A3
#define XM A2
#define YM 9
#define XP 8

// --- Touchscreen calibration values (adjust as needed) ---
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define MINPRESSURE 100
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// --- LCD control pins ---
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// --- Colors ---
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define YELLOW 0xFFE0

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// --- Question structure ---
struct Question {
 const char* text;
 const char* choices[4];
 int correctIndex;
};

// --- Question bank ---
// this section is sorted as: {"question",{"answer 0", "answer 1", "answer 2", "answer 3"}, number for correct answer}
// feel free to customize this bank. the MEGA 2560 r3 can hold about 100 questions.

Question allQuestions[] = {
 {"Who was the main guy in communism during c.r.?", {"mao", "sun yat sen", "deng xiapeng", "cheng kai shek"}, 0},
 {"Incriminating poster used to attack people during the Cultural Revolution?", {"propaganda", "meanie sheet", "da zi bao", "mao poster"}, 2},
 {"The carving up of China by European powers into spheres of influence was known as what?", {"Europeans giving to China", "Cutting the melon", "The Great Wall", "Unequal treaties"}, 1},
 {"Why did China lose the Opium Wars?", {"Unmotivated army", "Depressed populace", "Technological isolationism", "Mao"}, 2},
};

const int numQuestions = sizeof(allQuestions) / sizeof(Question);
int questionOrder[numQuestions];

// --- Shuffle the questions ---
void shuffleQuestions() {
 for (int i = 0; i < numQuestions; i++) {
 questionOrder[i] = i;
 }
 for (int i = numQuestions - 1; i > 0; i--) {
 int j = random(i + 1);
 int temp = questionOrder[i];
 questionOrder[i] = questionOrder[j];
 questionOrder[j] = temp;
 }
}

void shuffleChoices(Question &q) {
 const char* originalChoices[4];
 for (int i = 0; i < 4; i++) {
 originalChoices[i] = q.choices[i];
 }
 
 int indices[] = {0, 1, 2, 3};
 for (int i = 3; i > 0; i--) {
 int j = random(i + 1);
 int temp = indices[i];
 indices[i] = indices[j];
 indices[j] = temp;
 }

 int newCorrectIndex = -1;
 for (int i = 0; i < 4; i++) {
 q.choices[i] = originalChoices[indices[i]];
 if (indices[i] == q.correctIndex) {
 newCorrectIndex = i;
 }
 }
 q.correctIndex = newCorrectIndex;
}

// --- Text wrapping ---
void printWrappedText(const char* text, int x, int y, int maxWidthChars, int lineHeight) {
 tft.setCursor(x, y);
 char tempText[256];
 strcpy(tempText, text);
 char* rest = tempText;
 char* word;
 String line = "";
 
 while ((word = strtok_r(rest, " ", &rest))) {
 if (line.length() + strlen(word) + (line.length() > 0 ? 1 : 0) > maxWidthChars) {
 tft.print(line);
 y += lineHeight;
 tft.setCursor(x, y);
 line = word;
 line += " ";
 } else {
 line += word;
 line += " ";
 }
 }
 if (line.length() > 0) {
 tft.print(line);
 }
}

// --- Draw question and answers ---
void drawQuestion(Question &q) {
 shuffleChoices(q);
 tft.fillScreen(BLACK);
 tft.setTextColor(WHITE);
 tft.setTextSize(2);

 printWrappedText(q.text, 10, 10, 30, 18);

 for (int i = 0; i < 4; i++) {
 int x = (i % 2) * (SCREEN_WIDTH / 2);
 int y = 60 + (i / 2) * (SCREEN_HEIGHT - 60) / 2;
 uint16_t color;
 switch (i) {
 case 0: color = RED; break;
 case 1: color = BLUE; break;
 case 2: color = GREEN; break;
 case 3: color = YELLOW; break;
 }
 tft.fillRect(x, y, SCREEN_WIDTH / 2, (SCREEN_HEIGHT - 60) / 2, color);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.setCursor(x + 5, y + 5);
 tft.print((char)('A' + i));
 tft.print(":");
 printWrappedText(q.choices[i], x + 15, y + 25, 15, 15);
 }
}

// --- Get which answer was touched ---
int getAnswerTouch() {
 TSPoint p = ts.getPoint();
 pinMode(XM, OUTPUT);
 pinMode(YP, OUTPUT);

 if (p.z < MINPRESSURE || p.z > MAXPRESSURE) {
 return -1;
 }

 int x = map(p.y, TS_MINY, TS_MAXY, SCREEN_WIDTH, 0);
 int y = map(p.x, TS_MINX, TS_MAXX, SCREEN_HEIGHT, 0);

 for (int i = 0; i < 4; i++) {
 int bx = (i % 2) * (SCREEN_WIDTH / 2);
 int by = 60 + (i / 2) * (SCREEN_HEIGHT - 60) / 2;
 if (x > bx && x < bx + (SCREEN_WIDTH / 2) && y > by && y < by + (SCREEN_HEIGHT - 60) / 2) {
 return i;
 }
 }
 return -1;
}

// --- Show feedback ---
void showResult(bool correct) {
 tft.fillScreen(correct ? GREEN : RED);
 tft.setTextColor(BLACK);
 tft.setTextSize(3);
 tft.setCursor(80, 100);
 tft.print(correct ? "Correct!" : "Wrong!");
 delay(1500);
 Serial.print(correct ? "Correct!" : "Wrong!");
}

// --- Setup ---
void setup() {
 Serial.begin(9600);
 randomSeed(analogRead(0));

 tft.reset();
 tft.begin(0x9341);
 tft.setRotation(1);
 tft.fillScreen(BLACK);

 shuffleQuestions();
}

// --- Main loop ---
void loop() {
 static int currentQuestionIndex = 0;

 if (currentQuestionIndex >= numQuestions) {
 tft.fillScreen(BLACK);
 tft.setTextColor(GREEN);
 tft.setTextSize(4);
 tft.setCursor(30, 100);
 tft.print("Quiz Complete!");
 Serial.println("Quiz complete");
 while (true);
 }

 int qIndex = questionOrder[currentQuestionIndex];
 Question q = allQuestions[qIndex];
 drawQuestion(q);

 int selected = -1;
 while (selected == -1) {
 selected = getAnswerTouch();
 delay(200);
 }

 // Wait for user to lift finger
 TSPoint p;
 do {
 p = ts.getPoint();
 pinMode(XM, OUTPUT);
 pinMode(YP, OUTPUT);
 delay(50);
 } while (p.z > MINPRESSURE && p.z < MAXPRESSURE);

 bool correct = (selected == q.correctIndex);
 showResult(correct);
 currentQuestionIndex++;
}
