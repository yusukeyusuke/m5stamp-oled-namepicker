#define LGFX_USE_V1

#include <LovyanGFX.hpp>
#include "names.h"

// SAMD21でLovyanGFXを独自設定で利用する場合の設定例

/*
このファイルを複製し、新しい名前を付けて、環境に合わせて設定内容を変更してください。
作成したファイルをユーザープログラムからincludeすることで利用可能になります。
複製したファイルはライブラリのlgfx_userフォルダに置いて利用しても構いませんが、
その場合はライブラリのアップデート時に削除される可能性があるのでご注意ください。
安全に運用したい場合はバックアップを作成しておくか、ユーザープロジェクトのフォルダに置いてください。
//*/


/// 独自の設定を行うクラスを、LGFX_Deviceから派生して作成します。
class LGFX : public lgfx::LGFX_Device
{
/*
 クラス名は"LGFX"から別の名前に変更しても構いません。
 AUTODETECTと併用する場合は"LGFX"は使用されているため、LGFX以外の名前に変更してください。
 また、複数枚のパネルを同時使用する場合もそれぞれに異なる名前を付けてください。
 ※ クラス名を変更する場合はコンストラクタの名前も併せて同じ名前に変更が必要です。
 名前の付け方は自由に決めて構いませんが、設定が増えた場合を想定し、
 例えばSeeed XIAOでSPI接続のILI9341の設定を行った場合、
  LGFX_XIAO_SPI_ILI9341
 のような名前にし、ファイル名とクラス名を一致させておくことで、利用時に迷いにくくなります。
//*/


// 接続するパネルの型にあったインスタンスを用意します。
//lgfx::Panel_GC9A01      _panel_instance;
//lgfx::Panel_GDEW0154M09 _panel_instance;
//lgfx::Panel_HX8357B     _panel_instance;
//lgfx::Panel_HX8357D     _panel_instance;
//lgfx::Panel_ILI9163     _panel_instance;
//lgfx::Panel_ILI9341     _panel_instance;
//lgfx::Panel_ILI9342     _panel_instance;
//lgfx::Panel_ILI9481     _panel_instance;
//lgfx::Panel_ILI9486     _panel_instance;
//lgfx::Panel_ILI9488     _panel_instance;
//lgfx::Panel_IT8951      _panel_instance;
//lgfx::Panel_SH110x      _panel_instance; // SH1106, SH1107
lgfx::Panel_SSD1306     _panel_instance;
//lgfx::Panel_SSD1327     _panel_instance;
//lgfx::Panel_SSD1331     _panel_instance;
//lgfx::Panel_SSD1351     _panel_instance; // SSD1351, SSD1357
//lgfx::Panel_SSD1963     _panel_instance;
//lgfx::Panel_ST7735      _panel_instance;
//lgfx::Panel_ST7735S     _panel_instance;
//lgfx::Panel_ST7789      _panel_instance;
//lgfx::Panel_ST7796      _panel_instance;


// パネルを接続するバスの種類にあったインスタンスを用意します。
//lgfx::Bus_SPI       _bus_instance;   // SPIバスのインスタンス
lgfx::Bus_I2C       _bus_instance;   // I2Cバスのインスタンス (ESP32のみ)
//lgfx::Bus_Parallel8 _bus_instance;   // 8ビットパラレルバスのインスタンス (ESP32のみ)

public:

