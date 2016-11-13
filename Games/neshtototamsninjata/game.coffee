canvas = document.getElementById 'canvas-id'
canvas.width = window.innerWidth
canvas.height = window.innerHeight
context = canvas.getContext '2d'

class rotRect
    constructor: (x, y, @len, @wid, sin, cos, @color) ->
        @px = []
        @py = []
        @updatePos(x, y)
        @updateAng(cos, sin)

    updatePos: (x, y) ->
        for i in [0...4]
            @px[i] += x - @x
            @py[i] += y - @y
        @x = x
        @y = y
        return

    updateAng: (@cos, @sin) ->
        ax = @cos * @len / 2
        ay = @sin * @len / 2
        bx = -@sin * @wid / 2
        bY = @cos * @wid / 2
        @px[0] = ax + bx + @x
        @py[0] = ay + bY + @y
        @px[1] = ax - bx + @x
        @py[1] = ay - bY + @y
        @px[2] = -ax - bx + @x
        @py[2] = -ay - bY + @y
        @px[3] = -ax + bx + @x
        @py[3] = -ay + bY + @y
        return

    draw: ->
        context.fillStyle = @color
        context.beginPath()
        for i in [0...4]
            context.lineTo @px[i], @py[i]
        context.fill()
        return

class shuriken
    constructor: (@x, @y, @dir) ->
        @ang = 0
        @rect1 = new rotRect @x, @y, 20, 5, (Math.sin @ang), (Math.cos @ang), '#777777'
        @rect2 = new rotRect @x, @y, 5, 20, (Math.sin @ang), (Math.cos @ang), '#777777'

    move: ->
        @ang += 0.5
        @rect1.updatePos @rect1.x + (10 * Math.cos @dir), @rect1.y - (10 * Math.sin @dir)
        @rect2.updatePos @rect2.x + (10 * Math.cos @dir), @rect2.y - (10 * Math.sin @dir)
        @x += 10 * Math.cos @dir
        @y -= 10 * Math.sin @dir
        @rect1.updateAng (Math.cos @ang), (Math.sin @ang)
        @rect2.updateAng (Math.cos @ang), (Math.sin @ang)
        return

    draw: ->
        context.fillStyle = '#777777'
        context.strokeStyle = '#777777'
        context.globalAlpha = 0.25
        context.beginPath()
        context.arc @x, @y, 10, 0, 2 * Math.PI
        context.fill()
        context.globalAlpha = 1
        context.beginPath()
        context.arc @x, @y, 10, 0, 2 * Math.PI
        context.stroke()
        @rect1.draw()
        @rect2.draw()
        return

class gad
    constructor: (@x, @y, @col) ->
        @ang = 0
        @pow = 0

    lookAt: (x, y) ->
        @ang = Math.PI - Math.atan2 @y - y, @x - x
        return

    move: ->
        @x += Math.cos @ang
        @y -= Math.sin @ang

    draw: ->
        context.fillStyle = @col
        context.strokeStyle = @col
        context.globalAlpha = 0.25
        context.beginPath()
        context.arc @x, @y, 20, 0, 2 * Math.PI
        context.fill()
        context.globalAlpha = 1
        context.beginPath()
        context.arc @x, @y, 20, 0, 2 * Math.PI
        context.stroke()
        context.beginPath()
        context.moveTo @x, @y
        context.lineTo @x + (Math.cos @ang) * 20, @y - (Math.sin @ang) * 20
        context.stroke()
        return

ninja = new gad canvas.width / 2, canvas.height / 2, '#00ff00'
gadove = []
keys = []
shurikeni = []

window.addEventListener 'mousemove', ((x) ->
    ninja.lookAt x.pageX, x.pageY
), false

window.addEventListener 'keydown', ((x) ->
    keys[x.keyCode] = true
    return
), false

window.addEventListener 'keyup', ((x) ->
    keys[x.keyCode] = false
    return
), false

window.addEventListener 'mousedown', ((x) ->
    shurikeni.push new shuriken canvas.width / 2, canvas.height / 2, Math.PI - Math.atan2 canvas.height / 2 - x.pageY, canvas.width / 2 - x.pageX
    return
), false

gen = ->
    pos = Math.random() * (2 * Math.PI)
    dist = (canvas.width + canvas.height) / 2
    gadove.push new gad (dist * Math.cos pos) + canvas.width / 2, (dist * Math.sin pos) + canvas.height / 2 , '#ff0000'
    gadove[gadove.length - 1].lookAt canvas.width / 2, canvas.height / 2
    return

update = ->
    i = 0
    while i < gadove.length
        gadove[i].move()
        if (Math.sqrt ((gadove[i].x - ninja.x) * (gadove[i].x - ninja.x)) + ((gadove[i].y - ninja.y) * (gadove[i].y - ninja.y))) <= 40
            alert 'Zagubenqk'
            clearInterval upd
            clearInterval gn
            clearInterval drw
        i++
    i = 0
    while i < shurikeni.length
        shurikeni[i].move()
        if shurikeni[i].x < 0 || shurikeni[i].x > canvas.width || shurikeni[i].y < 0 || shurikeni[i].y > canvas.height
            shurikeni[j] = shurikeni[shurikeni.length - 1]
            shurikeni.pop()
        i++
    i = 0
    while i < gadove.length
        j = 0
        while j < shurikeni.length
            if (Math.sqrt ((gadove[i].x - shurikeni[j].x) * (gadove[i].x - shurikeni[j].x)) + ((gadove[i].y - shurikeni[j].y) * (gadove[i].y - shurikeni[j].y))) <= 30
                gadove[i] = gadove[gadove.length - 1]
                gadove.pop()
                shurikeni[j] = shurikeni[shurikeni.length - 1]
                shurikeni.pop()
            j++
        i++
    return

draw = ->
    context.clearRect 0, 0, canvas.width, canvas.height
    ninja.draw()
    i = 0
    while i < gadove.length
        gadove[i].draw()
        i++
    i = 0
    while i < shurikeni.length
        shurikeni[i].draw()
        i++
    return

gn = setInterval gen, 1000
upd = setInterval update, 10
drw = setInterval draw, 33.3
