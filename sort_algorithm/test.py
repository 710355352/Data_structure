# import random
import dis
def main():
    a = list(range(10))
    b = a[0:5]
    b[0] = 10

dis.dis('__main__')
dis.dis(main)

