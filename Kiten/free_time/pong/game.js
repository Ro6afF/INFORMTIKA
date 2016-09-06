let canvas = document.getElementById("canvas-id");
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;
let context = canvas.getContext('2d');

let tX = Math.floor(Math.random() * (canvas.width - 200)) + 100, tY = Math.floor(Math.random() * canvas.height - 100);
let dtX = 2, dtY = 2;
let pY = 0;
let py = 0;
let keys = [];

window.addEventListener("keydown", function (args) {
			keys[args.keyCode] = true;
			console.log(args.keyCode);
		}, false);

window.addEventListener("keyup", function (args) {
			keys[args.keyCode] = false;
		}, false);

function areColliding(Ax, Ay, Awidth, Aheight, Bx, By, Bwidth, Bheight) {
	if (Bx <= Ax + Awidth) {
		if (Ax <= Bx + Bwidth) {
			if (By <= Ay + Aheight) {
				if (Ay <= By + Bheight) {
					return 1;
				}
			}
		}
	}
	return 0;
};


function update() {
	if(keys[38])
	{
		py -=2;
	}
	if(keys[40])
	{
		py+=2;
	}
	if(keys[87])
	{
		pY -=2;
	}
	if(keys[83])
	{
		pY+=2;
	}
	if(pY <0)
	{
		pY = 0;
	}
	if(py <0)
	{
		py = 0;
	}
	if(pY+100 > canvas.height)
	{
		pY = canvas.height - 100;
	}
	if(py+100 > canvas.height)
	{
		py = canvas.height - 100;
	}
	tX += dtX;
	tY += dtY;
	if(tY + 30 >= canvas.height || tY <= 0)
	{
		dtY *= -1;
	}
	if(areColliding(canvas.width - 50, py, 50, 100, tX, tY, 30, 30) || areColliding(0, pY, 50, 100, tX, tY, 30, 30))
	{
		dtX *= -1;
	}
	if(tX + 30 < 0 || tX > canvas.width)
	{
		tX = Math.floor(Math.random() * (canvas.width - 200)) + 100, tY = Math.floor(Math.random() * canvas.height + 100);
	}
}

function draw() {
	context.clearRect(0, 0, canvas.width, canvas.height);
	context.fillStyle = '#00ff00';
	context.fillRect(tX, tY, 30, 30);
	context.fillStyle = '#0000ff';
	context.fillRect(0, pY, 50, 100);
	context.fillStyle = '#ff0000';
	context.fillRect(canvas.width - 50, py, 50, 100);
}

let upd = setInterval(update, 1);
let drw = setInterval(draw, 1);
