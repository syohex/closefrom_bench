# closefrom system call micro benchmark

## Environment

FreeBSD 12.1 on Virtualbox

## Build

```
make
```

## Result

```
% make bench
Close 100 file descriptors
closefrom: 26 usecs
close: 29 usecs

Close 1000 file descriptors
closefrom: 311 usecs
close: 316 usecs

Close 10000 file descriptors
closefrom: 3772 usecs
close: 3943 usecs

Close 100000 file descriptors
closefrom: 37590 usecs
close: 45523 usecs
```
