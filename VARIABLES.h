// RYTHM, the simple drum box
//
// All in the spirit of open-source and open-hardware
// by Jorge Gutiérrez
//
// NANO
//
// 2017 Spain
//
// VARIABLES 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define      sound1  4
#define      sound2  5
#define      sound3  6
#define      sound4  7

#define startButton  8
#define resetButton  9

#define  tempoLed    2
#define recordLed    1

#define  speakerPin  3

#define       tempo A0

uint16_t SAMPLE_RATE    =  8000;


unsigned char const *sounddata_data=0;
int sounddata_length=0;
volatile uint16_t sample;
byte lastSample;

bool stateBeat = false;
bool prevStateBeat = false;
bool beatRun = true;

int8_t patternBeat;
uint16_t countBeat;

bool setBeat = false;
bool beatOK = false;
bool beatOn = false;
bool selectBeat1 = false;
bool selectBeat2 = false;
bool selectBeat3 = false;
bool selectBeat4 = false;
bool selectBeat5 = false;
bool selectBeat6 = false;
bool selectBeat7 = false;
bool selectBeat8 = false;

bool beatstep1 = false;
bool beatstep2 = false;
bool beatstep3 = false;
bool beatstep4 = false;
bool beatstep5 = false;
bool beatstep6 = false;
bool beatstep7 = false;
bool beatstep8 = false;

unsigned char *beat1, *beat2, *beat3, *beat4, *beat5, *beat6, *beat7, *beat8;
uint16_t beatLength1, beatLength2, beatLength3, beatLength4, beatLength5, beatLength6, beatLength7, beatLength8;

unsigned char const static kick[] PROGMEM =
{
  128,129,129,129,129,130,130,131,132,132,137,132,126,100,140,249,79,164,144,144,113,142,125,114,123,73,116,66,83,55,79,59,67,60,70,63,72,66,86,94,101,116,107,136,182,141,158,223,186,199,207,227,237,239,239,240,235,223,198,196,188,183,171,168,156,150,141,132,124,120,105,100,89,75,71,70,56,46,44,33,29,29,28,25,22,23,22,23,25,28,32,39,48,51,57,66,
  71,79,87,97,105,112,119,128,134,141,151,156,168,168,188,181,201,196,227,221,238,235,234,238,238,235,234,229,224,212,207,193,188,184,177,170,165,158,151,142,137,128,121,113,108,102,95,88,84,77,75,67,65,57,56,49,49,44,43,42,34,36,32,35,37,36,33,40,38,43,42,48,48,52,54,55,63,69,70,74,80,84,89,92,98,104,107,111,115,119,120,129,123,134,137,140,144,144,147,150,
  154,152,155,158,157,162,158,159,162,161,160,160,162,162,161,162,163,164,163,168,167,169,169,173,171,174,171,176,176,177,175,179,176,175,174,173,172,172,166,166,162,158,156,152,148,143,140,134,131,125,121,117,113,108,104,100,95,91,87,82,80,74,72,67,64,60,55,54,51,49,46,42,44,43,43,41,42,43,45,46,48,49,51,55,58,61,66,72,76,81,86,92,100,104,112,116,123,128,135,140,
  145,150,155,160,163,168,171,176,178,180,182,185,187,188,189,190,188,190,189,188,186,188,183,184,180,179,175,174,169,168,165,160,158,155,151,148,145,142,138,135,132,129,126,124,121,118,116,114,112,110,109,106,106,104,104,103,103,102,102,102,102,103,103,104,105,105,106,106,108,109,111,112,113,114,115,116,118,119,121,121,123,124,125,126,127,128,129,130,131,132,132,133,133,134,134,134,135,134,134,134,
  134,134,133,133,133,132,132,132,131,131,130,130,130,129,129,128,128,128,128,128,127,127,127,127,127,127,127,127,127,127,127,128,128,128,128,129,129,130,130,130,131,131,132,132,133,133,134,134,135,135,135,136,136,136,136,136,136,136,136,136,136,136,136,136,136,135,135,135,135,134,134,134,134,134,134,133,133,133,133,133,133,133,133,133,133,133,132,132,132,132,132,132,132,132,131,131,131,131,131,131,
  130,130,130,130,130,130,129,129,129,129,129,129,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,129,129,129,129,129,130,130,130,130,131,131,131,131,131,132,132,132,132,132,132,133,133,133,133,133,133,133,133,133,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,134,133,133,133,133,133,133,133,133,133,132,132,132,132,
  132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,
  131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,132,132,132,132,132,132,132,132,132,132,132,132,132,132,132,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,130,130,130,130,130,130,130,130,130,131,131,131,131,131,130,130,130,130,130,130,130,130,130,130,130,130,130,130,129,
  129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,128,128,128,128,128,128,128,128,128,128,128,128,128
};

