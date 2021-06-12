#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun  8 23:18:15 2021

@author: ayoub
"""

import turtle
import math as m
import threading
import time
from ctypes import *
file = "/Rice_Eating_Philo/RIICE/rice.so"
my_functions = CDLL(file)

def color(col,philos,i):
    philos[i].fillcolor(col)
    philos[i].begin_fill()
    philos[i].circle(5)
    philos[i].end_fill()

def draw(philos,i):
    philos[i].up()
    philos[i].goto(45*m.cos(i*2*m.pi/7),45*m.sin(i*2*m.pi/7))
    philos[i].down()
    color("black",philos,i)

def Life(philos,i):
    n=my_functions.countdown()
    while(n > 0):
        if(my_functions.states(i) == 0):
            color("red",philos,i)
        elif(my_functions.states(i) == 1):
            color("blue",philos,i)
        else:
            color("yellow",philos,i)
        time.sleep(1)
        n=my_functions.countdown()

print("Red for resting, blue for eating, yellow for thinking")
print("There is also a written follow-up of what's happening in the terminal in case you want to check ")
print("noting that is not the final form of the code, as we can go EVEN.. FURTHER.. BEYOOOND")

philos = list()
for i in range(7):
    x = turtle.Turtle()
    philos.append(x)

wn = turtle.Screen()
wn.title("Turtle")

t = turtle.Turtle()
t.up()
t.goto(0,-25)
t.down()
t.fillcolor("brown")
t.begin_fill()
t.circle(30)
t.end_fill()
    
for i in range(7):
    draw(philos,i)
    

for i in range(7):
    x = threading.Thread(target = Life,args=(philos,i))
    x.start()

y = threading.Thread(target=my_functions.main,daemon=True)
y.start()
        
turtle.exitonclick()
