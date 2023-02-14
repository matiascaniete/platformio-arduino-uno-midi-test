#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const char *notenames[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

void printChannel(int inChannel)
{
  Serial.print("[");
  Serial.print(inChannel);
  Serial.print("] ");
}

void printNoteName(int note)
{
  int octave = note / 12;
  int nnumber = note % 12;
  Serial.print(notenames[nnumber]);
  Serial.print(octave - 2);
}

void handleNoteOn(byte inChannel, byte inNumber, byte inVelocity)
{
  printChannel(inChannel);
  printNoteName(inNumber);
  Serial.print(" NoteOn  ");
  Serial.print(inNumber);
  Serial.print("\tvelocity: ");
  Serial.println(inVelocity);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void handleNoteOff(byte inChannel, byte inNumber, byte inVelocity)
{
  printChannel(inChannel);
  printNoteName(inNumber);
  Serial.print(" NoteOff ");
  Serial.print(inNumber);
  Serial.print("\tvelocity: ");
  Serial.println(inVelocity);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  pinMode(LED_BUILTIN, OUTPUT);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.println("Arduino Ready");
}

void loop()
{
  MIDI.read();
}