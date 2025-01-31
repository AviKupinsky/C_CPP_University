import turtle

def draw_petal():
    """drawing petal"""
    turtle.forward(30)
    turtle.right(45)
    turtle.forward(30)
    turtle.right(135)
    turtle.forward(30)
    turtle.right(45)
    turtle.forward(30)
    turtle.right(135)


def draw_flower():
    """"drawing a full flower"""
    turtle.left(45)
    draw_petal()
    turtle.left(90)
    draw_petal()
    turtle.left(90)
    draw_petal()
    turtle.left(90)
    draw_petal()
    turtle.left(135)
    turtle.forward(150)


# this next segment is drawing a flower and moving the turtle forward
def draw_flower_and_advance():
    """"drawing a flower and advance"""
    draw_flower()
    turtle.right(90)
    turtle.up()
    turtle.forward(150)
    turtle.right(90)
    turtle.forward(150)
    turtle.left(90)
    turtle.down()


# this next segment reverses the way the flower is drawn
def draw_flower_bed():
    """"drawing a flower bed"""
    turtle.up()
    turtle.forward(200)
    turtle.left(180)
    turtle.down()

if __name__ == "__main__":
    draw_flower_bed()
    draw_flower_and_advance()
    draw_flower_and_advance()
    draw_flower_and_advance()

turtle.done


