# Matthew Pool
# Wormhole: A Text Adventure Game
# @author Matthew Pool
"""This program is a text-based game.
To Win: Player must collect all seven items before finding the location of the Alien Worm
rev 1.0 serves as a demo and include basic gameplay with 'go direction' and 'exit' commands
rev 2.0 adds the use of the 'get item' command, as well as other optimization and design changes
rev 3.0 will add a map to help with navigation and enhance gameplay experience
"""
# MODULES
from time import sleep
from sys import platform
from os import system
# try: from os import get_terminal_size

# SETTINGS
REV = 3.0  # revision number
ENTER = False  # determines if enter_prompt() prompts user for ENTER KEY
CLEAR = True  # determines setting for clearing terminal output

# TODO: text-scrolling
TEXT_SPEED = 0.05  # default speed: 0.05 or 0 (higher is faster)
TEXT_WIDTH = 78  # try: = get_terminal_size().columns
TEXT_OFFSET = 0  # default around 40 maybe
switch = True  # determines initial delay for 1st line of room_text 

# line lengths
MULTIPLIER = 94  # determines long_line length
long_line = '-' * MULTIPLIER
short_line = '-' * 22

# sleep (wait) time in seconds
QUICK = 0.6
MEDIUM = 1.3
SLOW = 2.0

# OTHER DECLARATIONS
BYE = 'Thanks for playing!\n'  # final message

# commands
if REV == 1.0:
    COMMANDS = 'commands: [go south, go north, go east, go west, exit'  # no get_item command
    MAP = False

elif REV == 2.0:
    COMMANDS = 'commands: [ go south | go north | go east | go west || get item (example: get light) || exit ]'  # get_item available
    MAP = False

elif REV == 3.0:
    COMMANDS = 'commands: [ go south | go north | go east | go west || get item (example: get light) || exit ]'  # map available
    MAP = True

else:
    print('ERROR: revision number not recognized')
    quit(1)  # exit with error


# START DEF FUNCTIONS **************************************************************************************************

# clear()
def clear():
    """clears terminal output in Windows OS"""
    if platform.startswith('win32'):
        system('cls')
    # TODO: other OSes


def rules():
    """outputs player commands to user"""
    print("To Move:  'go direction' (Example: go North")
    print("Get Item: 'get item'     (Example: get light)")
    print("Quit:     'exit'\n")

    sleep(QUICK)
    return None


def show_instructions():
    """Function to show end user the title, instructions, commands"""

    # title
    title = 'Wormhole'

    # sub_title
    sub_title = 'A text adventure game'

    # directions
    directions = '* Collect all seven ITEMS before encountering the hideous alien worm creature!'

    # output to user
    print('\n{:^20s}'.format(title))
    print('\n{:^20s}'.format(sub_title))
    print('\n{:^20s}'.format(directions))

    print(long_line)
    print('{:^20s}'.format(COMMANDS))
    print(long_line)

    if ENTER:
        input('Press <ENTER>')

    return None