uint16_t kick_length = 832;


unsigned char const static tick[] PROGMEM =

{
  127, 128, 127, 126, 125, 124, 124, 123, 124, 126, 129, 132, 134, 134, 134, 137, 140, 139, 136, 139, 143, 141, 132, 121, 110, 105, 107, 107, 106, 112, 114, 106, 105, 109, 96, 91, 110, 129, 145, 159, 170, 168, 154, 157, 161, 155, 160, 170, 177, 184, 184, 177, 154, 112, 78, 64, 69, 84, 84, 79, 75, 69, 66, 67, 64, 45, 44, 85, 150, 186, 179, 182, 205, 212, 199, 197, 207, 206, 198, 209, 210, 187, 163, 116, 62, 43, 59, 80, 70, 49, 61, 64, 53, 60, 61, 60, 84, 131, 167, 200, 213, 196, 190, 205, 226, 237, 243, 213, 183, 192, 184, 178, 132, 68, 59, 42, 28, 50, 70, 41, 0, 27, 63, 38, 16, 48, 79, 98, 137, 179, 199, 198, 201, 208, 199, 203, 210, 204, 207, 202, 192, 174, 139, 122, 118, 91, 61, 71, 89, 74, 61, 77, 79, 61, 60, 89, 120, 120, 132, 167, 184, 170, 179, 219, 198, 162, 174, 183, 194, 184, 133, 128, 153, 126, 93, 101, 67, 18, 50, 66, 25, 23, 80, 69, 54, 100, 91, 113, 144, 124, 125, 155, 190, 198, 192, 198, 202, 192, 187, 189, 178, 165, 144, 148, 170, 139, 88, 91, 113, 97, 89, 84, 82, 104, 95, 80, 102, 121, 117, 118, 136, 155, 158, 163, 166, 158, 150, 165, 168, 133, 136, 129, 103, 112, 114, 107, 85, 60, 82, 107, 78, 63, 92, 90, 90, 121, 133, 102, 105, 174, 171, 146, 172, 179, 178, 159, 163, 199, 169, 136, 171, 183, 145, 136, 143, 126, 114, 106, 103, 117, 116, 105, 98, 82, 100, 99, 97, 126, 119, 97, 122, 161, 117, 97, 128, 144, 145, 133, 134, 130, 128, 133, 125, 117, 124, 122, 123, 122, 109, 107, 114, 112, 103, 108, 120, 120, 107, 134, 143, 111, 139, 155, 136, 151, 163, 151, 159, 192, 168, 123, 157, 188, 160, 90, 120, 208, 131, 54, 98, 131, 99, 101, 106, 64, 88, 133, 108, 87, 113, 121, 101, 104, 146, 138, 92, 123, 173, 133, 122, 158, 123, 134, 151, 113, 116, 119, 121, 122, 113, 122, 123, 115, 118, 135, 127, 94, 117, 156, 147, 141, 134, 110, 178, 223, 120, 101, 165, 162, 143, 129, 122, 123, 123, 120, 146, 155, 89, 75, 123, 137, 94, 96, 130, 109, 125, 99, 100, 156, 110, 92, 144, 161, 117, 86, 119, 154, 131, 113, 132, 131, 117, 135, 138, 124, 118, 136, 154, 137, 149, 105, 88, 157, 146, 107, 123, 146, 125, 135, 150, 123, 133, 154, 120, 96, 138, 149, 119, 120, 136, 140, 133, 112, 118, 156, 140, 99, 121, 158, 115, 80, 145, 140, 89, 120, 146, 128, 101, 108, 142, 134, 111, 124, 141, 134, 123, 123, 132, 140, 122, 119, 153, 148, 122, 120, 127, 139, 129, 115, 123, 125, 137, 140, 120, 120, 138, 134, 107, 125, 143, 118, 123, 138, 124, 129, 162, 131, 97, 123, 135, 133, 128, 133, 130, 109, 115, 138, 131, 120, 130, 131, 128, 123, 124, 133, 136, 115, 116, 146, 140, 126, 114, 120, 145, 133, 119, 127, 124, 126, 140, 138, 120, 114, 132, 140, 124, 123, 132, 134, 129, 119, 127, 133, 122, 120, 131, 128, 114, 124, 138, 127, 111, 128, 139, 115, 116, 147, 134, 107, 132, 144, 127, 123, 138, 130, 130, 143, 122, 130, 140, 124, 120, 129, 130, 122, 126, 126, 123, 124, 129, 129, 118, 123, 138, 133, 121, 123, 136, 133, 130, 131, 121, 131, 130, 124, 134, 127, 121, 126, 130, 120, 119, 128, 123, 123, 126, 125, 125, 129, 128, 124, 132, 125, 122, 136, 130, 128, 132, 130, 133, 132, 127, 129, 136, 134, 126, 122, 127, 131, 126, 127, 128, 125, 125, 127, 130, 122, 128, 139, 126, 120, 127, 129, 130, 133, 128, 119, 125, 129, 126, 126, 130, 125, 122, 128, 125, 122, 128, 129, 125, 129, 129, 124, 129, 127, 127, 128, 123, 125, 130, 129, 128, 128, 129, 129, 128, 129, 132, 131, 126, 130, 131, 126, 131, 131, 127, 127, 129, 128, 129, 129, 125, 127, 129, 127, 126, 127, 126, 126, 129, 128, 125, 124, 126, 129, 126, 125, 128, 127, 127, 128, 127, 127, 128, 128, 127, 127, 128, 128, 125, 127, 128, 127, 127, 128, 127, 126, 130, 128, 127, 128, 129, 128, 128, 129, 127, 128, 128, 128, 131, 128, 126, 128, 130, 128, 127, 128, 128, 128, 128, 128, 127, 126, 127, 128, 126, 127, 127, 126, 127, 127, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 127, 128, 128, 128, 127, 127, 128, 128, 127, 128, 128, 127, 128, 128, 128, 128, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 127, 128, 127

};
uint16_t tick_length = 832;


