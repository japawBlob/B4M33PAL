import os

for x in range(1,9):
	fileName = "datapub/pub0" + str(x) + ".in" 

	with open(fileName, 'r') as input:
		lines = input.readlines()

	numbers = lines[0].split()
	#int(numbers[0])+2
	for x in range(int(numbers[0])):
		newFirstLine = numbers[0] + " " + numbers[1] + " " + str(x) + "\n"
		lines[0] = newFirstLine
		with open(fileName, 'w') as f:
			f.writelines(lines)
		#os.system('valgrind --log-fd=1 ./2Conveyor < pub12.in >> output.txt')
		osCopmmand = "./2Conveyor < " + fileName + " >> output.txt"
		os.system(osCopmmand)

#os.system('./2Conveyor < pub12.in >> output.txt')