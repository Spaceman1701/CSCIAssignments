from fast_factorization import factorize_fast
from slow_factorization import factorize_slow
from composites import CompositeNumberMap

from time import clock

import sys


def run_factor_speed(num_map, num_digs, num_trials, function):  # performance measurement function
    success_count = 0
    avg_time = clock()
    for i in range(num_trials):
        n = num_map.random_number(num_digs)[0]
        result = function(n, 300)
        if result:
            success_count += 1
    avg_time = clock() - avg_time
    return avg_time / num_trials, success_count / num_trials


def write_pref_test(out_file, num_map, num_trials):  # csv writing performance test
    with open(out_file, 'w') as output:
        output.write("digits,Pollard Rho-Time,Pollard Rho-Success,Brute Force-Time,Brute Force-Success,trials={trials}"
                     .format(trials=num_trials))
        output.write('\n')

    for n_size in num_map.available_sizes():
        total_time = clock()
        fast_results = run_factor_speed(num_map, n_size, num_trials, factorize_fast)
        slow_results = run_factor_speed(num_map, n_size, num_trials, factorize_slow)
        total_time = clock() - total_time
        print("completed trial n={size} in {time} seconds.".format(size=n_size, time=total_time))
        with open(out_file, 'a') as output:
            output_str = str(n_size) + "," + str(fast_results[0]) + "," + str(fast_results[1]) + "," + \
                str(slow_results[0]) + "," + str(slow_results[1]) + '\n'
            output.write(output_str)


def run_perf_test(composite_map, num_digs, num_trials):  # simple performance test
    fast_results = run_factor_speed(composite_map, num_digs, num_trials, factorize_fast)
    print("Pollard Rho Results:", fast_results)

    slow_results = run_factor_speed(composite_map, num_digs, num_trials, factorize_slow)
    print("Brute Force Resutls:", slow_results)


def simple_factor(number, timeout):
    results = factorize_fast(number, timeout)
    if not results:
        print("Failed to find factors in {timeout} seconds.".format(timeout=timeout))
    print("Found factors {factor_one}, {factor_two} in {time} seconds."
          .format(factor_one=results[0], factor_two=results[1], time=results[2]))

if __name__ == '__main__':  # handles the command line arguments. Messy, but doesn't have any critical functionality
    args = sys.argv
    if len(sys.argv) == 1:  # write to a csv because I have to go to class
        file_name = "nums.txt"
        cm = CompositeNumberMap(file_name)
        print("available n sizes:", cm.available_sizes())
        out_file = input("output:")
        write_pref_test(out_file, cm, 15)
    elif '-p' in args:  # prompt version so I can gather data in my IDE without having to edit my config every time
        file_name = "nums.txt"
        cm = CompositeNumberMap(file_name)
        print("available n sizes:", cm.available_sizes())
        num_digs = int(input("digs:"))
        num_trials = int(input("trials:"))
        run_perf_test(cm, num_digs, num_trials)
        print("finished n={digs} trial".format(digs=num_digs))  # so I don't forget which is which
    elif '-c' in args:
        file_name = args[args.index('-c') + 1]
        cm = CompositeNumberMap(file_name)
        print("available n sizes:", cm.available_sizes())
        num_digs = int(args[args.index('-c') + 2])
        num_trials = int(args[args.index('-c') + 3])
        run_perf_test(cm, num_digs, num_trials)
    else:
        number = int(args[1])
        timeout = 600000
        if '-t' in args:
            timeout = int(args[args.index('-t') + 1])
        simple_factor(number, timeout)