unsigned char const static cowbell[] PROGMEM =

{
  128,129,112,108,86,114,157,124,159,206,159,121,96,93,46,41,167,172,164,178,227,178,165,116,38,8,79,124,133,148,186,255,230,163,96,39,8,18,59,85,125,241,248,243,201,128,83,4,6,38,52,92,172,243,247,229,165,76,13,8,7,29,66,142,238,247,242,194,123,48,6,11,9,33,103,164,247,244,238,160,92,49,13,9,17,58,134,216,246,241,194,139,73,35,12,12,
  29,91,163,242,237,227,162,122,79,16,13,17,67,126,175,230,236,183,157,104,72,21,19,41,95,148,178,219,212,169,150,108,52,34,40,80,110,146,172,182,185,166,127,97,60,52,71,93,127,140,166,174,176,153,117,87,76,75,90,99,125,142,159,175,154,139,114,97,88,92,96,107,118,145,156,160,148,127,118,110,104,94,97,108,126,143,153,144,143,131,126,116,104,102,98,114,129,136,143,141,
  137,140,129,120,103,103,107,116,127,129,136,142,143,140,130,118,109,105,115,116,123,128,134,144,146,139,127,116,115,113,112,116,117,130,138,145,142,135,128,120,117,115,111,114,121,131,143,142,141,130,129,125,118,113,110,116,127,134,140,140,137,136,128,125,114,112,112,120,129,136,138,139,137,136,130,120,115,111,118,123,131,134,137,140,140,134,128,117,115,116,119,126,128,136,137,141,139,131,124,118,
  116,120,121,126,129,135,141,139,137,128,123,121,121,121,123,125,132,135,138,136,131,128,125,124,122,123,123,127,132,135,134,134,129,129,127,125,124,123,126,129,131,132,132,131,130,128,128,125,125,125,127,129,130,130,130,130,130,128,127,126,126,127,128,129,129,129,130,130,129,128,127,127,127,128,128,128,129,129,129,129,129,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128
};
uint16_t cowbell_length = 394;


unsigned char const static blip[] PROGMEM =

{
  128,149,117,85,141,185,112,43,133,218,116,10,125,251,128,2,109,237,143,15,101,223,148,25,94,211,163,31,88,205,164,53,74,198,177,55,71,183,183,74,62,167,191,93,48,164,193,94,63,145,195,113,53,137,199,117,59,126,188,139,59,106,196,148,63,97,186,166,75,75,180,184,83,62,163,193,96,55,156,192,103,67,138,191,119,66,133,188,123,68,124,185,131,71,118,181,
  142,72,111,180,142,80,110,170,145,88,107,163,149,95,103,155,154,98,102,153,150,106,106,144,145,113,112,135,145,118,111,137,143,120,114,134,139,122,115,132,140,124,116,129,138,127,118,129,136,127,121,125,135,131,121,126,133,130,124,126,132,129,127,128,130,129
};
uint16_t blip_length = 162;

