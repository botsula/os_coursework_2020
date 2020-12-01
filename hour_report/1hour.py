import matplotlib.pyplot as plt

if __name__ == '__main__':
    f = open('1hour_mmap.txt', 'r')

    x = []
    for line in f:
        try:
            x.append(int(line.split()[2][:-1]))
        except ValueError:
            break

    plt.bar([i for i in range(len(x))], height=x)
    plt.ylabel('mmap size (bytes)')
    plt.xlabel('Number of mmaps')
    plt.title('One hour script of delay')
    plt.savefig('1hour.png')
    plt.show()
