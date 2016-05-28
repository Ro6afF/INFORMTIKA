var canvas = document.getElementById('canvas-id');
canvas.width = 800;
canvas.height = 600;
var context = canvas.getContext('2d');
var socket = io();

var myId = -1;
var players = [];
window.onbeforeunload = function () {
    socket.emit('disconnection', myId);
}

function getRandomColor() {
    var letters = '0123456789ABCDEF'.split('');
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

function update() {
    socket.emit('update', myId, players[myId]);
}

socket.on('con', function (id) {
    if (myId == -1) {
        myId = id;
    }
    players[id] = {
        X: 15
        , Y: 15
        , R: 15
        , col: getRandomColor()
    }
});

window.addEventListener('mousemove', function (e) {
    players[myId].X = e.clientX;
    players[myId].Y = e.clientY;
}, false);


socket.on('upd', function (id, obj) {
    players[id] = obj;
})
socket.on('discon', function (id) {
    players[id] = undefined;
});

function draw() {
    context.clearRect(0, 0, canvas.width, canvas.height);
    for (var i in players) {
        if (players[i] != undefined) {
            context.fillStyle = players[i].col;
            context.beginPath();
            context.arc(players[i].X, players[i].Y, players[i].R, 0, 2 * Math.PI);
            context.fill();
        }
    }
}


var drw = setInterval(draw, 1);
var upd = setInterval(update, 10);
