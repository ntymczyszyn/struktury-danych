import csv
import random

max_number = 1000000
P_random_numbers = [i for i in range(max_number)]
random.shuffle(P_random_numbers)
P_ordered_numbers = [i for i in range(max_number)]
P_reversed_numbers = list(reversed(P_ordered_numbers))

max_number_halved = int(max_number/2)
PN_random_numbers = [i for i in range(-max_number_halved, max_number_halved)]
random.shuffle(PN_random_numbers)
PN_ordered_numbers = [i for i in range(-max_number_halved, max_number_halved)]
PN_reversed_numbers = list(reversed(PN_ordered_numbers))

with open('P_random_numbers.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)

    for num in P_random_numbers:
        writer.writerow([num])

with open('P_ordered_numbers.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)

    for num in P_ordered_numbers:
        writer.writerow([num])

with open('P_reversed_numbers.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)

    for num in P_reversed_numbers:
        writer.writerow([num])

with open('PN_random_numbers.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)

    for num in PN_random_numbers:
        writer.writerow([num])

with open('PN_ordered_numbers.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)

    for num in PN_ordered_numbers:
        writer.writerow([num])

with open('PN_reversed_numbers.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)

    for num in PN_reversed_numbers:
        writer.writerow([num])
















