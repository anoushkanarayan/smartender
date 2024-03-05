/*  
 * Bluetooth Test - Processing Side (In Chrome)
 * Arduino to HM10 module to Google Chrome
 * https://www.amazon.com/gp/product/B06WGZB2N4/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1
 * 
 * p5.ble.js
 https://yining1023.github.io/p5ble-website/
 
 * kevin darrah
 * 
 * Twitter: https://twitter.com/KDcircuits
 * For inquiries or design services:
 * https://www.kdcircuits.com
 * 
 * License?  Do whatever you want with this code - it's just a sample
 */
 
 //globals
let blueToothCharacteristic;//this is a blu
let receivedValue = "";

let blueTooth;
let isConnected = false;
let preparingDrinkText;
let titleText;


var millisecondTimerStart;
//var oldColorPickerValue;


function setup() {

  createCanvas(windowWidth, windowHeight);
  
  // Create a p5ble class
  console.log("setting up");
  blueTooth = new p5ble();
  
  titleText = createP(''); // This paragraph will show the "preparing drink" text
  titleText.position(windowWidth/2-121, 20);
  titleText.style('color', '#FFF'); // White text color
  titleText.style('font-size', '36px');
  titleText.style('font-weight', 'bold'); // Make the text bold
  titleText.html(`SMARTENDER`); // Update the text
  titleText.show(); 
  
  preparingDrinkText = createP(''); // This paragraph will show the "preparing drink" text
  preparingDrinkText.position(width / 2 - 85, 85);
  preparingDrinkText.style('color', '#FFF'); // Black text color
  preparingDrinkText.style('font-size', '24px');
  preparingDrinkText.hide(); // Hide initially

  /*const connectButton = createButton('Connect');
  connectButton.mousePressed(connectToBle);
  connectButton.position(15, 15);*/

  const LEDonButton = createButton('LED ON');
  LEDonButton.mousePressed(LEDon);
  LEDonButton.position(15, 15);

  const LEDoffButton = createButton('LED OFF');
  LEDoffButton.mousePressed(LEDoff);
  LEDoffButton.position(LEDonButton.x+LEDonButton.width+10, 15);

  /*ledColorPicker = createColorPicker('#ff0000');
  ledColorPicker.position(LEDoffButton.x+LEDoffButton.width+10, 60);
  millisecondTimerStart = millis();*/
  
  let connectbtn = createButton(`Connect`);
  connectbtn.position(width / 2 - 50, 170);
  connectbtn.size(100, 40);
  connectbtn.style('font-size', '18px');
  connectbtn.mousePressed(connectToBle);
  
 for (let i = 1; i < 11; i++) {
    let btn = createButton(`Drink ${i}`);
    btn.position(width / 2 - 50, 185 + i * 50);
    btn.size(100, 40);
    btn.style('font-size', '18px');
    btn.mousePressed(() => selectDrink(i + 1));
  }
  
  function selectDrink(drinkNumber) {
    preparingDrinkText.html(`Preparing Drink ${drinkNumber}`); // Update the text
    preparingDrinkText.show(); 
  }
}


function draw() {
  drawScreen();
}
