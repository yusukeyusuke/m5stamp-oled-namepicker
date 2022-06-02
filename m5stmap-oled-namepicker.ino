#define LGFX_USE_V1

#include <LovyanGFX.hpp>
#include "names.h"

class LGFX : public lgfx::LGFX_Device
{
lgfx::Panel_SSD1306     _panel_instance;
lgfx::Bus_I2C       _bus_instance;   // I2Cバスのインスタンス (ESP32のみ)

public:
  LGFX(void)
  {
    { // バス制御の設定を行います。
      auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。
      cfg.pin_scl = 21;
      cfg.pin_sda = 19;
      cfg.i2c_addr    = 0x3C;       // I2Cデバイスのアドレス

      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }

    { // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

      // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

      cfg.memory_width     =   128;  // ドライバICがサポートしている最大の幅
      cfg.memory_height    =   64;  // ドライバICがサポートしている最大の高さ
      cfg.panel_width      =   128;  // 実際に表示可能な幅
      cfg.panel_height     =    64;  // 実際に表示可能な高さ

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance); // 使用するパネルをセットします。
  } 
};

static LGFX lcd;
static LGFX_Sprite canvas(&lcd);


int pushButton = 39;
int classButton = 26;
int nameButton = 36;

int lcdPower = 22;
int lcdGnd = 25;

RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int currentClass=0;
RTC_DATA_ATTR int currentName=0;
RTC_DATA_ATTR byte nameOrder[MAX_NAMES];

void randomizeNameOrder(){
  int num = nums[currentClass];
  for(int i=0;i<num;i++){
    nameOrder[i]=i;
  }
  for(int i=num-1;i>=0;i--){
    int r = random(i+1);
    int tmp = nameOrder[i];
    nameOrder[i] = nameOrder[r];
    nameOrder[r] = tmp;
  }
}




void lcdInits() {
  lcd.init();
  canvas.setTextWrap(false);
  canvas.createSprite(384, 32);
  canvas.fillScreen(TFT_BLACK);
  canvas.setTextColor(TFT_WHITE);
  canvas.setCursor(0,0);
  canvas.setFont(&fonts::lgfxJapanGothic_32);
  //canvas.println("日本語");
  //canvas.printf("%d",ttt);
  uint8_t white = 0x0FF;
//  canvas.fillRect(5,5,10,10,white);
//  canvas.pushSprite(0, 0);
  canvas.setPivot(0,0);

}

void setup(){
  pinMode(pushButton, INPUT);
  pinMode(classButton, INPUT_PULLDOWN);
  pinMode(nameButton, INPUT_PULLDOWN);
  pinMode(lcdPower, OUTPUT);
  pinMode(lcdGnd, OUTPUT);

  digitalWrite(lcdPower, HIGH);
  digitalWrite(lcdGnd, LOW);
  setCpuFrequencyMhz(10);
  //delay(5);
  lcdInits();
}

int KEEPTIME = 200;
int keepWake = KEEPTIME;
float dir=-0.01;
float x=1;
int n = 0;
int firstTime = 1;
void loop(){

  /*
  if(digitalRead(pushButton)==LOW){
    digitalWrite(lcdPower, LOW);
    delay(1000);
    digitalWrite(lcdPower, HIGH);
    delay(10);
    lcdInits();
  }
  */
  if(digitalRead(classButton)==HIGH){
    currentClass++;
    currentClass = currentClass%3;
    randomizeNameOrder();
    currentName=0;
    keepWake = KEEPTIME * 2;
    canvas.fillScreen(TFT_BLACK);
    canvas.fillRect(0,0,12,32,TFT_WHITE);
    canvas.setFont(&fonts::Font2);
    canvas.setTextColor(TFT_BLACK, TFT_WHITE);
    canvas.setCursor(2,0);
    canvas.printf("%d",(currentClass+1)/10);
    canvas.setCursor(2,16);
    canvas.printf("%d",(currentClass+1)%10);
    canvas.setTextColor(TFT_WHITE, TFT_BLACK);
    canvas.setFont(&fonts::lgfxJapanGothic_16);
    canvas.setCursor(14,12);
    canvas.println(classNames[currentClass]);
    canvas.setPivot(0,0);
    canvas.pushRotateZoom(0.0, 0, 0, 1.0 , 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
  }

  if(keepWake == KEEPTIME + 1){
    firstTime = 1;
  }
  
  if(digitalRead(nameButton)==HIGH || firstTime == 1){
    int num_name=nameOrder[currentName];
    currentName++;
    if(currentName >= nums[currentClass]){
      currentName = 0;
      randomizeNameOrder();
    }
    
    firstTime = 0;
    keepWake = KEEPTIME;
    canvas.fillScreen(TFT_BLACK);
    canvas.fillRect(0,0,12,32,TFT_WHITE);
    canvas.setFont(&fonts::Font2);
    canvas.setTextColor(TFT_BLACK, TFT_WHITE);
    canvas.setCursor(2,0);
    canvas.printf("%d",(num_name+1)/10);
    canvas.setCursor(2,16);
    canvas.printf("%d",(num_name+1)%10);
    canvas.setTextColor(TFT_WHITE, TFT_BLACK);
    canvas.setFont(&fonts::lgfxJapanGothic_12);
    canvas.setCursor(14,0);
    canvas.println(nnn[currentClass][num_name*2+1]);
    canvas.setFont(&fonts::lgfxJapanGothic_16);
    canvas.setCursor(14,12);
    canvas.println(nnn[currentClass][num_name*2]);
    canvas.setPivot(0,0);
    canvas.pushRotateZoom(0.0, 0, 0, 1.0 , 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
  }
    //canvas.pushRotateZoom(64, 16, aa,x , 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
    /*
  for (int angle = 0; angle <= 360; ++angle) {
    canvas.pushRotateZoom(64, 16, angle, 1.0, 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
    if ((angle % 36) == 0) lcd.display(); // 電子ペーパーの場合の表示更新を 36回に一度行う
  }
  */

  keepWake--;
  if(keepWake <= 0){
      esp_sleep_enable_ext1_wakeup( BIT64(GPIO_NUM_26) | BIT64(GPIO_NUM_36) ,ESP_EXT1_WAKEUP_ANY_HIGH);
      esp_deep_sleep_start();
  }
  
  delay(100);
}
