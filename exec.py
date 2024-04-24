import subprocess

def compile():
    subprocess.run(["g++", "-o", "parallel", "-fopenmp", "parallel.c"], check=True)
    subprocess.run(["g++", "-o", "sequential", "sequential.c"], check=True)
                    
def get_data(threads):
    slices = []
    result = []
    time = []
    clock = []
    tmp = ''
    cont = 0
    for n in range(0, 9):
        a = pow(10,n)
        slices.append(a)
        if threads == 0:
            process = subprocess.Popen(["./sequential", str(a)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        else:
            process = subprocess.Popen(["./parallel", str(threads),str(a)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        output = stdout.decode()
        for i in output:
            if(i != '\n'):
                if(tmp == ''):
                    tmp = i
                else:
                    tmp = tmp+i
            else:
                if cont == 0:
                    result.append(float(tmp))
                    tmp = ''
                    cont = cont+1
                elif cont == 1:
                    time.append(float(tmp))
                    tmp = ''
                    cont = cont+1
                else:
                    clock.append(int(tmp))
                    tmp = ''
                    cont = 0 
    if(threads == 0):
        print('Execução sequencial')
    else:
        print('Execução com '+str(threads)+' threads')
    print(slices)
    print(result)
    print(time)
    print(clock)



def main():
    compile()
    threads = [0, 2, 4, 6, 8, 16]
    for i in threads:
        get_data(i)

if __name__ == '__main__':
    main()