def room_message(_current_room, _inventory):
    """function to determine appropriate text to show user"""
    room_text = ''
    _current_room = _current_room.lower()

    if _current_room == 'cavern':
        room_text = "You awaken on the ground with your clothes soaking wet - feeling sluggish and disoriented. \nYou slowly stand up and look around to check your unfamiliar surroundings. \nYou seem to be in some sort of cave or cavern. \"Where am I?\" you wonder. \nHaving been born with a keen sense of cardinal direction, you look North.\nYou see a small, dark passage-way, just big enough to squeeze through..."
        # room_text = "The only way to go is North..."

    elif _current_room == 'entryway':
        room_text = "The path to the South is now blocked by falling rock and debris. \nTo the West you see a path full of leaves and vines. \nTo the East you see a big stainless steel door."

    elif _current_room == 'garden':
        room_text = "Weird alien mushrooms growing everywhere! It\'s truly magnificent. \nMaybe I should pick up just one for the road. I see a path to the North."

    elif _current_room == 'pink pond':
        room_text = "I've never seen water like this before! That fish! What is that?! \nI could surely make some delicious fish paste out of one of those! A path to the North continues..."

    elif _current_room == 'graveyard':
        room_text = "Looks like things have been buried down here. What is that? It's some kind of ancient text. \nIt says \'If you have all seven, to the right will be Heaven' - signed, EWJ. Hmmmmmmm weird. "

    elif _current_room == 'freezer':
        room_text = "So cold. And dark. What is this place? Oh my God. Are those..... Human corpses?! \nThere's a key hanging by another steel door on the North-side and a sign that says, \n\"Fresh Earthling Meat\". I\'d better just grab that key and run..."

    elif _current_room == 'laboratory':
        room_text = "You walk into some sort of Science lab. Beakers and flasks and things everywhere. \nHalf-human, half-worm thingy. Disgusting. But such intricate gadgets and gizmos hanging on the wall. \nThere's a hole to the North that's been dug out by who-knows-what."

    elif _current_room == 'dump':
        room_text = "That smell! What is that awful, rancid scent? Wait... I'd recognize that smell anywhere. \nIt's poop. And not just any poop. Alien. Worm. Poop. Of course! A sign on the West wall reads, \n\"You're getting worm-er\". A poop pun. I'm too tired for puns. In fact... I'm pooped."

    elif _current_room == 'worm incubation chamber':

        if len(_inventory) == 7:
            room_text = 'A giant, hideous alien worm creature erupts from the ground below you. \nYou pull out your wormhole blaster, filling it with fish paste and warm worm poo. \nYou start firing, disintegrating the alien worm into a splatter of slime. \nThe ground starts giving away as more wormholes appear! You quickly fire at the ground. \nA cosmological wormhole appears, and you leap! Guess you are a little worm-er after all.'

        elif len(_inventory) != 7:
            room_text = 'A giant, hideous alien worm creature erupts from the ground below you. Looks like you\'re worm food...\nOof.\n\nGAME OVER'

    else:
        room_text = 'Where on Earth are you!?'

    return room_text


def show_status(_current_room, _inventory, _item):
    """show player the current room, inventory, and any items in the room"""
    # current room
    if _current_room == 'worm incubation chamber':
        tmp_title = 'Worm Incubation Chamber'
        print('\n{:^20s}\n'.format(tmp_title))
    else:
        print('\n{:^20s}\n'.format(_current_room.capitalize()))

    # call room_message()
    room_text = room_message(_current_room, _inventory)

    # output room_text from room_message()
    print(room_text)


    # current_room -item check
    if _item != '' and _item != "alien worm":  # player does not have current_room item
        print('You see a(n) {}.'.format(_item.upper()))  # item message

    # inventory
    print('\ninventory:', _inventory)

    print(short_line)

    return room_text


def get_input():
    """prompt user for command"""
    print('What do you do!?')
    user_input = (input('>')).strip().lower()

    try:
        user_input = (user_input.split(' '))
    except IndexError or NameError or TypeError:
        print('What?')
        sleep(MEDIUM)

    return user_input


