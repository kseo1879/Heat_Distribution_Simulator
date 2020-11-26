# HEAT-DISTRIBUTION-SIMULATOR

This is the submittion for HEAT-DISTRIBUTION Simulation SOFT3410 Assignment2 Part 1

By: Calvin Seo

SID: 480347192

## How to use

### 1. To run and test the program 

To compile: You can simply type this in your command line
```bash
make
```
OR
```bash
make firewall
```

- Now, You have two options here to test the program output.

```bash
make test_2d
```
OR
```bash
make test_3d
```

This will output the requirnment of 10 X 10 array of heat distribution. 

2d will test it's result of implementing two, two dimentional array.

3d will test it's result of implementing one, three dimentional array. 

### 2. To clean the directory

To clean the directory simply type
```bash
make clean
```

### 3. Changing the macros

firewall.c file will contain these macros from line 7 to 13

```bash
#define N (100)
#define PRINT (10) //IT WILL PRINT PRINT X PRINT 
#define ITERATION (5000) 
#define ROOM_TEMP (20.0)
#define FIRE_TEMP (100.0)
#define FIRE_PERCENTAGE (0.4)
#define THREAD_NUM (4)
```
You can change these numbers to print out or test different result.

- N: This specifies the size of N X N size metrix. 
- PRINT: This specifies the number N X N you want to print out at the end. When PRINT is 10, it will print out output as 10 X 10. 
- ITERTION: It is the number of iteration you want to iterate.
- ROOM_TEMP: Is the default room temperature, and also a initial temperature before the iteration.
- FIRE_TEMP: This would be the temperature of the fire wall.
- FIRE_PERCENTAGE: This would be percentage of the firewall. The above case would give 40% of fire wall.
- THREAD_NUM: This will change the number of threads that will execute the program.

