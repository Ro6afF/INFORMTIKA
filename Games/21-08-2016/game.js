var draws = [];
var ipr = [];

for (var i = 0; i < 800; i++) {
    ipr[i] = [];
    for (var j = 0; j < 600; j++) {
        ipr[i][j] = false;
    }
}

var q = [];
q.push({
    X: 0,
    Y: 0
});
while (q.length > 0) {
    var sq = q[q.length - 1];
    if (sq.X >= 0 && sq.X < 800 && sq.Y >= 0 && sq.Y < 600 && ipr[sq.X][sq.Y] == false) {
        console.log(sq);
        ipr[sq.X][sq.Y] = true;
        q.push({
            X: sq.X + 100,
            Y: sq.Y
        });
        q.push({
            X: sq.X,
            Y: sq.Y + 75
        });
        q.push({
            X: sq.X + 46,
            Y: sq.Y + 46
        });
        q.push({
            X: sq.X + 46,
            Y: sq.Y - 46
        });
    }
    q.pop();
}

draws[0] = function(mx, my) {
    context.lineWidth = 10;
    context.strokeStyle = "#000000";
    context.beginPath();
    context.moveTo(mx, my);
    context.lineTo(mx + 100, my);
    context.stroke();
};

draws[1] = function(mx, my) {
    context.lineWidth = 10;
    context.strokeStyle = "#000000";
    context.beginPath();
    context.moveTo(mx, my);
    context.lineTo(mx, my + 75);
    context.stroke();
};

draws[2] = function(mx, my) {
    context.lineWidth = 10;
    context.strokeStyle = "#000000";
    context.beginPath();
    context.moveTo(mx, my);
    context.lineTo(mx + 46, my + 46);
    context.stroke();
};

draws[3] = function(mx, my) {
    context.lineWidth = 10;
    context.strokeStyle = "#000000";
    context.beginPath();
    context.moveTo(mx, my);
    context.lineTo(mx + 46, my - 46);
    context.stroke();
};

function update() {}

function draw() {
    for(var i = 0; i < 800; i++)
    {
        for(var j = 0; j < 600; j++)
        {
            context.fillStyle = "#000000";
            if(ipr[i][j])
            {
                context.fillRect(i, j, 1, 1);
            }
        }
    }
};

function keyup(key) {}

function mouseup() {};
