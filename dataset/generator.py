import os

def generate_command(test_file, command, member1 = '', member2 = ''):
    test_file.write(command + ' ' + member1 + ' ' + member2 + '\n')

os.mkdir('generator_tests')
os.chdir('generator_tests')

for members in range(5, 101, 5):
    file_name = 'test_' + str(members) + '.txt'
    max_edges = (members * (members - 1))//2
    n_instructions = 6

    test_file = open(file_name, 'w')
    # write number of members, number of edges and number of instructions
    test_file.write(str(members) + ' ' + str(max_edges) + ' ' + str(n_instructions) + '\n')
    
    # write team ages
    test_file.write('1')
    for i in range(2, members + 1):
        test_file.write(' ' + str(i))
    test_file.write('\n')

    # write the edges between the members
    for i in range(1, members + 1):
        for j in range(i + 1, members + 1):
            test_file.write(str(i) + ' ' + str(j) + '\n')
    
    last_member = str(members)
    generate_command(test_file, 'C', '1')
    generate_command(test_file, 'C', last_member)
    generate_command(test_file, 'S', last_member, last_member)
    generate_command(test_file, 'S', '1', last_member)
    generate_command(test_file, 'S', str(members - 1), last_member)
    generate_command(test_file, 'M')

    test_file.close()