function drawScreen() {
  textSize(18);
  if (isConnected) {
    //background(0, 255, 0);
    //text('  Connected :)', 180, 15);
  } else {
    background(130, 92, 180);
    textAlign(LEFT, TOP);
    //text('Disconnected :/', 80, 15);
  }

  text(receivedValue, 15, 40);

  
}