unsigned char const static clap[] PROGMEM =

{
  128,122,164,121,123,49,34,101,250,246,152,60,49,111,58,167,243,126,103,68,138,107,113,121,135,96,147,138,114,110,115,90,125,85,53,91,165,246,143,91,89,70,97,54,129,241,102,103,167,113,90,131,147,149,117,81,111,112,35,94,196,103,158,168,112,44,120,56,138,226,108,107,61,99,147,82,54,129,13,101,250,184,82,140,81,179,56,81,80,147,198,98,141,18,46,56,
  189,254,168,36,66,79,53,144,253,192,89,10,140,167,53,77,163,202,164,73,29,98,165,119,18,91,84,89,98,209,192,61,73,25,142,237,166,219,135,97,74,22,152,180,84,79,18,108,145,178,100,41,146,158,198,133,92,93,131,73,58,131,142,158,70,82,91,188,156,136,81,54,175,172,64,165,89,15,71,219,174,86,127,159,67,84,121,151,250,145,96,44,75,132,128,74,133,184,107,138,
  209,148,138,62,135,120,24,69,192,204,112,29,122,86,128,134,172,133,145,122,85,108,151,111,72,82,88,200,163,106,52,120,196,196,130,46,103,187,156,56,110,116,180,116,99,118,142,140,110,102,162,175,128,62,104,183,143,61,154,175,142,51,160,151,123,71,118,126,176,110,144,170,153,149,127,49,53,165,172,102,158,159,118,115,98,140,88,94,124,143,109,231,146,52,104,157,172,153,100,89,
  127,143,147,110,153,130,87,127,107,139,182,117,126,118,126,122,114,132,128,121,131,147,121,123,115,170,121,78,130,117,122,128,158,132,113,142,135,154,122,101,102,120,101,99,154,178,147,108,125,125,142,140,109,122,137,137,132,93,117,163,135,124,93,126,145,162,106,123,100,146,138,123,134,155,133,130,115,139,135,130,98,138,152,102,120,129,126,153,127,120,125,136,133,136,138,147,132,138,134,124,
  100,123,135,137,125,137,146,149,138,122,115,116,125,136,136,147,121,126,136,143,144,131,110,132,120,130,142,170,127,112,114,120,136,143,136,140,136,110,121,152,141,149,115,115,129,137,144,156,124,113,132,134,146,127,124,131,127,136,135,133,137,123,123,146,144,142,129,117,127,119,138,150,129,124,131,126,129,150,129,128,121,116,127,146,145,132,129,134,149,136,130,123,130,132,121,126,142,137,130,128,
  133,140,127,124,126,125,136,136,124,123,139,138,137,129,139,131,112,124,138,132,129,125,137,139,125,125,135,122,126,135,135,132,132,132,128,134,133,126,127,129,127,129,131,132,122,126,133,133,125,124,135,136,133,129,126,131,130,130,130,128,129,130,130,130,128,128,131,130,129,129,128,128,127,128,129,131,130,128,129,128,130,129,129,130,129,129,127,129,129,128,127,128,128,129,128,128,129,129,129,129,
  129,128,128,128,128,129,128,128,128,128,128,128,128,128
};
uint16_t clap_length = 400;

unsigned char const static hat[] PROGMEM =

{
127, 128, 225, 217, 99, 38, 61, 153, 152, 144, 133, 73, 122, 144, 65, 188, 87, 170, 164, 111, 122, 151, 114, 88, 174, 77, 140, 92, 122, 141, 156, 124, 121, 123, 126, 133, 132, 139, 119, 120, 127, 141, 130, 122, 129, 127, 132, 121, 139, 118, 130, 131, 129, 132, 130, 134, 126, 128, 130, 126, 122, 132, 129, 127, 131, 126, 128, 127, 126, 125, 127, 125, 128, 125, 128, 128, 127, 127, 126, 127, 128, 128, 128, 127, 127, 127, 127, 127, 128, 127, 127, 126, 127, 127, 128, 127, 128, 126, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 126, 126, 128, 127, 126, 127, 126, 127, 127, 126, 127, 126, 127, 127, 127, 127, 127, 126, 127, 127, 127, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 126, 126, 126, 127, 127, 127, 126, 127, 127, 127, 126, 127, 127, 126, 127, 127, 127, 127, 127, 127, 126, 126, 126, 126, 126, 126, 126, 127, 127, 126, 127, 126, 126, 127, 126, 127, 126, 126, 126, 126, 126, 126, 126, 127, 127, 126, 127, 127, 127, 127, 126, 126, 127, 127, 127, 126, 127, 126, 127, 127, 127, 127, 127, 126, 126, 127, 127, 126, 127, 127, 127, 127, 126, 127, 127, 127, 127, 127, 127, 127, 127
};
uint16_t hat_length = 256;

