 
 //globals
let blueToothCharacteristic;
let receivedValue = "";

let blueTooth;
let isConnected = false;

function setup() {

  createCanvas(windowWidth, windowHeight);
  
  console.log("setting up");
  blueTooth = new p5ble();
  
  titleText = createP('');
  titleText.position(windowWidth/2-121, 20);
  titleText.style('color', '#FFF'); 
  titleText.style('font-size', '36px');
  titleText.style('font-weight', 'bold');
  titleText.html(`SMARTENDER`);
  titleText.show(); 
  
  preparingDrinkText = createP('');
  preparingDrinkText.position(width / 2 - 85, 85);
  preparingDrinkText.style('color', '#FFF');
  preparingDrinkText.style('font-size', '24px');
  preparingDrinkText.hide(); // Hide initially
  
  const LEDonButton = createButton('LED ON');  // FOR TESTING ONLY
  LEDonButton.mousePressed(LEDon);
  LEDonButton.position(15, 15);
  
  const LEDoffButton = createButton('LED OFF'); // FOR TESTING ONLY
  LEDoffButton.mousePressed(LEDoff);
  LEDoffButton.position(LEDonButton.x+LEDonButton.width+10, 15);
  
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
    btn.mousePressed(Drink1)
    //btn.mousePressed(() => selectDrink(i + 1));
  }
  
  function selectDrink(drinkNumber) {
    preparingDrinkText.html(`Preparing Drink ${drinkNumber-1}`);
    preparingDrinkText.show(); 
  }
}


function draw() {
  drawScreen();
}
