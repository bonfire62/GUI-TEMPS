#include <SPI.h>
#include <SD.h>
#include <net.h>

#include <EtherCard.h>
#include <enc28j60.h>
#include <Time.h>

#include <SoftwareSerial.h>

#include <EasyTransfer.h>

#include <OneWire.h>

#include <DallasTemperature.h>

/* Geothermal Control Main Program
 *
 *  Written by Kenneth Bonar
 *  7/21/2015
 */
#define ONE_WIRE_BUS 24
SoftwareSerial USB(50, 48); //RX, TX
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

// Dummy example variables
int size = 0;
int ledLight = 0;

int pause = 0;
int r = 65;
int g = 65;
int b = 225;
int graphValue = 0;
int fixedGraph = 0;
int rotaryRID, rotaryGID, rotaryBID;
float angle = 0;
// custom variables (temperature and fans)
// temp controls
int temp1 = 0; 
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
int temp5 = 0;
int temp6 = 0;
int temp7 = 0;
int temp8 = 0;
int temp9 = 0;
int temp10 = 0;
// begin fan controls
int pwmLevel1 = 0; 
int pwmLevel2 = 0;
int pwmLevel3 = 0;
int pwmLevel4 = 0;
int pwmLevel5 = 0;
int pwmLevel6 = 0;
int pwmLevel7 = 0;
int pwmLevel8 = 0;

int dataLogging = 0; // Controls if currently logging
int createLog = 2; // Button for method that starts log
int saveLog = 3; // Button for saving log
int statusLabel = 4;
int onButton = 5;
int offButton = 6;
int fan1;
int fan2;
int fan3;
int fan4;
int fan5;
int fan6;
int fan7;
int fan8;
int autoMode = 0; //Automatic Control Variable
int tempCtrl1 = 75; // temps to set for thermostat effect (auto)
int tempCtrl2 = 75;
int tempCtrl3 = 75;
int tempCtrl4 = 75;
int timeTemp1;
int closeLogStatus = 0;
int dataLogStatus = 0;


void setup() {

  // Start the guino dashboard interface.
  // The number is your personal key for saving data. This should be unique for each sketch
  // This key should also be changed if you change the gui structure. Hence the saved data vill not match.
  gBegin(34236);
  //sensors for temperature
  sensors.begin();
  //fan input
  r = 65;
  g = 65;
  b = 190;
  
  pwmLevel1 = pwmLevel2 = pwmLevel3 = pwmLevel4 = pwmLevel5 = pwmLevel6 = pwmLevel7 = pwmLevel8 = 0;
  gUpdateValue(&pwmLevel1);gUpdateValue(&pwmLevel2);gUpdateValue(&pwmLevel3);gUpdateValue(&pwmLevel4);gUpdateValue(&pwmLevel5);gUpdateValue(&pwmLevel6);gUpdateValue(&pwmLevel7);gUpdateValue(&pwmLevel8);
  pinMode(2, OUTPUT);// fan PWM controls
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(ONE_WIRE_BUS, INPUT);
  autoMode = 0;
}


