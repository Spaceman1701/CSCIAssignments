import random


def monty_hall_simulate(switch, num_trials):
    success = 0
    for trial in range(num_trials):
        car_door = random.randint(0, 2)
        pick = random.randint(0, 2)
        if switch:
            reveal_door = random.choice([x for x in range(3) if x is not pick and x is not car_door])
            pick = random.choice([x for x in range(3) if x is not pick and x is not reveal_door])
        if pick is car_door:
            success += 1
    return success / num_trials * 100


print(monty_hall_simulate(True, 100000))
print(monty_hall_simulate(False, 100000))






