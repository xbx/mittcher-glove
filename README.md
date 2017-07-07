# Mittcher Glove

![Mittcher Glove Logo](logo.png)
A simple application using **ptrace(2)** to capture the stderr of a process.

## How to use it

### Compilation

```sh
gcc -o mittcher-glove.out ./src/tracer.c
```

### Running an example

These example programs will exit with an error after waiting some seconds.
If you do not manage to go through the commands in time, then try again.

Python:

```sh
python tracee/asd.py & #This would output a PID
```

NodeJS:
```sh
node tracee/node-error.js & #This would output a PID
```

```sh
sudo ./mittcher-glove <pid_of_asd.py>
```

## References

[My seminal question on StackOverflow](http://stackoverflow.com/43854398/read-the-stderr-of-a-process-using-ptrace2)
