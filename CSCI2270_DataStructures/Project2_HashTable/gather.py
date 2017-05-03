import os
import subprocess

p = subprocess.Popen(['./a', 'playerData.txt', '17000'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)


size_line = p.stdout.readline()
oa_col_line = p.stdout.readline()
c_col_line = p.stdout.readline()
oa_ops_line = p.stdout.readline()
c_ops_line = p.stdout.readline()

print(str(size_line))
print(str(oa_col_line))
print(str(c_col_line))
print(str(oa_ops_line))
print(str(c_ops_line))

p.communicate(input=b'2/n')
