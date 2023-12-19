void displayAlphabet() {
  if (!shown) {
    lcd.clear();
    shown = true;
  } 

    lcd.setCursor(0, 0);
    lcd.print(alphabet1);
    lcd.setCursor(0, 1);
    lcd.print(alphabet2);
}


void setBrightness(byte value) {
  value = map(value, minLcdBrightness, maxLcdBrightness, minMappedValue, maxMappedValue);
  analogWrite(backLightPin, value);
  EEPROM.update(lcdBrightnessMemoryLocation, value);
}
