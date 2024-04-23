 
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
  
  /*const LEDonButton = createButton('LED ON');  // FOR TESTING ONLY
  LEDonButton.mousePressed(LEDon);
  LEDonButton.position(15, 15);
  
  const LEDoffButton = createButton('LED OFF'); // FOR TESTING ONLY
  LEDoffButton.mousePressed(LEDoff);
  LEDoffButton.position(LEDonButton.x+LEDonButton.width+10, 15);*/
  
  let connectbtn = createButton(`Connect`);
  connectbtn.position(width / 2 - 90, 170);
  connectbtn.size(200, 40);
  connectbtn.style('font-size', '18px');
  connectbtn.mousePressed(connectToBle);
  
  let btn = createButton(`The Brad`);
  btn.position(width / 2 - 90, 185 + 1 * 50);
  btn.size(200, 40);
  btn.style('font-size', '18px');
  btn.mousePressed(Drink1)
  
  let btn2 = createButton(`The Alanna`);
  btn2.position(width / 2 - 90, 185 + 2 * 50);
  btn2.size(200, 40);
  btn2.style('font-size', '18px');
  btn2.mousePressed(Drink2)
  
  let btn3 = createButton(`The Chur`);
  btn3.position(width / 2 - 90, 185 + 3 * 50);
  btn3.size(200, 40);
  btn3.style('font-size', '18px');
  btn3.mousePressed(Drink3)
  
  let btn4 = createButton(`The Jason`);
  btn4.position(width / 2 - 90, 185 + 4 * 50);
  btn4.size(200, 40);
  btn4.style('font-size', '18px');
  btn4.mousePressed(Drink4)
  
  let btn5 = createButton(`The Cedar Rose`);
  btn5.position(width / 2 - 90, 185 + 5 * 50);
  btn5.size(200, 40);
  btn5.style('font-size', '18px');
  btn5.mousePressed(Drink5)
  
  let btn6 = createButton(`The Pooja`);
  btn6.position(width / 2 - 90, 185 + 6 * 50);
  btn6.size(200, 40);
  btn6.style('font-size', '18px');
  btn6.mousePressed(Drink6)
  
  let btn7 = createButton(`The Anoushka`);
  btn7.position(width / 2 - 90, 185 + 7 * 50);
  btn7.size(200, 40);
  btn7.style('font-size', '18px');
  btn7.mousePressed(Drink7)

  
  /*for (let i = 1; i < 3; i++) {
    let btn;
    if (i==1) {
      let btn = createButton(`The Brad`);
    } else if (i==2) {
      let btn = createButton(`The Alanna`);
    }
    //let btn = createButton(`The Brad`);  
    btn.position(width / 2 - 50, 185 + i * 50);
    btn.size(100, 40);
    btn.style('font-size', '18px');
    btn.mousePressed(Drink1)
    //btn.mousePressed(() => selectDrink(i + 1));
  }*/
  
  /*function selectDrink(drinkNumber) {
    preparingDrinkText.html(`Preparing Drink ${drinkNumber-1}`);
    preparingDrinkText.show(); 
  }*/
}


function draw() {
  drawScreen();
}
