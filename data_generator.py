#/usr/bin/python

from random import randint

print "### DATASET GENERATOR ###"

def percentage(part, whole):
  return 100 * float(part)/float(whole)

__RMX__ = 1.125
__RUM__ = 0xAFF

def get_in_range(range_):
	val = randint(-range_ / 2,range_)
	return abs(val) + 1

def make_range(old):
	old *= __RMX__
	return old

ran = 5
template = ""

first = 10
second = 5
third = 10

total = ((third * second) * first)
work = 0
lastwork = -1

for line in range(1,first+1):
	for i in range(1,second + 1):
		ran = make_range(ran)
		mrange = int(ran)
		for j in range(1,third + 1):
			work += 1
			val = get_in_range(mrange)
			template += "%i," % val
		
		# Make sure that the line end is proper
		val = get_in_range(mrange)
		template += "%i" % val

		if int(lastwork) != int(percentage(work, total)):
			lastwork = percentage(work, total)
			print("%i%% completed!" % percentage(work, total))

	template += "\n"

print "### DONE ###"
print "Dumping data to file %s" % "inputx.data"

f = open('inputx.data','w')
f.write(template)
f.close()
