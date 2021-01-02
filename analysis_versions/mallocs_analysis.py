import os


def sort_versions(mal_lst):
    sort_mal_names = [(mal_name.split('_')[2].split('.')[0], mal_name) for mal_name in mal_lst]
    sort_mal_names.sort(key=lambda x: int(x[0]), reverse=True)
    return [mal_name[1] for mal_name in sort_mal_names]


def prev_malloc_file_window_search(i, line, prev_f_lines, out_file1):
    if line not in prev_f_lines:
        out_file1.write('line ' + str(i) + ' is a new one: ' + line)


def find_differences(cur_mal, prev_mal):
    def create_path(file_name, dir='./mallocs'):
        return os.path.join(dir, file_name)

    cur_f, prev_f = open(create_path(cur_mal), 'r'), open(create_path(prev_mal), 'r')
    prev_f_lines = prev_f.readlines()

    out_file1 = open(create_path(cur_mal, './logs_of_not_found_lines'), 'w+')
    out_file1.write('Comparison of files: ' + cur_mal + ' and ' + prev_mal + '\n')

    for i, line in enumerate(cur_f.readlines()):
        prev_malloc_file_window_search(i, line, prev_f_lines, out_file1)


if __name__ == '__main__':
    malloc_files = sort_versions(os.listdir('mallocs'))
    for i in range(len(malloc_files) - 1):
        find_differences(malloc_files[i], malloc_files[i+1])


