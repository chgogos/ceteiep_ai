globvar = 0

def printMove(fr,to):
    global globvar
    print(str(globvar) + '. move from ' + str(fr) + ' to ' + str(to))

def towers(n, fr, to, spare):
    global globvar
    if n==1:
        globvar += 1
        printMove(fr, to)
    else:
        towers(n-1, fr, spare, to)
        towers(1,fr,to,spare)
        towers(n-1, spare, to, fr)

if __name__ == "__main__":
    towers(4, 'f', 't', 's')