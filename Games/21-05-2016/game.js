var requestAnimationFrame = window.webkitRequestAnimationFrame ||
                window.mozRequestAnimationFrame ||
                window.msRequestAnimationFrame ||
                window.oRequestAnimationFrame ||
                window.requestAnimationFrame ||
                function (callback) { setTimeout(callback, 33); };

var canvas = document.getElementById("canvas-id");

function qm() {
    n = ((canvas.width + canvas.height) / 2) / 30;
    for (var i = 0; i < n; i++) {
        ne6ta[i] = {
            X: Math.floor(Math.random() * canvas.width - 15),
            Y: Math.floor(Math.random() * canvas.height - 15),
            color: "#0f0",
            zeto: false,
            r: 15,
            ang: 2 * Math.PI,
            kadur: 0
        }
    }
}

canvas.width = window.innerWidth - 4;
canvas.height = window.innerHeight - 4;
window.onresize = function () {
    canvas.width = window.innerWidth - 4;
    canvas.height = window.innerHeight - 4;
    qm();
}

var context = canvas.getContext("2d");

var ne6ta = [];
var n;
qm();

window.addEventListener("mousemove", function (args) {
    var X = args.clientX - canvas.offsetLeft;
    var Y = args.clientY - canvas.offsetTop;
    var w, h;
    for (var i = 0; i < n; i++) {
        w = Math.abs(X - ne6ta[i].X);
        h = Math.abs(Y - ne6ta[i].Y);
        if (Math.sqrt(w * w + h * h) <= 15) {
            ne6ta[i].zeto = true;
        }
    }
}, false);

function invertColor(hexTripletColor) {
    var color = hexTripletColor;
    color = color.substring(1);           
    color = parseInt(color, 16);          
    color = 0xFFFFFF ^ color;             
    color = color.toString(16);           
    color = ("000000" + color).slice(-6); 
    color = "#" + color;                  
    return color;
}

function update() {
    for (var i = 0; i < n; i++) {
        if (ne6ta[i].zeto) {
            if (ne6ta[i].r > 0.1) {
                if (ne6ta[i].kadur >= 1000) {
                    ne6ta[i].r -= 0.1;
                }
                else {
                    var oX = (1 - Math.random() * 2) * 25, oY = (1 - Math.random() * 2) * 25;
                    while (ne6ta[i].X + oX < 0 || ne6ta[i].X + oX > canvas.width) {
                        oX = (1 - Math.random() * 2) * 25;
                    }
                    while (ne6ta[i].Y + oY < 0 || ne6ta[i].Y + oY > canvas.height) {
                        oY = (1 - Math.random() * 2) * 25;
                    }
                    ne6ta[i].X += oX;
                    ne6ta[i].Y += oY;
                    for (var j = 0; j < ne6ta.length; j++) {
                        if (i != j) {
                            if (Math.sqrt((ne6ta[i].X - ne6ta[j].X) * (ne6ta[i].X - ne6ta[j].X) + (ne6ta[i].Y - ne6ta[j].Y) * (ne6ta[i].Y - ne6ta[j].Y)) <= ne6ta[i].r + ne6ta[j].r) {
                                ne6ta[j].zeto = true;
                            }
                        }
                    }
                }
                ne6ta[i].kadur++;
            }
        }
    }
}

function draw() {
    context.globalAlpha = 1;
    context.fillStyle = "#000";
    context.fillRect(0, 0, canvas.width, canvas.height);
    for (var i = 0; i < n; i++) {
        context.fillStyle = "#0f0";
        if (ne6ta[i].zeto && ne6ta[i].kadur % 7 == 0) {
            context.fillStyle = invertColor(context.fillStyle);
        }
        context.beginPath();
        context.arc(ne6ta[i].X, ne6ta[i].Y, ne6ta[i].r, 0, ne6ta[i].ang);
        context.fill();
    }
    requestAnimationFrame(draw);
}

var upd = setInterval(update, 1);
draw();