void loop() {
  // **** Main update call for the guino
  guino_update();

  sensors.requestTemperatures();
  //temperature sensors begin

  float currentTemp1 = sensors.getTempCByIndex(0);
 
  float currentTemp2 = sensors.getTempCByIndex(1);
  
  float currentTemp3 = sensors.getTempCByIndex(2);
  
  float currentTemp4 = sensors.getTempCByIndex(3);

  float currentTemp5 = sensors.getTempCByIndex(4);

  float currentTemp6 = sensors.getTempCByIndex(5);
  
  float currentTemp7 = sensors.getTempCByIndex(6);
  
  float currentTemp8 = sensors.getTempCByIndex(7);
  
  float currentTemp9 = sensors.getTempCByIndex(8);
  

  int FarenheitTemp1 = DallasTemperature::toFahrenheit(currentTemp1);
  int FarenheitTemp2 = DallasTemperature::toFahrenheit(currentTemp2);
  int FarenheitTemp3 = DallasTemperature::toFahrenheit(currentTemp3);
  int FarenheitTemp4 = DallasTemperature::toFahrenheit(currentTemp4);
  int FarenheitTemp5 = DallasTemperature::toFahrenheit(currentTemp5);
  int FarenheitTemp6 = DallasTemperature::toFahrenheit(currentTemp6);
  int FarenheitTemp7 = DallasTemperature::toFahrenheit(currentTemp7);
  int FarenheitTemp8 = DallasTemperature::toFahrenheit(currentTemp8);
  int FarenheitTemp9 = DallasTemperature::toFahrenheit(currentTemp9);

  temp1 = FarenheitTemp1;
  temp2 = FarenheitTemp2;
  temp3 = FarenheitTemp3;
  temp4 = FarenheitTemp4;
  temp5 = FarenheitTemp5;
  temp6 = FarenheitTemp6;
  temp7 = FarenheitTemp7;
  temp8 = FarenheitTemp8;
  temp9 = FarenheitTemp9;

  //Fan Control
  analogWrite(2, pwmLevel1);
  analogWrite(3, pwmLevel2);
  analogWrite(4, pwmLevel3);
  analogWrite(5, pwmLevel4);
  analogWrite(6, pwmLevel5);
  analogWrite(7, pwmLevel6);
  analogWrite(8, pwmLevel7);
  analogWrite(9, pwmLevel8);

  //Send Values to GUI
  gUpdateValue(&temp1);
  gUpdateValue(&temp2);
  gUpdateValue(&temp3);
  gUpdateValue(&temp4);
  gUpdateValue(&temp5);
  gUpdateValue(&temp6);
  gUpdateValue(&temp7);
  gUpdateValue(&temp8);
  gUpdateValue(&temp9);
  

  if(autoMode)
  {
    if (temp1 > tempCtrl1 && pwmLevel1<255)
    {
      pwmLevel1 = 255;
      gUpdateValue(&pwmLevel1);
      return;
    }
  }
  //if(!autoMode)
  //{
	 //if(fan1 == 1)
	 //{
		 //pwmLevel1 = 255;
		 //gUpdateValue(&pwmLevel1);
	 //}
	 //if(fan1 == 0)
	 //{
		 //pwmLevel1 = 0;
		 //gUpdateValue(&pwmLevel1);
	 //}
	 //if(fan2 == 1)
	 //{
		 //pwmLevel2 = 255;
		 //gUpdateValue(&pwmLevel2);
	 //}
	 //if(fan2 == 0)
	 //{
		 //pwmLevel2 = 0;
		 //gUpdateValue(&pwmLevel2);
	//}
	//if(fan3 == 1)
	//{
		//pwmLevel3 = 255;
	 //gUpdateValue(&pwmLevel3);
	//}
	//if(fan3 == 0)
	//{
		//pwmLevel3 = 0;
		//gUpdateValue(&pwmLevel3);
	//}
	//if(fan4 == 1)
	//{
		//pwmLevel4 = 255;
		//gUpdateValue(&pwmLevel4);
	//}
	//if(fan4 == 0)
	//{
		//pwmLevel4 = 0;
		//gUpdateValue(&pwmLevel4);
	//}
	//if(fan5 == 1)
	//{
		//pwmLevel5 = 255;
		//gUpdateValue(&pwmLevel5);
	//}
	//if(fan5 == 0)
	//{
		//pwmLevel5 = 0;
		//gUpdateValue(&pwmLevel5);
	//}
	//if(fan6 == 1)
	//{
		//pwmLevel6 = 255;
		//gUpdateValue(&pwmLevel6);
	//}
	//if(fan6 == 0)
	//{
		//pwmLevel6 = 0;
		//gUpdateValue(&pwmLevel6);
	//}
	//if(fan7 == 1)
	//{
		//pwmLevel7 = 255;
		//gUpdateValue(&pwmLevel7);
	//}
	//if(fan7 == 0)
	//{
		//pwmLevel7 = 0;
		//gUpdateValue(&pwmLevel7);
	//}
	//if(fan8 == 1)
	//{
		//pwmLevel8 = 255;
		//gUpdateValue(&pwmLevel8);
	//}
	//if(fan8 == 0)
	//{
		//pwmLevel8 = 0;
		//gUpdateValue(&pwmLevel8);
	//}
		 
	 
  //}
  
  //if(closeLogStatus)
  //{
	  //dataLogClose();
	  //return;
  //}
  //if(dataLogging)
  //{
	  //usbWrite();
	  //return;
  //}

  
  delay(200);

}
// This is where you setup your interface
void gInit()
{
  gAddLabel("BUTTONS", 1);

  gAddSlider(0, 255, "N1", &pwmLevel1);

  gAddSlider(0, 255, "N2", &pwmLevel2);

  gAddSlider(0, 255, "N3", &pwmLevel3);

  gAddSlider(0, 255, "N4", &pwmLevel4);

  gAddSlider(0, 255, "S1", &pwmLevel5);

  gAddSlider(0, 255, "S2", &pwmLevel6);

  gAddSlider(0, 255, "S3", &pwmLevel7);

  gAddSlider(0, 255, "S4", &pwmLevel8);
  

  // The rotary sliders
  gAddLabel("GUI COLOR", 1);
  gAddSpacer(1);

  rotaryRID = gAddRotarySlider(0, 255, "R", &r);
  rotaryGID = gAddRotarySlider(0, 255, "G", &g);
  rotaryBID = gAddRotarySlider(0, 255, "B", &b);

  gAddToggle("PAUSE", &pause);
  gAddSpacer(1);
  
  //ON/OFF buttons
  
  onButton = gAddButton("FANS ON");
  offButton = gAddButton("FANS OFF");
  gAddToggle("FAN 1" , &fan1);
  gAddToggle("FAN 2" , &fan2);
  gAddToggle("FAN 3" , &fan3);
  gAddToggle("FAN 4" , &fan4);
  gAddToggle("FAN 5" , &fan5);
  gAddToggle("FAN 6" , &fan6);
  gAddToggle("FAN 7" , &fan7);
  gAddToggle("FAN 8" , &fan8);
  
  gAddColumn();

  // LOG BUTTONS


  createLog = gAddButton("SETUP DATA LOG");
  saveLog = gAddButton("SAVE DATA LOG");
  statusLabel = gAddLabel("STATUS: NOT SETUP", 1);

  gAddSpacer(1);

  gAddToggle("AUTO", &autoMode);
  gAddColumn();

  gAddLabel("GRAPHS", 1);
  gAddSpacer(1);


  // AUTO MODE BUTTON

  // Last parameter in moving graph defines the size 10 = normal
  gAddMovingGraph("Temperature 1", 0, 120, &temp1, 10);
  gAddSlider(5, 120, "VALUE", &temp1);
  gAddSpacer(1);

  gAddMovingGraph("Temperature 2", 0, 120, &temp2, 10);
  gAddSlider(5, 120, "VALUE", &temp2);
  gAddSpacer(1);

  gAddMovingGraph("Temperature 3", 0, 120, &temp3, 10);
  gAddSlider(5, 120, "VALUE", &temp3);
  gAddSpacer(1);
  
  gAddMovingGraph("Temperature 4", 0, 120, &temp4, 10);
  gAddSlider(0, 120, "VALUE", &temp4);
  gAddSpacer(1);


  gAddColumn();
  // Add more stuff here.
  gAddSpacer(1);
  gAddSpacer(1);
  gAddSpacer(1);

  gAddMovingGraph("Temperature 5", 0, 120, &temp5, 10);
  gAddSlider(0, 120, "VALUE", &temp5);
  gAddSpacer(1);

  gAddMovingGraph("Temperature 6", 0, 120, &temp6, 10);
  gAddSlider(0, 120, "VALUE", &temp6);
  gAddSpacer(1);

  gAddMovingGraph("Temperature 7", 0, 120, &temp7, 10);
  gAddSlider(0, 120, "VALUE", &temp7);
  gAddSpacer(1);
  
  gAddMovingGraph("Temperature 8", 0, 120, &temp8, 10);
  gAddSlider(0, 120, "VALUE", &temp8);
  gAddSpacer(1);
  
  gAddColumn();
  
  gAddSpacer(1);
  gAddSpacer(1);
  gAddSpacer(1);
  
  gAddMovingGraph("Temperature 9", 0, 120, &temp9, 10);
  gAddSlider(0, 120, "VALUE", &temp9);
  gAddSpacer(1);
  
  gAddMovingGraph("Temperature 10", 0, 120, &temp10, 10);
  gAddSlider(0, 120, "VALUE", &temp10);
  gAddSpacer(1);
  

  gSetColor(r, g, b); // Set the color of the Gui interface.
}

