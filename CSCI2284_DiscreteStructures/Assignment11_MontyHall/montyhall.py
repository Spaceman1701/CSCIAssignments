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


trial_sizes = [100, 1000, 100000]

for trial in trial_sizes:
    print("N = {trial}: ALWAYS SWAP: {swap}, NEVER SWAP: {noswap}".format(trial=trial,
            swap=monty_hall_simulate(True, trial), noswap=monty_hall_simulate(False, trial)))

# ---------------------------------------------------- results --------------------------------------------------
# N = 100: ALWAYS SWAP: 69.0, NEVER SWAP: 35.0
# N = 1000: ALWAYS SWAP: 65.60000000000001, NEVER SWAP: 35.099999999999994
# N = 100000: ALWAYS SWAP: 66.792, NEVER SWAP: 33.628
# ---------------------------------------------------------------------------------------------------------------
