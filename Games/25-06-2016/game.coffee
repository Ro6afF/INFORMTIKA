canvas = document.getElementById 'canvas-id'
canvas.width = 800
canvas.height = 600
context = canvas.getContext '2d'

field = []

for i in [0..35]
    field[i] = (
        X: ((i % 6) * 90) + Math.floor(i / 6) * 15 * 3 + 10,
        Y: Math.floor(i / 6) * 22 * 3 + 10,
        p: 0
    )
imgs = []

imgs[0] = new Image()
imgs[1] = new Image()
imgs[2] = new Image()

imgs[0].src = 'empty.png'
imgs[1].src = 'red.png'
imgs[2].src = 'green.png'

turn = 1

oriented = (p1x, p1y, p2x, p2y, p3x, p3y) ->
    (p1x + p2x) * (p1y - p2y) + (p2x + p3x) * (p2y - p3y) - (p1x + p3x) * (p1y - p3y) / 2

isInHex = (X, Y, num) ->
    p = [(X: field[num].X + 45, Y: field[num].Y), (X: field[num].X + 90, Y: field[num].Y + 11), (X: field[num].X + 90, Y: field[num].Y + 90 - 11), (X: field[num].X + 45, Y: field[num].Y + 90), (X: field[num].X, Y: field[num].Y + 11), (X: field[num].X, Y: field[num].Y + 90 - 11)]
    c = (X: field[num].X + 45, Y: field[num].Y + 45)
    for i in [0..5]
        if i != 5
            if oriented(p[i].X, p[i].Y, p[i+1].X, p[i+1].Y, c.X, c.Y) != oriented(p[i].X, p[i].Y, p[i+1].X, p[i+1].Y, X, Y)
                return false
        else
            if oriented(p[i].X, p[i].Y, p[0].X, p[0].Y, c.X, c.Y) != oriented(p[i].X, p[i].Y, p[0].X, p[0].Y, X, Y)
                return false
                
    true

window.addEventListener 'mouseup', ((args) ->
    for i in [0..35]
        if isInHex args.pageX, args.pageY, i
            console.log i
    return), false

update = ->
    
draw = (aX, aY, col) ->
    context.clearRect 0, 0, canvas.width, canvas.height
    for i in field
        context.drawImage imgs[i.p], i.X, i.Y, 90, 90 
    return 

upd = setInterval update, 1
drw = setInterval draw, 1