// Method called every time a button has been pressed in the interface.
void gButtonPressed(int id)
{
  //if (createLog == id)
  //{
      //dataLoggerSetup();
      //return;
  //}
//
  //if (saveLog == id)
  //{
    //closeLogStatus = 1;
    //gUpdateValue(&closeLogStatus);
    //return;
  //}
  if (onButton == id)
  {
	  autoMode = 0;
	  gUpdateValue(&autoMode);
	  pwmLevel1 = pwmLevel2 = pwmLevel3 = pwmLevel4 = pwmLevel5 = pwmLevel6 = pwmLevel7 = pwmLevel8 = 255;
	  gUpdateValue(&pwmLevel1);gUpdateValue(&pwmLevel2);gUpdateValue(&pwmLevel3);gUpdateValue(&pwmLevel4);gUpdateValue(&pwmLevel5);gUpdateValue(&pwmLevel6);gUpdateValue(&pwmLevel7);gUpdateValue(&pwmLevel8);
	  fan1=fan2=fan3=fan4=fan5=fan6=fan7=fan8=1;
	  gUpdateValue(&fan1);gUpdateValue(&fan2);gUpdateValue(&fan3);gUpdateValue(&fan4);gUpdateValue(&fan5);gUpdateValue(&fan6);gUpdateValue(&fan7);gUpdateValue(&fan8);
	  return;
	  
  }
  if (offButton == id)
  {
	  autoMode = 0;
	  gUpdateValue(&autoMode);
	  pwmLevel1 = pwmLevel2 = pwmLevel3 = pwmLevel4 = pwmLevel5 = pwmLevel6 = pwmLevel7 = pwmLevel8 = 0;
	  gUpdateValue(&pwmLevel1);gUpdateValue(&pwmLevel2);gUpdateValue(&pwmLevel3);gUpdateValue(&pwmLevel4);gUpdateValue(&pwmLevel5);gUpdateValue(&pwmLevel6);gUpdateValue(&pwmLevel7);gUpdateValue(&pwmLevel8);
	  fan1=fan2=fan3=fan4=fan5=fan6=fan7=fan8=0;
	  gUpdateValue(&fan1);gUpdateValue(&fan2);gUpdateValue(&fan3);gUpdateValue(&fan4);gUpdateValue(&fan5);gUpdateValue(&fan6);gUpdateValue(&fan7);gUpdateValue(&fan8);
	  return;
  }

}

void gItemUpdated(int id)
{
  if (rotaryRID == id || rotaryGID == id || rotaryBID == id)
  {
    gSetColor(r, g, b);
	return;
  }
}

//void dataLoggerSetup()
//{
//
  //dataLogging = 1;
  //gUpdateValue(&dataLogging);
  //gUpdateLabel(statusLabel, "DATA LOG CREATED");
  //return ;
//}

//void dataLogClose()
//{
//return;
//}
//void usbWrite()
//{
	//return;
//}













