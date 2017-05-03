import re
import subprocess

def parse_verbose_line(line):
    return int(re.search(r'\d+', str(line)).group())


def parse_result(result):
    return [data for data in str(result).split(' ')[1:]]


def readstd(p):
    result = p.stdout.readline()
    print(result, end='')
    return result


def collect_data(step_size=3000, max_size=25000):
    ids = []
    with open("playerData.txt") as datafile:
        next(datafile)
        for line in datafile:
            ids.append(line.split(',')[3])

    start_size = 5147
    print("starting data gathering")
    with open("data.csv", 'w') as csv:
        csv.write("size, OA, collisions, resolution ops, search ops, CHAIN, collisions, resolution ops, search ops\n")
        for size in range(start_size, max_size, step_size):
            csv.write(str(size))

            p = subprocess.Popen(['./a', 'playerData.txt', str(size)], stdin=subprocess.PIPE, stdout=subprocess.PIPE, bufsize=1, universal_newlines=True)

            size_line = parse_verbose_line(readstd(p))
            oa_collisions = parse_verbose_line(readstd(p))
            c_collisions = parse_verbose_line(readstd(p))
            oa_resolve_ops = parse_verbose_line(readstd(p))
            c_resolve_ops = parse_verbose_line(readstd(p))

            oa_search_ops, c_search_ops = 0, 0
            for id in ids:
                readstd(p)
                readstd(p)  # menu
                p.stdin.write('A\r')
                p.stdin.flush()
                p.stdin.write(id)
                p.stdin.write('\r')
                result = readstd(p)
                data = parse_result(result)
                oa_search_ops += int(data[0].strip())
                c_search_ops += int(data[1].strip())
            oa_search_ops /= len(ids)
            c_search_ops /= len(ids)

            readstd(p)
            readstd(p)
            p.stdin.write('2\n')
            if p:
                p.kill()

            print("writing results!")

            csv.write(",,{oa_col},{oa_res},{oa_sch},,{c_col},{c_res},{c_sch}\n".format(oa_col=oa_collisions,
                                                                                      oa_res=oa_resolve_ops,
                                                                                      oa_sch=oa_search_ops,
                                                                                      c_col=c_collisions,
                                                                                      c_res=c_resolve_ops,
                                                                                      c_sch=c_search_ops))


if __name__ == '__main__':
    collect_data()




