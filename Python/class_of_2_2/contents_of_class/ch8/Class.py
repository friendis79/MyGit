import turtle
t=turtle.Turtle()
t.shape("turtle")

class Shape:
    def __init__(self,length,angle):
        self.length=length
        self.angle=angle
    def draw(self):
        turtle.title("그리기")
        
class Rectangle(Shape):
    def __init__(self,length, angle):
        Shape.__init__(self,length,angle)
        
    def draw(self):
        Shape.draw(self)
        t.penup()
        t.right(135)
        t.forward(self.length)
        t.left(135)
        t.pendown() 
        for i in range(4):
            t.forward(self.length*2**(1/2))
            t.left(self.angle)
        t.penup()
        t.home()
            
class Circle(Shape):
    def __init__(self,length,angle):
        Shape.__init__(self,length,angle)
    def draw(self):
        t.penup()
        t.right(90)
        t.forward(self.length)
        t.left(90)
        t.pendown() 
        Shape.draw(self)
        t.circle(self.length)
        t.penup()
        t.home()

class Hexagon(Shape):
    def __init__(self,length,angle):
        Shape.__init__(self,length,angle)
    def draw(self):
        Shape.draw(self)
        t.right(90)
        t.forward(self.length)
        t.left(135)
        t.pendown()
        t.left(-15)
        for i in range(6):
            t.forward(self.length)
            t.left(self.angle)
        t.penup()
        t.home()

circle=Circle(100,0)
circle.draw()
rectangle=Rectangle(100, 90)
rectangle.draw()
hexagon=Hexagon(100,60)
hexagon.draw()
turtle.done()
turtle.bye()