def is_valid(_user_input, _current_room, _rooms, _silly_count, _inventory):
    """validate user_input as acceptable command or show error to user"""
    # check if user_input is valid
    if _user_input is not None and _user_input != '' and _user_input != ' ':

        try:
            if _user_input[0].lower() == 'go':

                if _user_input[1].lower() in _rooms[_current_room]:
                    print('You decide to go {}...'.format(_user_input[1].capitalize()))
                    print(short_line)
                    if CLEAR:
                        sleep(MEDIUM)
                    else:
                        sleep(QUICK)

                    # update player location
                    new_room = (_rooms[_current_room][_user_input[1]])
                    valid = True
                    return valid, new_room, _silly_count, _inventory

                else:
                    if _silly_count == 0:
                        print('You can\'t really do that, silly...')
                    elif _silly_count == 1:
                        print("We would go {} if we could...".format(_user_input[1]))
                    elif _silly_count == 2:
                        print("OK. Look, bruh. I appreciate your ruthless persistence for {}, but it's just not here!!!".format(_user_input[1]))
                    elif _silly_count == 3:
                        print("BRUH?!")
                    elif _silly_count == 4:
                        rules()
                        _silly_count = -1

                    _silly_count += 1

                    print(short_line)
                    sleep(QUICK)
                    valid = False
                    return valid, _current_room, _silly_count, _inventory

            elif _user_input[0].lower() == 'get':

                if _user_input[1].lower() == _rooms[_current_room]['item']:
                    get_item = _user_input[1].lower()
                    print(get_item.upper() + ' retrieved!')
                    _inventory.append(get_item)
                    _rooms[_current_room]['item'] = ''
                    sleep(MEDIUM)
                    valid = True
                    return valid, _current_room, _silly_count, _inventory

                elif _user_input[1].lower() == '':
                    rules()
                    valid = False
                    return valid, _current_room, _silly_count, _inventory

                else:
                    if _silly_count == 0:
                        print("I don't see that here, silly...")
                    elif _silly_count == 1:
                        print("I would tell you if there was a {} here...".format(_user_input[1]))
                    elif _silly_count == 2:
                        print("OK. Look, bruh. I respect your ruthless persistence to find a {}, but it's just not here!!!".format(_user_input[1]))
                    elif _silly_count == 3:
                        print("Huh?")
                    elif _silly_count == 4:
                        rules()
                        _silly_count = -1

                    _silly_count += 1

                    print(short_line)
                    sleep(QUICK)

                    valid = False
                    return valid, _current_room, _silly_count, _inventory

            elif _user_input[0].strip().lower() == 'exit':
                user_confirm = ''

                while user_confirm.lower() != 'y' and user_confirm.lower() != 'n':
                    print('\n', short_line)
                    print('Are you sure(Y/N)?')
                    user_confirm = input('>')
                    try:
                        if user_confirm.lower() == 'y':
                            print('\nYou succumb to the fear and desperation and end your journey suddenly...\n')
                            sleep(SLOW)
                            print(BYE)
                            exit()

                        elif user_confirm.lower() == 'n':
                            print('\nYou decide to hold on a little bit longer...\n')
                            sleep(QUICK)

                        else:
                            print('Bruh...')
                            sleep(QUICK)

                    except IndexError or NameError or TypeError:
                        print('Say what?')

                valid = False
                return valid, _current_room, _silly_count, _inventory

            else:
                print('What now?')
                print(short_line)
                sleep(QUICK)
                valid = False
                return valid, _current_room, _silly_count, _inventory

        except IndexError or NameError or TypeError:
            rules()
            valid = False
            return valid, _current_room, _silly_count, _inventory

    else:
        rules()
        valid = False
        return valid, _current_room, _silly_count, _inventory


# START def main()******************************************************************************************************


def main():

    # rooms dict links a primary room key with a value consisting of at least one key(room):value(direction)
    rooms = {
        # start location
        'cavern':       {'north': 'entryway', 'item': ''},
        # 1st official game room
        'entryway':     {'east': 'freezer', 'west': 'garden', 'item': 'compass'},
        # west wing
        'garden':       {'east': 'entryway', 'north': 'pink pond', 'item': 'shroom'},
        'pink pond':    {'south': 'garden', 'north': 'graveyard', 'item': 'fish'},
        'graveyard':    {'south': 'pink pond', 'east': 'worm incubation chamber', 'item': 'scripture'},
        # east wing
        'freezer':      {'west': 'entryway', 'north': 'laboratory', 'item': 'key'},
        'laboratory':   {'south': 'freezer', 'north': 'dump', 'item': 'gun'},
        'dump':         {'south': 'laboratory', 'west': 'worm incubation chamber', 'item': 'poop'},
        # enemy location
        'worm incubation chamber': {'item': 'alien worm'},
    }

    # creates empty inventory
    inventory = []

    # start room
    current_room = 'cavern'

    # silly stuff
    silly_count = 0

    # valid user_input
    valid = False

    # clearn terminal output
    clear()

    # title, directions, commands
    # show_instructions()

    # delay
    sleep(SLOW)

    # loop forever
    while True:

        if CLEAR:
            clear()
            show_instructions()

        item = rooms[current_room]['item']

        # update status output to user
        show_status(current_room, inventory, item)

        # check if game is over
        if item == 'alien worm' and len(inventory) != 7:  # lose game
            print('\n\n')
            break

        elif item == 'alien worm' and len(inventory) == 7:  # win game
            print('\nAw man... You win, bruh!')
            break

        # loop until valid user_input
        while True:

            # get user input command
            user_input = get_input()

            try:
                # check validity of user input
                if user_input != '' and user_input != [] and user_input is not None:
                    if user_input[0] != '' and user_input[0] != [] and user_input is not None:
                        try:
                            valid, current_room, silly_count, inventory = is_valid(user_input, current_room, rooms, silly_count, inventory)

                        except IndexError or NameError or TypeError:
                            valid = False

            except IndexError or NameError or TypeError:
                print('Say what?')

            # is user_input valid
            if valid:
                break  # exit input loop


# END OF DEF FUNCTIONS**************************************************************************************************
if __name__ == "__main__":

    main()

    # game over
    print(BYE)
    
    user_input = get_input();

    exit()
