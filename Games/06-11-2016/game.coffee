canvas = document.getElementById('neshtosi')

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

orient = (x1, y1, x2, y2, x3, y3) ->
    (x1 * y2 + x3 * y1 + x2 * y3 - x3 * y2 - x1 * y3 - x2 * y1) > 0

areRotColliding = (a, b) ->
    i = 0
    while i < 4
        flag = true
        c = orient(a.px[3], a.py[3], a.px[0], a.py[0], b.px[i], b.py[i])
        j = 0
        while j < 3
            if orient(a.px[j], a.py[j], a.px[j + 1], a.py[j + 1], b.px[i], b.py[i]) != c
                flag = false
                break
            ++j
        if flag
            return true
        ++i
    i = 0
    while i < 4
        flag = true
        c = orient(b.px[3], b.py[3], b.px[0], b.py[0], a.px[i], a.py[i])
        j = 0
        while j < 3
            if orient(b.px[j], b.py[j], b.px[j + 1], b.py[j + 1], a.px[i], a.py[i]) != c
                flag = false
                break
            ++j
        if flag
            return true
        ++i
    false
 
class strv
    constructor: (@x, @y, color) ->
        @speed = 0;
        @gangle = 0
        @hangle = 0
        @hull = new rotRect @x, @y, 100, 100, 0, 1, color
        @gun = new rotRect @x + 50, @y, 100, 15, 0, 1, '#ffffff'

    moveGun: (angle) ->
        @gangle = angle
        sin = Math.sin angle
        cos = Math.cos angle
        @gun = new rotRect (@x + cos * 50), (@y + sin * 50), 100, 15, sin, cos, '#ffffff'
        return
                
    moveHull: (dX, dY) ->
        @x = @hull.x + dX
        @y = @hull.y + dY
        @hull.updatePos @x, @y
        @moveGun @gangle
        return    
    rotateHull: (angle) ->
        @hangle += angle
        @hull.updateAng (Math.cos @hangle), (Math.sin @hangle)
        return   
                
    draw: ->
        @hull.draw()
        @gun.draw()
 
getAng = (x1, y1, x2, y2, x3, y3) ->
    a1 = Math.atan2 y1 - y2, x1 - x2
    a2 = Math.atan2 y3 - y2, x3 - x2
    a1 - a2 + Math.PI / 2
    
keys = []
    
window.addEventListener 'mousemove', ((e) ->
    test.moveGun ((getAng e.pageX, e.pageY, test.gun.x, test.gun.y, 1000 + test.gun.x, test.gun.y) - Math.PI / 2)
    return
), false

window.addEventListener 'keydown', ((e) ->
    keys[e.keyCode] = true;
    return
), false

window.addEventListener 'keyup', ((e) ->
    keys[e.keyCode] = false;
    return
), false
        
update = ->
    if keys[37] || keys[65]
        test.rotateHull -0.02
    if keys[39] || keys[68]
        test.rotateHull 0.02
    if (keys[38] || keys[87]) && test.speed < 2
        test.speed += 0.02
    if (keys[40] || keys[83]) && test.speed > -2
        test.speed -= 0.02
    test.moveHull Math.cos(test.hangle) * test.speed, Math.sin(test.hangle) * test.speed
    if test.speed > 0
        test.speed -= 0.01
    if test.speed < 0
        test.speed += 0.01
	
test = new strv 500, 500, "#00ff00"

draw = ->
    context.clearRect 0, 0, canvas.width, canvas.height
    test.draw()
    return

canvas.width = window.innerWidth
canvas.height = window.innerHeight
context = canvas.getContext('2d')
upd = setInterval(update, 1)
drw = setInterval(draw, 33.3)
