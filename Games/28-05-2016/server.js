var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var id = 0;

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/index.html');
});

app.get('/:file', function (req, res) {
    res.sendFile(__dirname + '/' + req.params.file);
});

io.on('connection', function (socket) {
    io.emit('con', id++);
    socket.on('disconnection', function (id) {
        io.emit('discon', id);
    });

    socket.on('update', function (id, obj) {
        io.emit('upd', id, obj);
    })
});

http.listen(3000, function () {
    console.log('listening on *:3000');
});
