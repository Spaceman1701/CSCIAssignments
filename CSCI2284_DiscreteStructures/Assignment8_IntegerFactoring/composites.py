import random


class CompositeNumberMap:
    """
    handles loading of a file containing a list of composite numbers for the performance testing function
    """
    def __init__(self, file_name):
        self.numbers = dict()

        number_list = None
        with open(file_name, 'r') as file:
            number_list = file.readlines()
        number_list = [int(line.strip()) for line in number_list]

        for number in number_list:
            dig = len(str(number))
            bits = dig.bit_length()

            if dig not in self.numbers:
                self.numbers[dig] = []
            self.numbers[dig].append((number, bits))

    def random_number(self, num_dig):
        """
        :param num_dig: size of number in digits
        :return: a random number with the given number of digits
        """
        n = random.choice(self.numbers[num_dig])
        assert len(str(n[0])) == num_dig
        return n

    def available_sizes(self):
        return [key for key, value in self.numbers.items()]