  // コンストラクタを作成し、ここで各種設定を行います。
  // クラス名を変更した場合はコンストラクタも同じ名前を指定してください。
  LGFX(void)
  {
    { // バス制御の設定を行います。
      auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。


// ※ ピン番号の設定は、Arduino互換用のピン番号ではなく、"PA07" 等の実際のMCUのポート番号を指定します。
// ※ SERCOMのPAD設定は不要です。LGFX内部でSERCOM番号とポート番号を元にPADを自動設定する仕組みになっています。
// I2Cバスの設定
//      cfg.sercom_index = 0;         // 使用するSERCOMの番号を指定
//      cfg.freq_write  = 400000;     // 送信時のクロック
//      cfg.freq_read   = 400000;     // 受信時のクロック
//      cfg.pin_sda = lgfx::samd21::PORT_A | 8; // I2CのSDAをピン番号を設定
//      cfg.pin_scl = lgfx::samd21::PORT_A | 9; // I2CのSCLをピン番号を設定
      cfg.pin_scl = 21;
      cfg.pin_sda = 19;
      cfg.i2c_addr    = 0x3C;       // I2Cデバイスのアドレス
      cfg.i2c_port =0;

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
      //cfg.offset_x         =     0;  // パネルのX方向オフセット量
      //cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     2;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      //cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      //cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      //cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      //cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      //cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      //cfg.dlen_16bit       = false;  // データ長を16bit単位で送信するパネルの場合 trueに設定
      //cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance); // 使用するパネルをセットします。
  } 
};



/// 独自の設定を行うクラスを、LGFX_Deviceから派生して作成します。
class LGFX2 : public lgfx::LGFX_Device
{
/*
 クラス名は"LGFX"から別の名前に変更しても構いません。
 AUTODETECTと併用する場合は"LGFX"は使用されているため、LGFX以外の名前に変更してください。
 また、複数枚のパネルを同時使用する場合もそれぞれに異なる名前を付けてください。
 ※ クラス名を変更する場合はコンストラクタの名前も併せて同じ名前に変更が必要です。
 名前の付け方は自由に決めて構いませんが、設定が増えた場合を想定し、
 例えばSeeed XIAOでSPI接続のILI9341の設定を行った場合、
  LGFX_XIAO_SPI_ILI9341
 のような名前にし、ファイル名とクラス名を一致させておくことで、利用時に迷いにくくなります。
//*/


// 接続するパネルの型にあったインスタンスを用意します。
//lgfx::Panel_GC9A01      _panel_instance;
//lgfx::Panel_GDEW0154M09 _panel_instance;
//lgfx::Panel_HX8357B     _panel_instance;
//lgfx::Panel_HX8357D     _panel_instance;
//lgfx::Panel_ILI9163     _panel_instance;
//lgfx::Panel_ILI9341     _panel_instance;
//lgfx::Panel_ILI9342     _panel_instance;
//lgfx::Panel_ILI9481     _panel_instance;
//lgfx::Panel_ILI9486     _panel_instance;
//lgfx::Panel_ILI9488     _panel_instance;
//lgfx::Panel_IT8951      _panel_instance;
//lgfx::Panel_SH110x      _panel_instance; // SH1106, SH1107
lgfx::Panel_SSD1306     _panel_instance2;
//lgfx::Panel_SSD1327     _panel_instance;
//lgfx::Panel_SSD1331     _panel_instance;
//lgfx::Panel_SSD1351     _panel_instance; // SSD1351, SSD1357
//lgfx::Panel_SSD1963     _panel_instance;
//lgfx::Panel_ST7735      _panel_instance;
//lgfx::Panel_ST7735S     _panel_instance;
//lgfx::Panel_ST7789      _panel_instance;
//lgfx::Panel_ST7796      _panel_instance;


// パネルを接続するバスの種類にあったインスタンスを用意します。
//lgfx::Bus_SPI       _bus_instance;   // SPIバスのインスタンス
lgfx::Bus_I2C       _bus_instance2;   // I2Cバスのインスタンス (ESP32のみ)
//lgfx::Bus_Parallel8 _bus_instance;   // 8ビットパラレルバスのインスタンス (ESP32のみ)

public:

