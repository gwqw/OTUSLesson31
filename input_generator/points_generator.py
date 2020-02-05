#!/usr/bin/python3
"""
    Points generator (input file) for kkmeans
"""

import math, sys
from random import random, randint

def gauss(px, py, w, a, x, y):
    return a * math.exp(-((x-px)**2 + (y-py)**2)/ (2 * w**2))

def kitchen_func(area):
    if area < 60:
        return area / 4
    else:
        return 20 + area / 100

def rooms_func(area, kitchen_area):
    rooms = (area - kitchen_area) // 20
    if rooms <= 0: rooms = 1
    return rooms

def is_good_floor(floor, floor_count):
    return not(floor == 1 or floor == floor_count)

def price_func(area, floor_type, position_factor):
    price = area * 100000
    if not floor_type:
        price *= 0.8
    price *= position_factor
    return price

def calc_position_factor(centers, width, x, y):
    factor = 1
    for cx,cy in centers:
        factor += gauss(cx, cy, width, 10, x, y)
    return factor

def generate_centers(square_size, num):
    res = []
    for i in range(num):
        xi = square_size * random()
        yi = square_size * random()
        res.append((xi, yi))
    return res

def get_area_from_factor(factor):
    return factor * randint(1,10) + 20

class CoordGenerator:
    def __init__(self, circle_cnt, square_size):
        self.square_size = square_size
        self.circles = []
        for i in range(circle_cnt):
            xi = square_size * random() * 0.8 + 0.1 * square_size
            yi = square_size * random() * 0.8 + 0.1 * square_size
            ri = randint(1, int(0.1 * square_size))
            self.circles.append((xi, yi, ri))

    def generate_point(self):
        i = randint(0, len(self.circles)-1)
        x,y,r = self.circles[i]
        sign = 1.0 if random() > 0.5 else -1.0
        xi = 2 * r * random() - r
        yi = sign * math.sqrt(r * r - xi * xi)
        return xi + x, yi + y


def generate_data(square_size, points_num):
    coord_gen = CoordGenerator(points_num // 10, square_size)
    center_num = points_num // 20
    if center_num <= 0: center_num = 1
    centers = generate_centers(square_size, center_num)
    res = []
    for i in range(points_num):
        xi, yi = coord_gen.generate_point()
        factor = calc_position_factor(centers, square_size // 10, xi, yi)
        area = get_area_from_factor(factor)
        kitchen = kitchen_func(area)
        rooms = rooms_func(area, kitchen)
        floor = randint(1,10)
        price = price_func(area, is_good_floor(floor, 10), factor)
        res.append((xi, yi, rooms, price, area, kitchen, floor, 10))
    return res

def print_points(points):
    for x, y, rooms, price, area, kitchen, floor, floor_num in points:
        print(x, y, rooms, price, area, kitchen, floor, floor_num, sep=';')

if __name__ == "__main__":
    points = generate_data(1000, 200)
    print_points(points)