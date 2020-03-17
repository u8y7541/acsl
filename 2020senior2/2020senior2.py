alphabet = 'QWERTYUIOPASDFGHJKLZXCVBNM'
fin = open('sr-sample-input.txt')
fout = open('output.txt', 'w')
lines = [(i[:-1] if i[-1]=='\n' else i) for i in fin.readlines()]
lines = [''.join(['' if c.capitalize() not in alphabet else c.capitalize() for c in i]) for i in lines]

def ADF(a, b):
	maxlen, maxpos = -1, (0, 0)
	if (len(a)*len(b) == 0): return 0
	for sublen in range(1, min(len(a),len(b))+1):
		for i in range(len(a)-sublen+1):
			for j in range(len(b)-sublen+1):
				if a[i:i+sublen] == b[j:j+sublen]:
					if sublen == maxlen:
						if a[i:i+sublen]<a[maxpos[0]:maxpos[0]+maxlen]:
							maxpos = (i, j)
					else:
						maxlen = sublen
						maxpos = (i, j)
	if maxlen<0: return 0
	return maxlen + ADF(a[0:maxpos[0]],b[0:maxpos[1]]) + ADF(a[maxpos[0]+maxlen:],b[maxpos[1]+maxlen:])

for i in range(5):
	str1, str2 = lines[i*2], lines[i*2+1]
	print(ADF(str1,str2), file=fout)

fin.close()
fout.close()
