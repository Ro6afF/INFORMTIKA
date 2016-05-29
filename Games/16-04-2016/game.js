// Creating variables
endlessCanvas = true;
var myX = 0, myY = 0, myZ = 9;
var dX = random(-10, 10), dY = random(-10, 10), dZ = random(-1, 1);
var hX = 0, hY = 0, hZ = 1;
var bum = false;

function random(min, max) {
    return Math.random() * (max - min + 1) + min;
}

function bounce() {
    if(myX <= -400 || myX >= 400 ) {
        dX *= -1;
    } else if(myY <= -300 || myY >= 300) {
        dY *= -1;
    } else if (myZ <= 1 || myZ >= 10) {
        if ( Math.sqrt((myX - hX) * (myX - hX) + (myY - hY) * (myY - hY)) <= 60 || myZ >= 10) {
            dZ *= -1;
            bum = true;
        }
    }
}

function update() {
    bounce();
    myX += dX;
    myY += dY;
    myZ += dZ;
    hX = mouseX - 400;
    hY = mouseY - 300;
    if(myZ <= 0 && bum) {
        alert("LOOSER");
        location.reload();
    }
}

function draw() {
    context.beginPath();
    context.arc(myX + 400, myY + 300, 30/myZ, 0, 2*Math.PI);
    context.fillStyle = "#0000ff";
    context.fill();
    context.beginPath();
    context.arc(hX + 400, hY + 300, 30/hZ, 0, 2*Math.PI);
    context.globalAlpha = 0.5;
    context.fillStyle = "#ff0000";
    context.fill();
};

function keyup(key) {
    // Show the pressed keycode in the console
    console.log("Pressed", key);
};

function mouseup() {
    // Show coordinates of mouse on click
    console.log("Mouse clicked at", mouseX, mouseY);
};
