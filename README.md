# Quad equations solver

"The best quad equations solver ever" © Steve Jobs

### Build
Repo includes Makefile. Build with `make`.

**Note:** In `main.cpp` you can find `TEST` define. Undefine it for disabling test mode.

### Usage
Type in terminal: `.\main.exe`

#### Available flags:

1. `-h` - help
2. `-t` - works only when `TEST` was defined. After it, you must specify file with tests

#### Available return values:

`0` - `OK`

`1` - `Wrong arguments given`

`2` - `User input error`

`3` - `Test file input error`

`4` - `End of input stream reached`

### Test mode
In this test program with test itself. You must specify test file in format (there might be multiple tests):
```
<coeff a> <coeff b> <coeff c>
<solutions number>
<solution 1 (if exists)> <solution 2 (if exists)>

```
E.g.
```
1 -10 1
2
0.101021 9.898979

1 1
1
0

```


## Credits
This is MIPT summer school project. DED and DRA forever
