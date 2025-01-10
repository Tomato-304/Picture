cars = ['bmw', 'audi', 'toyota', 'subaru']
cars.sort()
print(cars)

cars.reverse()
print(cars)

for car in cars:
    print(car)

squares = []

for value in range(1, 11):
    square = value ** 2
    squares.append(square)

print(squares)

players = ['charles', 'martina', 'michael', 'florence', 'eli']
print(players[2:])
my_favorite=players[:]
print(my_favorite)

name = ""
while ( name != 'your name'):
    print("Please type your name.")
    name = input()

print("Thank you!")