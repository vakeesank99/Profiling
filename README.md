# Profiling for 1000000 integer sum
Profiling is most critical part when it comes to the in depth understanding of computer architecture. even though it's good practice to start from the VM box or related virtual machines for linux. but rather i tried the Windows Subsystem for Linux(WSL) in windows 11 os. hope you can follow the steps below. if you have already done the WSL part kind check out the **Profiling**. 

## 1. WSL
```
wsl --install -d ubuntu
```
 but i got the error 
 Error: 0x800701bc WSL 2 requires an update to its kernel component. For information please visit
so i try to update the wsl first using 
```
wsl --update
```
 then it worked fine
 started the interface create the directory 
 ```
 mkdir your_dir_name

```
then main.c 
 ```
 vim main.c
```

other commands
`i `- insert the code
`:w: `save
`:wq:` save and quit

how to delete one line 
`dd

1. Update and upgrade:

```bash
$ sudo apt-get update && sudo apt-get upgrade -y
```
.Clean unrequired packages:

```bash
$ sudo apt autoremove -y
```

3. Install GCC:

```bash
$ sudo apt-get install gcc -y
```
4. Check and confirmed installed gcc version:

```bash
gcc --version
```

compile the c file
```
gcc -o main.out main.c
```

then run the file
`./main.out`
## 2.Profiling
### GPROF
compile for open text file and save the answers in a text file.\
`gcc -pg -o main.out main.c -DCREATE_TEXT -DTEXT`\

then run using\
`./main.out`

generate profiling files\
 `gprof main.out gmon.out > gprof_text_analysis.txt`\
likewise for bin\
```
	gcc -pg -o main.out main.c -DCREATE_BIN -DBIN
	./main.out
	gprof main.out gmon.out > gprof_bin_analysis.txt
```
for mem\
```
	gcc -pg -o main.out main.c -DMEM
	./main.out
	gprof main.out gmon.out > gprof_mem_analysis.txt
```

### PERF

install perf\

```
apt install flex bison
git clone https://github.com/microsoft/WSL2-Linux-Kernel --depth 1
cd WSL2-Linux-Kernel/tools/perf
make -j8
sudo cp perf /usr/local/bin
```

for activate several settings tab do the below code\
`sudo sysctl kernel.perf_event_paranoid=-1`

record the events\
```
perf record -B  dd if=/dev/zero of=/dev/null c
ount=100000
```
 to look at all the hardware and software events\
 ```
perf stat  -e branch-misses,cache-misses,cache-references,cpu-cycles,instructions,stalled-cycles-backend,stalled-cycles-frontend,alignment-faults,bpf-output,cgroup-switches,context-switches,cpu-clock,cpu-migrations,dummy,emulation-faults,major-faults,minor-faults,page-faults,task-clock ./main.out dd if=/dev/zero of=/dev/null count=100000
```
 so that the final comparison between three main tasks are given below
#### Memory
Performance counter stats for './main.out dd if=/dev/zero of=/dev/null count=100000':
```
             55637      branch-misses
(58.52%)
            467314      cache-misses              #   25.133 % of all cache refs      (70.20%)
           1859377      cache-references          #   77.133 M/sec
          48097253      cpu-cycles                #    1.995 GHz
          46720730      instructions              #    0.97  insn per cycle
                                                  #    0.59  stalled cycles per insn
          27742292      stalled-cycles-backend    #   57.68% backend cycles idle
           5360078      stalled-cycles-frontend   #   11.14% frontend cycles idle     (71.29%)
                 0      alignment-faults          #    0.000 /sec
                 0      bpf-output                #    0.000 /sec
                 0      cgroup-switches           #    0.000 /sec
                 0      context-switches          #    0.000 /sec
             24.11 msec cpu-clock                 #    0.978 CPUs utilized
                 0      cpu-migrations            #    0.000 /sec
                 0      dummy                     #    0.000 /sec
                 0      emulation-faults          #    0.000 /sec
                 0      major-faults              #    0.000 /sec
              1967      minor-faults              #   81.598 K/sec
              1967      page-faults               #   81.598 K/sec
             24.11 msec task-clock                #    0.978 CPUs utilized

       0.024650240 seconds time elapsed

       0.000000000 seconds user
       0.024820000 seconds sys
```
#### Text

 Performance counter stats for './main.out dd if=/dev/zero of=/dev/null count=100000':
```
           2145107      branch-misses
             (84.60%)
          19326521      cache-misses              #   60.972 % of all cache refs      (84.84%)
          31697305      cache-references          #   54.216 M/sec                    (86.31%)
        1561671251      cpu-cycles                #    2.671 GHz
             (86.33%)
        3896994228      instructions              #    2.50  insn per cycle
                                                  #    0.11  stalled cycles per insn  (86.31%)
         420365823      stalled-cycles-backend    #   26.92% backend cycles idle      (86.30%)
          63062423      stalled-cycles-frontend   #    4.04% frontend cycles idle     (85.32%)
                 0      alignment-faults          #    0.000 /sec

                 0      bpf-output                #    0.000 /sec

                 0      cgroup-switches           #    0.000 /sec

                 0      context-switches          #    0.000 /sec

            584.65 msec cpu-clock                 #    0.999 CPUs utilized
                 0      cpu-migrations            #    0.000 /sec

                 0      dummy                     #    0.000 /sec

                 0      emulation-faults          #    0.000 /sec

                 0      major-faults              #    0.000 /sec

                66      minor-faults              #  112.889 /sec

                66      page-faults               #  112.889 /sec

            584.65 msec task-clock                #    0.999 CPUs utilized

       0.585086988 seconds time elapsed

       0.262352000 seconds user
       0.322894000 seconds sys
       ```
#### Binary
Performance counter stats for './main.out dd if=/dev/zero of=/dev/null count=100000':
```
            338146      branch-misses
             (85.81%)
            994342      cache-misses              #    8.115 % of all cache refs      (85.79%)
          12253470      cache-references          #   34.794 M/sec                    (85.82%)
        1378437548      cpu-cycles                #    3.914 GHz
             (85.78%)
        3924117823      instructions              #    2.85  insn per cycle
                                                  #    0.10  stalled cycles per insn  (85.82%)
         387032460      stalled-cycles-backend    #   28.08% backend cycles idle      (85.81%)
           5583238      stalled-cycles-frontend   #    0.41% frontend cycles idle     (85.17%)
                 0      alignment-faults          #    0.000 /sec

                 0      bpf-output                #    0.000 /sec

                 0      cgroup-switches           #    0.000 /sec

                 0      context-switches          #    0.000 /sec

            352.17 msec cpu-clock                 #    0.999 CPUs utilized
                 0      cpu-migrations            #    0.000 /sec

                 0      dummy                     #    0.000 /sec

                 0      emulation-faults          #    0.000 /sec

                 0      major-faults              #    0.000 /sec

                65      minor-faults              #  184.569 /sec

                65      page-faults               #  184.569 /sec

            352.17 msec task-clock                #    0.999 CPUs utilized

       0.352507170 seconds time elapsed

       0.342683000 seconds user
       0.010078000 seconds sys
       ```
## References
1. [https://perf.wiki.kernel.org/index.php/Tutorial#Collecting_samples]
2. [https://hackingcpp.com/cpp/tools/profilers.html]