  // コンストラクタを作成し、ここで各種設定を行います。
  // クラス名を変更した場合はコンストラクタも同じ名前を指定してください。
  LGFX2(void)
  {
    { // バス制御の設定を行います。
      auto cfg = _bus_instance2.config();    // バス設定用の構造体を取得します。


// ※ ピン番号の設定は、Arduino互換用のピン番号ではなく、"PA07" 等の実際のMCUのポート番号を指定します。
// ※ SERCOMのPAD設定は不要です。LGFX内部でSERCOM番号とポート番号を元にPADを自動設定する仕組みになっています。
// I2Cバスの設定
//      cfg.sercom_index = 0;         // 使用するSERCOMの番号を指定
//      cfg.freq_write  = 400000;     // 送信時のクロック
//      cfg.freq_read   = 400000;     // 受信時のクロック
//      cfg.pin_sda = lgfx::samd21::PORT_A | 8; // I2CのSDAをピン番号を設定
//      cfg.pin_scl = lgfx::samd21::PORT_A | 9; // I2CのSCLをピン番号を設定
      cfg.pin_scl = 21;
//      cfg.pin_scl = 32;
      cfg.pin_sda = 18;
      cfg.i2c_addr    = 0x3C;       // I2Cデバイスのアドレス
      cfg.i2c_port =1;
      
      _bus_instance2.config(cfg);    // 設定値をバスに反映します。
      _panel_instance2.setBus(&_bus_instance2);      // バスをパネルにセットします。
    }

    { // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance2.config();    // 表示パネル設定用の構造体を取得します。

      // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

      cfg.memory_width     =   128;  // ドライバICがサポートしている最大の幅
      cfg.memory_height    =   64;  // ドライバICがサポートしている最大の高さ
      cfg.panel_width      =   128;  // 実際に表示可能な幅
      cfg.panel_height     =    64;  // 実際に表示可能な高さ
      //cfg.offset_x         =     0;  // パネルのX方向オフセット量
      //cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     2;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      //cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      //cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      //cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      //cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      //cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      //cfg.dlen_16bit       = false;  // データ長を16bit単位で送信するパネルの場合 trueに設定
      //cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance2.config(cfg);
    }

    setPanel(&_panel_instance2); // 使用するパネルをセットします。
  } 
};

static LGFX lcd2;
static LGFX2 lcd;
static LGFX_Sprite canvas(&lcd );


int pushButton = 39;
int classButton = 26;
int nameButton = 36;

int classButtonPress = 0;
int nameButtonPress = 0;

int lcdPower = 22;
int lcdGnd = 25;

RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR int currentClass=0;
RTC_DATA_ATTR int currentName=0;
RTC_DATA_ATTR byte nameOrder[MAX_NAMES];

void randomizeNameOrder(){
  randomSeed(millis()); // CPU起動からの時刻をシードに設定
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
  lcd2.init();

  canvas.setTextWrap(false);
  canvas.createSprite(256, 64);
  canvas.fillScreen(TFT_BLACK);
  canvas.setTextColor(TFT_WHITE);
  canvas.setCursor(0,0);
  canvas.setPivot(0,0);

  //canvas.fillRect(0,0,32,32,TFT_WHITE);
  //canvas.pushRotateZoom(0.0, 0, 0, 1.0 , 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
  //canvas.pushSprite(0, 0);
}

void setup(){
  //setCpuFrequencyMhz(50);
  bootCount++;
  if(bootCount > 30000){
    bootCount = 1;
  }
  randomSeed(bootCount);
  //Serial.begin(19200);
  pinMode(pushButton, INPUT);
  pinMode(classButton, INPUT_PULLDOWN);
  pinMode(nameButton, INPUT_PULLDOWN);
  pinMode(lcdPower, OUTPUT);
  pinMode(lcdGnd, OUTPUT);

  digitalWrite(lcdPower, HIGH);
  digitalWrite(lcdGnd, LOW);
  delay(50);
  lcdInits();
  //Serial.println("BOOTCOUNT");
  //Serial.println(bootCount);
  //Serial.println("SETUP DONE");
  
}

int KEEPTIME = 50;
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
    if(classButtonPress == 1){
      // inhibit key repeat
    } else {
      classButtonPress = 1;
      //Serial.println("CLASS PUSH");
      currentClass++;
      currentClass = currentClass%(sizeof(nums) / sizeof(nums[0])); // nums配列の範囲内に収める
      randomizeNameOrder();
      currentName=0;
      keepWake = KEEPTIME * 1.5+2;
      canvas.fillScreen(TFT_BLACK);
      canvas.fillRect(0,0,12,64,TFT_WHITE);
      canvas.setFont(&fonts::Font2);
      canvas.setTextColor(TFT_BLACK, TFT_WHITE);
      canvas.setCursor(2,0);
      canvas.printf("%d",(currentClass+1)/10);
      canvas.setCursor(2,16);
      canvas.printf("%d",(currentClass+1)%10);
      canvas.setTextColor(TFT_WHITE, TFT_BLACK);
      canvas.setFont(&fonts::lgfxJapanGothic_32);
      canvas.setCursor(14,12);
      canvas.println(classNames[currentClass]);
      canvas.setPivot(0,0);
      //canvas.pushRotateZoom(0.0, 0, 0, 1.0 , 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
      canvas.pushSprite(0, 0);
      canvas.pushSprite(&lcd2, -128, 0);
    }
  }else{
    classButtonPress = 0;
  }

  if(keepWake == KEEPTIME + 1){
    firstTime = 2;
  }
  
  if(digitalRead(nameButton)==HIGH || firstTime == 1 || firstTime == 2){
    if(nameButtonPress == 1){
      // inhibit key repeat
    } else {
      nameButtonPress = 1;
      if(firstTime == 1){
        randomizeNameOrder();
      }
      //Serial.println("NAME PUSH");
      //Serial.println(currentName);
      int num_name=nameOrder[currentName];
      currentName++;
      if(currentName >= nums[currentClass]){
        currentName = 0;
        randomizeNameOrder();
      }
      
      firstTime = 0;
      keepWake = KEEPTIME;
  
      canvas.fillScreen(TFT_BLACK);
  
      canvas.setTextColor(TFT_WHITE, TFT_BLACK);
      canvas.setFont(&fonts::lgfxJapanGothic_16);
      canvas.setCursor(0,0);
      canvas.println(nnn[currentClass][num_name*2+1]);
      canvas.setFont(&fonts::lgfxJapanGothic_32);
      canvas.setCursor(0,24);
      canvas.println(nnn[currentClass][num_name*2]);
  
      canvas.fillRect(256-32,0,256,16,TFT_WHITE);
      canvas.setTextColor(TFT_BLACK, TFT_WHITE);
      canvas.setFont(&fonts::Font2);
      canvas.setCursor(256-32+4,0);
      canvas.printf("%d",(num_name+1)/10);
      canvas.setCursor(256-32+4+16,0);
      canvas.printf("%d",(num_name+1)%10);
  
      canvas.setPivot(0,0);
      canvas.pushSprite(0, 0);
      canvas.pushSprite(&lcd2, -128, 0);
      // canvas.pushRotateZoom(0.0, 0, 0, 1.0 , 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
    }
  }else{
    nameButtonPress = 0;
  }
    //canvas.pushRotateZoom(64, 16, aa,x , 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
    /*
  for (int angle = 0; angle <= 360; ++angle) {
    canvas.pushRotateZoom(64, 16, angle, 1.0, 1.0); // 画面中心に角度angle、幅2.5倍、高さ3倍で描画
    if ((angle % 36) == 0) lcd.display(); // 電子ペーパーの場合の表示更新を 36回に一度行う
  }
  */
  if(keepWake%10==0){
  //Serial.println("KeepWake");
  //Serial.println(keepWake);
  }
  
  keepWake--;
  if(keepWake <= 0){
      //Serial.println("SLEEEEEEEEP");
      canvas.fillScreen(TFT_BLACK);
      canvas.pushSprite(0, 0);
      canvas.pushSprite(&lcd2, -128, 0);

      esp_sleep_enable_ext1_wakeup( BIT64(GPIO_NUM_26) | BIT64(GPIO_NUM_36) ,ESP_EXT1_WAKEUP_ANY_HIGH);
      esp_deep_sleep_start();
  }
  
  delay(100);
}
