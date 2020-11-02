import matplotlib.pyplot as plt
from alive_progress import alive_bar
import seaborn as sns
import numpy as np


class Tracer:
    def __init__(self):
        self.all_time = 0  # all running time (TODO: add while reading)
        self.timestamps = []  # relative timestamps when mmap appears
        self.addr = []  # address of mmap-ing
        self.all_cmd_num = []  # just indexes of all commands (can be interpreted as timeline)
        self.cmd_num = []  # indexes of mmap-s
        self.flags = []  # flag of mmap
        self.all_sizes = []  # >0 - if mmap | 0 - else
        self.only_mmap_sizes = []
        self.if_mmap = []  # 'mmap' | 'not mmap'
        self.big_sizes = []
        self.small_sizes = []


def read(file_name):
    cur_tracer = Tracer()
    count = 0
    with open(file_name, 'r') as f:
        for line in f:
            count += 1

    with open(file_name) as fp:
        line = fp.readline()
        cnt = 1
        with alive_bar(count) as bar:
            while line:
                if line.find('mmap') != -1:

                    temp_line = line.replace('(', ' ').replace(')', ' ').replace(',', '').split(' ')[5:]

                    # temp_line looks like -----------------------------------------------
                    # ['0.000034', 'mmap', 'NULL', '421512', 'PROT_READ', 'MAP_PRIVATE',
                    # '37', '0', '', '=', '0x7f5bcd299000\n']
                    # ----------------------------------------------------------------

                    print(temp_line)

                    cur_tracer.timestamps.append(float(temp_line[0]))
                    cur_tracer.addr.append(temp_line[2])
                    cur_tracer.all_sizes.append(int(temp_line[3]))
                    cur_tracer.only_mmap_sizes.append(int(temp_line[3]))
                    cur_tracer.cmd_num.append(cnt)
                    cur_tracer.if_mmap.append('mmap')

                    if int(temp_line[3]) > 100000:
                        cur_tracer.big_sizes.append(int(temp_line[3]) / 100000)
                    else :
                        cur_tracer.small_sizes.append(int(temp_line[3]) / 1000)
                    # break
                else:
                    cur_tracer.all_sizes.append(0)
                    cur_tracer.if_mmap.append('not mmap')

                cur_tracer.all_cmd_num.append(cnt)

                line = fp.readline()
                cnt += 1
                bar()

    return cur_tracer


def visualise(trace_object: Tracer):

    print("Mean = ", sum(tracer.only_mmap_sizes) / len(tracer.only_mmap_sizes))
    print("Max = ",  max(tracer.only_mmap_sizes))
    print("Min = ",  min(tracer.only_mmap_sizes))


    # ---------------------------------------------------------------------

    fig, ax = plt.subplots(figsize=(14, 10))
    ax.plot(trace_object.only_mmap_sizes)
    ax.set_xlabel('num of mmap', fontsize=14)
    ax.set_ylabel('Size', fontsize=14)

    plt.title('Mmap size (B) / time ({})'.format(file[:-4]))
    plt.show()

    fig.savefig('sizebytime_{}.png'.format(file[:-4]))

    # -------------------------------------------------------

    fig, ax = plt.subplots(figsize=(14, 10))
    ax.plot(trace_object.big_sizes)
    ax.set_xlabel('num of mmap', fontsize=14)
    ax.set_ylabel('Size', fontsize=14)

    plt.title('Mmap big size (MB) / time ({})'.format(file[:-4]))
    plt.show()

    fig.savefig('bigsizebytime_{}.png'.format(file[:-4]))




    fig, ax = plt.subplots(figsize=(14, 10))
    ax.plot(trace_object.small_sizes)
    ax.set_xlabel('num of mmap', fontsize=14)
    ax.set_ylabel('Size', fontsize=14)

    plt.title('Mmap small size (KB) / time ({})'.format(file[:-4]))
    plt.show()

    fig.savefig('smallsizebytime_{}.png'.format(file[:-4]))

    # ----------------------------------------------------------------------

    f, axes = plt.subplots(1, 1, figsize=(14, 4))

    sns.countplot(trace_object.only_mmap_sizes, ax=axes)
    axes.set_xlabel('Sizes', fontsize=14)
    axes.set_ylabel('Count', fontsize=14)

    plt.tick_params(
        axis='x',  # changes apply to the x-axis
        which='both',  # both major and minor ticks are affected
        bottom=False,  # ticks along the bottom edge are off
        top=False,  # ticks along the top edge are off
        labelbottom=False)

    plt.title('Count of dif. mmap sizes ({})'.format(file[:-4]))
    # sns.scatterplot(x=trace_object.all_cmd_num, y=trace_object.all_sizes, hue=trace_object.if_mmap, ax=axes[1])
    # axes[1].set_xlabel('Time', fontsize=14)
    # axes[1].set_ylabel('Size', fontsize=14)
    # axes[1].yaxis.set_label_position("right")
    # axes[1].yaxis.tick_right()

    plt.show()
    f.savefig('count_{}.png'.format(file[:-4]))


#     --------------------------------------------------------

    f, axes = plt.subplots(1, 1, figsize=(14, 4))

    sns.countplot(trace_object.big_sizes, ax=axes)
    axes.set_xlabel('Sizes', fontsize=14)
    axes.set_ylabel('Count', fontsize=14)

    plt.tick_params(
        axis='x',  # changes apply to the x-axis
        which='both',  # both major and minor ticks are affected
        bottom=False,  # ticks along the bottom edge are off
        top=False,  # ticks along the top edge are off
        labelbottom=False)

    plt.title('Count of dif. big mmap sizes ({})'.format(file[:-4]))
    # sns.scatterplot(x=trace_object.all_cmd_num, y=trace_object.all_sizes, hue=trace_object.if_mmap, ax=axes[1])
    # axes[1].set_xlabel('Time', fontsize=14)
    # axes[1].set_ylabel('Size', fontsize=14)
    # axes[1].yaxis.set_label_position("right")
    # axes[1].yaxis.tick_right()

    plt.show()
    f.savefig('bigcount_{}.png'.format(file[:-4]))


#     ---------------------------------

    f, axes = plt.subplots(1, 1, figsize=(14, 4))

    sns.countplot(trace_object.small_sizes, ax=axes)
    axes.set_xlabel('Sizes', fontsize=14)
    axes.set_ylabel('Count', fontsize=14)

    plt.tick_params(
        axis='x',  # changes apply to the x-axis
        which='both',  # both major and minor ticks are affected
        bottom=False,  # ticks along the bottom edge are off
        top=False,  # ticks along the top edge are off
        labelbottom=False)

    plt.title('Count of dif. small mmap sizes ({})'.format(file[:-4]))
    sns.scatterplot(x=trace_object.all_cmd_num, y=trace_object.all_sizes, hue=trace_object.if_mmap, ax=axes[1])
    axes[1].set_xlabel('Time', fontsize=14)
    axes[1].set_ylabel('Size', fontsize=14)
    axes[1].yaxis.set_label_position("right")
    axes[1].yaxis.tick_right()

    plt.show()
    f.savefig('smallcount_{}.png'.format(file[:-4]))

if __name__ == '__main__':
    file = "firefox_youtube1.txt"
    tracer = read('../' + file)
    visualise(tracer)
