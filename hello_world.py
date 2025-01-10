# message = "Hello Python world!"
age = 23
message = "Happy " + str(age) + "rd Birthday!"
#print(message)
# message = "One of Python's strengths is its diverse community."
# print(message)
# print(2 + 3 * 4)
# print(3 * 0.1)

# name="ada lovelace"
# print(name.title())
# print(name.upper())
# print(name.lower())

# bicycles = ['trek', 'cannondale', 'redline', 'specialized']
# bicycles[0] = 'honda'
# del bicycles[0]
# bicycles.insert(0, 'csfg')
# pop_message = bicycles.pop()
# message = "My first bicycle was a " + bicycles[0].upper() + "."
# print(message)
# print(pop_message)
# print(bicycles.__len__())

#print("Hello World!")
#print("What's your name?")
#my_name = input()
#print("It's good to meet you, " + my_name.title() + ".")
#print("The length of your name is: " + str(len(my_name)))

menus=('a','b','c','d','e')
#for menu in menus:
    # print(menu)

# menus[0]='f'

#alien_0 = {'color': 'green', 'points': 5}
#new_print = alien_0['points']
#alien_0['x_position'] = 21
#alien_0['y_position'] = 22
# print(alien_0)

alien_1={}
alien_1['color']='green'
alien_1['points']=5 
alien_1['x_position']=0
alien_1['y_position']=25
alien_1['color']='yellow'


alien_0 = {'x_position': 15, 'y_position': 25, 'speed': 'medium'}
# print("Original x-position: " + str(alien_0['x_position']))

if alien_0['speed'] == 'slow':
    x_increment = 1
elif alien_0['speed'] == 'medium':
    x_increment = 2
else:
    x_increment = 3

# print("New x-position: " + str(alien_0['x_position'] + x_increment))


user_0 = {
'username': 'efermi',
'first': 'enrico',
'last': 'fermi',
}


alien_0 = {'color': 'green', 'points': 5}
alien_1 = {'color': 'yellow', 'points': 10}
alien_2 = {'color': 'red', 'points': 15}
aliens = [alien_0, alien_1, alien_2]
for alien in aliens:
    print(alien)

users = {

    'aeinstein': {
        'first': 'albert',
        'last': 'einstein',
        'location': 'princeton',
    },

    'mcurie': {
        'first': 'marie',
        'last': 'curie',
        'location': 'paris',
    },

    'jsmith': {
        'first': 'john',
        'last': 'smith',
        'location': 'new york',
    },

}

for username, user_info in users.items():
    print("\nUsername: " + username)
    full_name = user_info['first'] + " " + user_info['last']
    location = user_info['location']

    print("\tFull name: " + full_name.title())
    print("\tLocation: " + location.title())