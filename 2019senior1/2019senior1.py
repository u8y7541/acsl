fin = open('input.txt')
lines = [i.split() for i in fin.readlines()]
fin.close()
fout = open('output.txt', 'w')

isPrime = lambda x: all([x%i>0 for i in range(2, int(x**0.5)+1)])
def numPrimeFactors(x):
	y = x
	i = 2
	answer = 0
	while i<=y:
		if i%100 == 0:
			if isPrime(y):
				answer+=1
				break
		if y%i==0:
			while y%i == 0:
				y/=i
			answer+=1
		i+=1
	return answer

N, P = [i[0] for i in lines], [int(i[1]) for i in lines]
for i in range(5):
	cur, pos = list(N[i]), P[i]
	digit = int(cur[-pos])
	for j in range(len(cur)-pos):
		cur[j] = str(int(cur[j])+digit)
	for j in range(len(cur)-pos, len(cur)):
		cur[j] = str(abs(digit-int(cur[j])))
	cur[-pos] = str(numPrimeFactors(int(N[i])))
	print(''.join(cur), file=fout)
fout.close()
