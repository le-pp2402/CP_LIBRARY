import os

ignores = ['.git'] 
print(os.listdir('./'))

with open('contents.txt', 'w') as f:
    for section in os.listdir('./'):
        if section not in ignores and os.path.isdir(section):
            f.write('[{}]\n'.format(section))
            for sub in os.listdir(os.path.join('./', section)):
                f.write(os.path.join(section, sub) + '\t' + sub.split('.')[0] + '\n')
    f.close()
