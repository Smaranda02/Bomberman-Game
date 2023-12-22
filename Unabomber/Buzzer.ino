void playMelody(Sound melody[], int length) {

  if (melodyIndex == length) {
    songEnded = true;
    melodyIndex = 0;
  }

  else {
    if (melody[melodyIndex].lastCount == 0) {
      melody[melodyIndex].lastCount = millis();
    }

    if (millis() - melody[melodyIndex].lastCount >= melody[melodyIndex].duration) {
      melody[melodyIndex].lastCount = 0;
      melodyIndex++;
    } else {
      tone(buzzerPin, melody[melodyIndex].pitch, melody[melodyIndex].duration);
    }
  }
}



void menuInteractionSound() {
  if (EEPROM.read(soundMemoryLocation)) {
    tone(buzzerPin, menuInteractionTone, menuInteractionDuration);
  }
}