unsigned char const static snare[] PROGMEM = //clap
{
  128,164,168,168,163,142,145,75,24,39,25,39,51,76,78,90,103,129,149,163,194,207,213,177,181,178,194,185,231,220,227,225,210,161,150,151,133,119,110,87,75,62,49,22,20,10,35,18,16,21,19,21,31,60,66,73,87,108,117,134,155,169,234,237,255,242,238,243,240,231,222,175,182,163,147,122,104,96,87,78,58,37,13,26,20,27,18,25,18,31,44,88,111,109,114,152,
  194,171,150,194,239,213,238,232,216,225,236,208,151,164,129,125,97,100,81,81,73,48,19,44,57,22,40,22,41,28,59,49,85,72,93,120,129,134,128,151,169,184,165,170,172,175,172,157,148,142,145,175,141,137,140,122,119,112,96,99,73,50,71,29,44,41,30,28,58,60,83,95,113,103,97,110,118,131,154,160,151,150,177,163,186,187,196,208,233,195,218,164,144,144,130,128,114,89,68,93,
  68,44,73,41,30,61,47,74,95,80,108,90,134,112,139,126,137,165,161,157,176,174,173,157,150,179,171,145,158,143,149,143,104,122,106,96,89,99,108,97,75,65,103,106,93,93,125,104,114,112,105,116,132,126,162,129,106,129,137,140,130,145,128,151,134,145,175,166,174,168,169,153,145,154,148,128,130,110,111,96,100,76,89,77,75,81,89,82,101,92,113,101,125,137,144,137,160,153,147,153,
  149,149,197,182,167,159,176,161,146,147,147,131,130,128,100,114,117,100,109,82,104,90,76,73,101,97,96,107,116,128,127,148,149,141,164,155,164,152,157,156,154,148,148,152,129,154,142,136,147,132,126,140,128,131,126,118,120,116,105,120,111,112,115,109,118,111,111,106,129,112,129,127,123,125,132,127,129,140,139,131,140,136,154,142,135,146,150,151,148,152,147,138,142,144,134,129,131,128,113,113,
  117,111,108,104,98,106,99,109,101,114,123,118,142,133,133,138,144,147,137,142,154,142,142,159,138,145,150,148,139,136,133,128,118,122,125,122,120,112,115,111,115,112,99,114,109,126,125,120,125,140,136,136,144,135,133,142,146,146,146,134,145,132,133,134,131,131,127,134,127,129,124,136,132,128,140,132,131,131,128,133,129,124,127,121,130,126,125,122,124,127,128,128,124,127,130,130,129,128,127,136,
  131,139,143,142,141,138,141,145,141,141,141,139,140,131,131,126,128,123,121,125,118,117,120,117,120,117,114,121,121,130,121,132,128,131,132,140,136,140,138,145,137,138,139,138,135,134,132,128,129,125,125,125,126,123,126,120,124,120,131,124,124,128,131,132,129,130,135,132,144,136,137,134,141,136,132,133,136,136,130,128,127,129,123,132,128,126,131,129,129,128,132,130,132,134,133,131,134,132,130,134,
  134,131,133,130,134,126,129,128,132,128,129,128,122,127,129,122,128,131,129,132,134,134,135,135,136,138,137,138,139,142,139,134,135,134,133,131,133,127,124,127,126,123,123,126,120,123,127,125,127,128,129,130,133,132,139,134,137,135,134,134,135,130,132,131,131,129,128,130,126,127,124,127,126,125,128,129,127,126,128,129,131,131,134,132,133,131,134,134,135,130,134,131,131,134,131,131,130,128,129,128,
  127,128,124,126,127,128,128,129,128,132,131,133,135,132,134,138,137,136,134,134,134,134,132,130,130,131,129,129,127,127,128,128,126,129,130,128,128,129,131,131,130,131,133,133,133,134,134,131,133,132,130,130,129,130,129,128,127,128,126,126,125,127,127,126,127,128,129,129,131,130,131,131,132,131,132,131,131,130,130,130,129,129,129,128,126,128,128,127,127,127,127,127,127,128,128,128,128,128,128,129,
  129,129,130,130,130,130,130,130,130,129,129,128,128,128,128,128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128};

uint16_t snare_length = 840;

unsigned char const static voidSound[] PROGMEM =
{ 0 };

uint16_t voidSound_length = 1;

