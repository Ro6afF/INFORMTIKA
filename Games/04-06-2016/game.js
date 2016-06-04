var grid  = [];
for(var i = 0; i < 3; i++) {
    grid[i] = [];
    for(var j = 0; j < 3; j++) {
        grid[i][j] = [];
        for(var n = 0; n < 3; n++) {
            grid[i][j][n] = 0;
        }
    }
}

var turn = 1;

function update() {
};

function draw() {
    for(var i = 0; i < 3; i++) {
        for(var j = 0; j < 3; j++) {
            for(var n = 0; n < 3; n++) {
                context.fillStyle = (grid[i][j][n] != 0) ? ((grid[i][j][n] == 1)?"#00ff00" : "#ff00ff") : "#000000";
                context.globalAlpha = 1 / ((3-i) + 1);
                context.fillRect((30 * j) + (i * 5), (30 * n) + (i * 5), 29 - (i*10), 29 - (i*10));
            }
        }
    }
};

function mouseup() {
    for(var j = 0; j < 3; j++) {
        for(var n = 0; n < 3; n++) {
            var cnt = 0;
            for(var i = 0; i < 3; i++) {
                if(areColliding(mouseX, mouseY, 1, 1,(30 * j) + (i * 5), (30 * n) + (i * 5), 29 - (i*10), 29 - (i*10) )) {
                    cnt++;
                }
            }
            if(cnt != 0) {
                if(grid[cnt-1][j][n] == 0) {
                    grid[cnt - 1][j][n] = turn;
                    turn *= -1;
                }
                return;
            }
        }
    }
}

